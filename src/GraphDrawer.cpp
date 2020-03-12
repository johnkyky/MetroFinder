#include "GraphDrawer.hpp"

using namespace std::chrono;

float mapTo(float a, float b, float c, float d, float val)
{
    return ( (val - a) / (b - a)) * (d - c) + c;
}

GraphDrawer::GraphDrawer(Graph& newGraph, const std::string stationPositions) : zoom(0), graph(newGraph), 
window(sf::VideoMode(1500, 1000), "MetroFinder"), hovered_station(NULL), selected_station{NULL, NULL}
{
    load_station(stationPositions);
    load_color();
    font.loadFromFile("font.ttf");
    window.setFramerateLimit(60);
    window.setVisible(false);
    leftPanel.setSize(sf::Vector2f(double(3 * window.getSize().x / 5), window.getSize().y));
    leftPanel.setViewport(sf::FloatRect(0.0f, 0.0, 0.600f, 1.0f));
    leftPanel_center = leftPanel.getCenter();
    rightPanel.setCenter(double(window.getSize().x / 5), window.getSize().y/2);
    rightPanel.setSize(sf::Vector2f(double(2 * window.getSize().x / 5), window.getSize().y));
    rightPanel.setViewport(sf::FloatRect(0.600f, 0.0, 0.400f, 1.0f));
}

GraphDrawer::~GraphDrawer()
{

}

void GraphDrawer::setSize(const unsigned int x, const unsigned int y) {window.setSize(sf::Vector2u(x, y));}
void GraphDrawer::setGraph(Graph& newGraph) {graph = newGraph;}

int GraphDrawer::load_station(const std::string fileName)
{
    std::ifstream file(fileName);
    int compteur = 0;

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

void GraphDrawer::handleEvent()
{
    sf::Event evt;

    window.setView(leftPanel);
    hovered_station = NULL;
    bool clicked = false;
    while (window.pollEvent(evt))
    {
        switch (evt.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseWheelScrolled:
                handle_zoom(evt, leftPanel, zoom);
                break;
            case sf::Event::MouseButtonPressed:
                handle_click(evt, clicked);
                break;
            default :
                break;
        }
    }
    handle_station(evt, clicked);
    window.setView(rightPanel);
}

void GraphDrawer::update()
{

}

void GraphDrawer::render()
{
    render_line();
    render_station();
    render_menu();
}

// Fonctions d'handle

void GraphDrawer::zoomToward(sf::Vector2i target, double zoom)
{
    const sf::Vector2f beforeCoord{ window.mapPixelToCoords(target) };
	sf::View& view = leftPanel;
	view.zoom(zoom);
	window.setView(view);
	const sf::Vector2f afterCoord{ window.mapPixelToCoords(target) };
	const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
	view.move(offsetCoords);
}

void GraphDrawer::handle_zoom(sf::Event evt, sf::View& view, double& zoom)
{
    const int signe = (evt.mouseWheelScroll.delta > 0) ? -1 : 1;
    window.setView(leftPanel);

    if (evt.mouseWheelScroll.delta == 0)
        return;
    zoom -= evt.mouseWheelScroll.delta;
    std::cout << "Zooming : " << zoom << " Signe : " << signe << "\n";
    if (zoom < -17)
        zoom = -17;
    else if (zoom > 0)
        zoom = 0;
    else if (signe > 0)
    {
        std::cout << "Zooming out !\n";
        zoomToward(sf::Mouse::getPosition(window), 1 / 0.875f);
    }
    else
    {
        std::cout << "Zooming in !\n";
        zoomToward(sf::Mouse::getPosition(window), 0.875f);
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

        if (temp == 1)
            hovered_station = &i.second;
        else if (temp == 2) 
        {
            if (selected_station[0]) 
            {
                if (selected_station[1])
                    selected_station[1]->setSelected(false);
                selected_station[1] = &i.second;
            } else
                selected_station[0] = &i.second;
        } else if (temp == 3) 
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
}


//Fonctions de render

void GraphDrawer::render_line()
{
    auto& temp = graph.getVertices();

    window.setView(leftPanel);
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
}

void GraphDrawer::render_station()
{
    window.setView(leftPanel);
    sf::View unzoomed(sf::FloatRect(0, 0, 3 * window.getSize().x / 5, window.getSize().y));
    sf::Vector2i currentPos;
    sf::Text temp;

    unzoomed.setViewport(sf::FloatRect(0, 0, 0.6f, 1.0f));
    temp.setFillColor(sf::Color::White);
    temp.setFont(font);
    temp.setCharacterSize(15);
    for (auto& i : stations)
    {
        i.second.draw(window);
        if (zoom < -10) {
            currentPos = window.mapCoordsToPixel(i.second.getPosition());
            window.setView(unzoomed);
            temp.setString(i.second.getName());
            temp.setPosition(window.mapPixelToCoords(currentPos));
            window.draw(temp);
            window.setView(leftPanel);
        }
    }
}

void GraphDrawer::render_menu()
{
    sf::Text temp;
    std::string buffera;
    sf::String buffer;

    window.setView(rightPanel);
    temp.setFont(font);
    temp.setCharacterSize(12);
    temp.setFillColor(sf::Color::White);
    if (selected_station[0])
        buffera = "Station 1 : " + selected_station[0]->getName();
    else
        buffera = "Station 1 : ";
    buffer = sf::String(buffera);
    temp.setString(buffer);
    temp.setPosition(sf::Vector2f(0, 50));
    window.draw(temp);
    if (selected_station[1])
        buffera = "Station 2 : " + selected_station[1]->getName();
    else
        buffera = "Station 2 : ";
    buffer = sf::String(buffera);
    temp.setString(buffer);
    temp.setPosition(sf::Vector2f(0, 70));
    window.draw(temp);
}