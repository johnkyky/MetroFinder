#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <stack>
#include <chrono>

struct edge {
    int id_source;
    int id_destination;
    unsigned int duration;
    bool is_metro = true;
};
typedef struct edge edge;

struct gare {
    std::string nom = "Undefined";
    int id = 0;
    std::string ligne = "";
    std::list<edge> connexion;
    int x = 0, y = 0;
};
typedef struct gare gare;

std::map<int, gare> load_raw(std::string fileName)
{
    std::ifstream fileStream;
    std::map<int, gare> res;
    char temp = ' ';

    fileStream.open(fileName);
    if (fileStream.fail() || !fileStream.is_open())
        throw std::runtime_error("Cannot open file \"" + fileName +"\"");
    std::cout << "Loading raw data\n";
    fileStream >> temp;
    while (!fileStream.eof() && temp != 'E') {
        gare buffer;

        fileStream >> buffer.id;
        if (temp == 'T')
            fileStream >> buffer.ligne;
        fileStream.get();
        std::getline(fileStream, buffer.nom);
        res.emplace(buffer.id, buffer);
        fileStream >> temp;
    }
    while (!fileStream.eof() && temp == 'E') {
        edge buffer;

        fileStream >> buffer.id_source >> buffer.id_destination >> buffer.duration;
        if (res[buffer.id_source].nom == res[buffer.id_destination].nom)
            buffer.is_metro = false;
        res[buffer.id_source].connexion.push_front(buffer);
        std::swap(buffer.id_destination, buffer.id_source);
        res[buffer.id_source].connexion.push_front(buffer);
        fileStream >> temp;
    }
    fileStream.close();
    return res;
}

void propagate_line(std::map<int, gare>& res)
{
    std::stack<int> to_treat;

    for (auto& g : res) {
        to_treat.push(g.second.id);
        while (!to_treat.empty()) {
            gare& station = res[to_treat.top()];
            to_treat.pop();
            if (station.ligne != "")
                for (auto& j : station.connexion) {
                    if (j.is_metro == false || res[j.id_destination].ligne != "")
                        continue;
                    res[j.id_destination].ligne = station.ligne;
                    to_treat.push(j.id_destination);
                }
        }
    }
}


int main()
{
    clock_t begin = clock();
    std::map<int, gare> test = load_raw("metro.txt");
    propagate_line(test);
    clock_t end = clock();
    for(auto& i : test) {
        std::cout << "Station : " << i.second.id << " " << i.second.nom << " ligne : " << i.second.ligne << std::endl << "Connecté a : " << std::endl;
        for (auto& j : i.second.connexion) {
            std::cout << "\t" << j.id_destination << " en " << j.duration << " seconde(s)" ;
            if (!j.is_metro)
                std::cout << " en marche a pied";
            std::cout << "." << std::endl;
        }
    }
    std::cout << "Elapsed time : " << double(end - begin) / CLOCKS_PER_SEC << std::endl;
    return 0;
}
