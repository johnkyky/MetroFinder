#include "GraphDrawer.hpp"

using namespace std::chrono;

float mapTo(float a, float b, float c, float d, float val)
{
    return ( (val - a) / (b - a)) * (d - c) + c;
}

GraphDrawer::GraphDrawer(Graph& newGraph, const std::string stationPositions) : zoom(1), graph(newGraph), 
window(sf::VideoMode(1500, 1000), "MetroFinder"),  hovered_station(NULL), selected_station(NULL)
{
    std::cout << "Loading stations positions from " << stationPositions << "\n";
    std::cout << load_station(stationPositions) << " positions found\n";
    load_color();
    window.setFramerateLimit(120);
    window.setVisible(false);
    leftPanel.setSize(sf::Vector2f(3 * window.getSize().x / 4, window.getSize().y));
    leftPanel.setViewport(sf::FloatRect(0, 0, 0.75f, 1.0f));
    rightPanel.setSize(sf::Vector2f(window.getSize().x / 4, window.getSize().y));
    rightPanel.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 1.0f));
}

GraphDrawer::~GraphDrawer()
{

}

void GraphDrawer::setSize(const unsigned int x, const unsigned int y) {window.setSize(sf::Vector2u(x, y));}
void GraphDrawer::setGraph(Graph& newGraph) {graph = newGraph;}

void GraphDrawer::display()
{
    window.setVisible(true);
    time_point<high_resolution_clock> last_update = high_resolution_clock::now();
    time_point<high_resolution_clock> current;
    int update_time = 0;
    const int update_per_second = 1000 / 10;

    while (window.isOpen())
    {
        current = high_resolution_clock::now();
        update_time += duration_cast<milliseconds>(current - last_update).count();

        window.clear(sf::Color(29, 34, 43));
        handleEvent();
        while (update_time >= update_per_second) {
            update();
            update_time -= update_per_second;
        }
        render();
        window.display();
        last_update = current;
    }
}

int GraphDrawer::load_station(std::string fileName)
{
    std::ifstream file(fileName);
    int compteur = 0;

    if (file.fail() || !file.is_open())
        throw std::runtime_error("[ERROR] : cannot open file " + fileName + "\n");
    while (!file.eof())
    {
        std::string buffer;
        int x, y;

        file >> x >> y;
        file.get();
        std::getline(file, buffer);
        x = mapTo(643375, 662000, 50, 3 * window.getSize().x / 4 - 50, x);
        y = mapTo(6853445, 6873000, window.getSize().y - 50, 50, y);
        stations.insert(std::pair<std::string, Station>(buffer, Station(buffer, x, y)));
        compteur++;
    }
    file.close();
    return compteur;
}

void GraphDrawer::load_color()
{
    lignesColor["1"]    = sf::Color(230, 165,  37);
    lignesColor["2"]    = sf::Color( 26,  76, 201);
    lignesColor["3"]    = sf::Color(140, 156,   3);
    lignesColor["3b"]   = sf::Color( 15, 219, 209);
    lignesColor["4"]    = sf::Color(205,  15, 212);
    lignesColor["5"]    = sf::Color(224, 142,  27);
    lignesColor["6"]    = sf::Color( 47, 247, 111);
    lignesColor["7"]    = sf::Color(231, 149, 237);
    lignesColor["7b"]   = sf::Color(107, 179, 109);
    lignesColor["8"]    = sf::Color(194, 155, 201);
    lignesColor["9"]    = sf::Color(207, 204,  33);
    lignesColor["10"]   = sf::Color(219, 170,  72);
    lignesColor["11"]   = sf::Color(117,  81,   9);
    lignesColor["12"]   = sf::Color( 22, 168,  80);
    lignesColor["13"]   = sf::Color(120, 255, 237);
    lignesColor["14"]   = sf::Color(125,   5, 252);
}

void GraphDrawer::handleEvent()
{
    sf::Event evt;

    window.setView(leftPanel);
    hovered_station = NULL;
    bool clicked = false;
    while (window.pollEvent(evt))
    {
        if (evt.type == sf::Event::Closed)
            window.close();
        else if (evt.type == sf::Event::MouseWheelScrolled) {
            double add = evt.mouseWheelScroll.delta * -0.1;
            if (add > 0 && zoom <= 1.2) {
                zoom += add;
                leftPanel.zoom(1 + add);
            }
            else if(add < 0 && zoom > 0) {
                zoom += add;
                leftPanel.zoom(1 + add);
            }
        }
        else if (evt.type == sf::Event::MouseButtonPressed)
            clicked = true;
    }
    for (auto& i : stations)
    {
        i.second.handleEvent(window, clicked);
        if (i.second.isHovered()) {
            hovered_station = &i.second;
            if (i.second.isSelected())
                selected_station = &i.second;
        }
    }
    window.setView(rightPanel);
}

void GraphDrawer::update()
{
    if (hovered_station != NULL)
        std::cout << "Station : " << hovered_station->getName() << "\n";
    else if (selected_station != NULL)
        std::cout << selected_station->getName() << "\n";
}

void GraphDrawer::render()
{
    window.setView(leftPanel);
    auto& temp = graph.getVertices();

    for (auto& i : temp)
    {
        std::string buffer = i.second.getName();
        for (auto& c : i.second.getEdges())
        {
            sf::Vector2f posa = stations[buffer].getPosition();
            sf::Vector2f posb = stations[temp[c.getDestination()].getName()].getPosition();
            sf::Color coul = lignesColor[i.second.getLine()];
            sf::Vertex line[2] = {
                sf::Vertex(posa, coul),
                sf::Vertex(posb, coul)
            };
            window.draw(line, 2, sf::Lines);
        }
    }
    for (auto& i : stations)
    {
        i.second.draw(window);
    }
    window.setView(rightPanel);
    window.setView(window.getDefaultView());
}