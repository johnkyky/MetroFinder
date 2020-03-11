#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include <map>    
#include <fstream>
#include <math.h>

float mapTo(float a, float b, float c, float d, float val)
{
    return ( (val - a) / (b - a)) * (d - c) + c;
}

std::map<std::string, sf::Vector2f> load_positions(std::string fileName)
{
    std::ifstream f(fileName);
    std::map<std::string, sf::Vector2f> res;

    while (!f.eof())
    {
        std::string nom;
        double x, y;

        f >> x;
        f >> y;
        x = mapTo(643375, 665000, 50, 1500, x);
        y = mapTo(6853445, 6873000, 950, 0, y);
        f.get();
        getline(f, nom);
        res.insert(std::pair<std::string, sf::Vector2f>(nom, sf::Vector2f(x, y)));
    }
    f.close();
    return res;
}

int main()
{
    Graph graph;
    graph.load_from_file("metro.txt");
    graph.render();

    std::map<std::string, sf::Vector2f> mappotron = load_positions("positions.txt");
    sf::RenderWindow window(sf::VideoMode(1500, 1000), "MetroFinder");
    sf::CircleShape station;
    station.setFillColor(sf::Color::Red);
    station.setRadius(4);
    window.setFramerateLimit(5);
    auto& vertices = graph.getVertices();
    std::cout << "Position : " << mappotron["Abbesses"].x << " " << mappotron["Abbesses"].y << std::endl;
    std::map<std::string, sf::Color> couleur;
    couleur["1"] = sf::Color::Red;
    couleur["2"] = sf::Color::Yellow;
    couleur["3"] = sf::Color::Red;
    couleur["3b"] = sf::Color::Red;
    couleur["4"] = sf::Color::White;
    couleur["5"] = sf::Color::Green;
    couleur["6"] = sf::Color::Magenta;
    couleur["7"] = sf::Color(125,150, 100);
    couleur["7b"] = sf::Color(0,125, 255);
    couleur["8"] = sf::Color(125,0,150);
    couleur["9"] = sf::Color(255,0,125);
    couleur["10"] = sf::Color(125,255, 0);
    couleur["11"] = sf::Color(125,0, 255);
    couleur["12"] = sf::Color(255,125, 0);
    couleur["13"] = sf::Color(20,255, 125);
    couleur["14"] = sf::Color::Blue;
    while (window.isOpen())
    {

        sf::Vector2i posmouse = sf::Mouse::getPosition(window);
        sf::Event evt;

        while (window.pollEvent(evt))
        {
            if (evt.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (auto& station : vertices)
        {
            for (auto& connexion : station.second.getEdges())
            {
                if (connexion.getMetro() == false)
                    continue;
                sf::Vector2f posa = mappotron[station.second.getName()];
                posa.x += 4; posa.y += 4;
                sf::Vector2f posb = mappotron[vertices[connexion.getDestination()].getName()];
                posb.x += 4; posb.y += 4;
                sf::Vertex line[] =
                {
                    sf::Vertex(posa, couleur[station.second.getLine()]),
                    sf::Vertex(posb, couleur[station.second.getLine()])
                };
                window.draw(line, 2, sf::Lines);
            }
        }
        for (auto& i : mappotron)
        {
            station.setPosition(i.second);
            window.draw(station);
        }
        for (auto& station : mappotron) {
            if (sqrt(pow(station.second.x - posmouse.x, 2) + pow(station.second.y - posmouse.y, 2)) <= 4)
                std::cout << "Ciblé : " << station.first << std::endl;
        }
        window.display();
    }
    return 0;
}