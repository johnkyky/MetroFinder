#include "GraphDrawer.hpp"

using namespace std::chrono;

float mapTo(float a, float b, float c, float d, float val)
{
    return ( (val - a) / (b - a)) * (d - c) + c;
}

GraphDrawer::GraphDrawer(Graph& newGraph, const std::string stationPositions) : zoom {0}, graph{newGraph}, 
window{sf::VideoMode(1920, 1080), "MetroFinder"}, menu(window), hovered_station{NULL}, selected_station{NULL, NULL}
{
    load_station(stationPositions);
    load_color();

    font.loadFromFile("font.ttf");
    menu.setFont(font);
    menu.init();
    window.setFramerateLimit(60);
    window.setVisible(false);

    rightPanel.setSize(sf::Vector2f(double(3 * window.getSize().x / 5), window.getSize().y));
    rightPanel.setViewport(sf::FloatRect(0.4f, 0.0, 0.600f, 1.0f));
    leftPanel.setCenter(double(window.getSize().x / 5), window.getSize().y/2);
    leftPanel.setSize(sf::Vector2f(double(2 * window.getSize().x / 5), window.getSize().y));
    leftPanel.setViewport(sf::FloatRect(0.0, 0.0, 0.4f, 1.0f));
}

GraphDrawer::~GraphDrawer()
{

}

void GraphDrawer::setSize(const unsigned int x, const unsigned int y) {window.setSize(sf::Vector2u(x, y));}
void GraphDrawer::setGraph(Graph& newGraph) {graph = newGraph;}

int GraphDrawer::load_station(const std::string fileName)
{
    std::ifstream file(fileName);
    int compteur{0};

    auto& vertex = graph.getVertices();
    if (file.fail() || !file.is_open())
        return 0;
    while (!file.eof())
    {
        std::string buffer;
        int x, y;

        file >> x >> y;
        file.get();
        std::getline(file, buffer);
        x = mapTo(643000, 662000, 50, 3 * (double) window.getSize().x / 5 - 50, x);
        y = mapTo(6853000, 6873000, window.getSize().y - 50, 50, y);
        stations.insert(std::pair<std::string, Station>(buffer, Station(buffer, x, y)));
        compteur++;
    }
    for (auto& i : vertex)
    {
        stations[i.second.getName()].setId(i.second.getId());
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

        window.clear(sf::Color(53, 48, 54));
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

void GraphDrawer::handleEvent()
{
    sf::Event evt;

    hovered_station = NULL;
    bool clicked = false;
    while (window.pollEvent(evt))
    {
        window.setView(leftPanel);
        MenuDrawer::handleRes temp = menu.handleEvent(evt);

        if (temp == MenuDrawer::handleRes::StartDijkstra)
        {
            vertexPath = graph.dijkstra(selected_station[0]->getId(), selected_station[1]->getId());
            menu.setPathString(graph.vertex_to_string(vertexPath));
        }
        else if (temp == MenuDrawer::handleRes::ModeSwap)
        {

        }
        else if (temp == MenuDrawer::handleRes::Exit || evt.type == sf::Event::Closed)
            window.close();
        else
            switch (evt.type)
            {
                case sf::Event::MouseWheelScrolled:
                    handle_zoom(evt, rightPanel, zoom);
                    break;
                case sf::Event::MouseButtonPressed:
                    handle_click(evt, clicked);
                    break;
                default :
                    break;
            }
    }
    window.setView(rightPanel);
    handle_station(evt, clicked);
    window.setView(leftPanel);
}

void GraphDrawer::update()
{

}

void GraphDrawer::render()
{
    window.setView(rightPanel);
    render_line();
    render_station();
    window.setView(leftPanel);
    menu.render();
}

// Fonctions d'handle

void GraphDrawer::zoomToward(sf::Vector2i target, double zoom)
{
    const sf::Vector2f beforeCoord{ window.mapPixelToCoords(target) };
	sf::View& view = rightPanel;
	view.zoom(zoom);
	window.setView(view);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(target) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
}

void GraphDrawer::handle_zoom(sf::Event evt, sf::View& view, double& zoom)
{
    if (evt.mouseWheelScroll.delta == 0)
        return;
    zoom -= evt.mouseWheelScroll.delta;
    if (zoom < -7)
        zoom = -7;
    else if (zoom > 0)
        zoom = 0;
    else 
    {
        rightPanel.setSize(sf::Vector2f(double(3 * window.getSize().x / 5), window.getSize().y));
        window.setView(rightPanel);
        if (zoom > 0 )
        {
            zoomToward(sf::Mouse::getPosition(window), (-zoom * 1 / 0.875f));
        }
        else
        {
            zoomToward(sf::Mouse::getPosition(window), 1 - (-zoom * 0.125f));
        }
    }
    

}

void GraphDrawer::handle_click(sf::Event evt, bool& clicked)
{
    switch (evt.mouseButton.button) {
        case sf::Mouse::Right :
            if (selected_station[0])
                selected_station[0]->setSelected(false);
            if (selected_station[1])
                selected_station[1]->setSelected(false);
            selected_station[0] = selected_station[1] = NULL;
            menu.resetSourceDestination();
            break;
        case sf::Mouse::Left :
            clicked = true;
            break;
        default:
            break;
    }
}
void GraphDrawer::handle_station(sf::Event evt, const bool clicked) 
{
    for (auto& i : stations)
    {
        int temp = i.second.handleEvent(window, clicked);

        if (temp == Station::Hovered)
            hovered_station = &i.second;
        else if (temp == Station::Selected) 
        {
            if (selected_station[0]) 
            {
                if (selected_station[1])
                    selected_station[1]->setSelected(false);
                selected_station[1] = &i.second;
            } else
                selected_station[0] = &i.second;
        } else if (temp == Station::Unselected) 
        {
            if (&i.second == selected_station[0])
            {
                selected_station[0]->setSelected(false);
                selected_station[0] = NULL;
            }
            if (&i.second == selected_station[1])
            {
                selected_station[1]->setSelected(false);
                selected_station[1] = NULL;
            }
        }
    }
    menu.setSource(selected_station[0]);
    menu.setDestination(selected_station[1]);
}


//Fonctions de render

void GraphDrawer::render_line()
{
    auto& temp = graph.getVertices();
    ThickLine line;

    line.setThickness(4);
    window.setView(rightPanel);
    for (auto& i : temp)
    {
        std::string buffer = i.second.getName();
        if (menu.showLine(i.second.getLine()))
            for (auto& c : i.second.getEdges())
            {
                sf::Vector2f posa = stations[buffer].getPosition();
                sf::Vector2f posb = stations[temp[c.getDestination()].getName()].getPosition();
                line.setColor(lignesColor[i.second.getLine()]);
                line.setSource(posa);
                line.setDestination(posb);
                window.draw(line);
            }
    }
    render_path();
}

void GraphDrawer::render_path()
{
    if (vertexPath.size() == 0)
        return;
    ThickLine line;

    line.setThickness(6);
    line.setColor(sf::Color::Red);
    auto current = vertexPath.begin();
    auto next = vertexPath.begin();
    next++;
    while(next != vertexPath.end())
    {
        if (current->getName() == next->getName()) {
            current++;
            next++;
            continue;
        }
        line.setSource(stations[current->getName()].getPosition());
        line.setDestination(stations[next->getName()].getPosition());
        window.draw(line);
        current++;
        next++;
    }
}

void GraphDrawer::render_station()
{
    window.setView(rightPanel);
    for (auto& i : stations)
            i.second.draw(window);
    if (zoom <= -6)
    {
        sf::View unzoomed(sf::FloatRect(0, 0, 3 * window.getSize().x / 5, window.getSize().y));
        sf::Vector2i currentPos;
        sf::Text temp;

        unzoomed.setViewport(sf::FloatRect(0.4f, 0, 0.6f, 1.0f));
        temp.setFillColor(sf::Color::White);
        temp.setFont(font);
        temp.setCharacterSize(20);
        for (auto& i : stations)
        {
            currentPos = window.mapCoordsToPixel(i.second.getPosition());
            window.setView(unzoomed);
            temp.setString(i.second.getName());
            temp.setPosition(window.mapPixelToCoords(currentPos));
            window.draw(temp);
            window.setView(rightPanel);
        }
    }
}