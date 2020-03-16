#include "GraphDrawer.hpp"

using namespace std::chrono;

float mapTo(float a, float b, float c, float d, float val)
{
    return ( (val - a) / (b - a)) * (d - c) + c;
}

std::string id_to_string(const int id)
{
    const std::string convert[16] = {"1", "2", "3", "3b", "4", "5", "6", "7", "7b", "8", "9", "10", "11", "12", "13", "14"};
    return convert[id];
}

GraphDrawer::GraphDrawer(Graph& newGraph, const std::string stationPositions) : zoom(0), graph(newGraph), 
window(sf::VideoMode(1500, 1000), "MetroFinder", sf::Style::Default, sf::ContextSettings(0, 0, 4)), hovered_station(NULL), selected_station{NULL, NULL}
{
    load_station(stationPositions);
    load_color();
    font.loadFromFile("font.ttf");
    init_button();
    window.setFramerateLimit(60);
    window.setVisible(false);
    rightPanel.setSize(sf::Vector2f(double(3 * window.getSize().x / 5), window.getSize().y));
    rightPanel.setViewport(sf::FloatRect(0.4f, 0.0, 0.600f, 1.0f));
    rightPanel_center = rightPanel.getCenter();
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
    int compteur = 0;

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
    window.setView(leftPanel);
    while (window.pollEvent(evt))
    {

        if (evt.type == sf::Event::Closed)
            window.close();
        for (int i = 0; i < 16; i++)
        {
            linesButton[i].button_activated(window, evt);
        }
        switch (evt.type)
        {
            case sf::Event::MouseWheelScrolled:
                handle_zoom(evt, rightPanel, zoom);
                break;
            case sf::Event::MouseButtonPressed:
                handle_click(evt, clicked);
                break;
            case sf::Event::Resized:
                rightPanel.setCenter(double(3 * window.getSize().x / 10), window.getSize().y/2);
                rightPanel.setSize(sf::Vector2f(double(3 * window.getSize().x / 5), window.getSize().y));
                leftPanel.setCenter(double(window.getSize().x / 5), window.getSize().y/2);
                leftPanel.setSize(sf::Vector2f(double(2 * window.getSize().x / 5), window.getSize().y));
            default :
                break;
        }
    }
    for (int i = 0; i < 16; i++)
    {
        showLine[id_to_string(i)] = !linesButton[i].isActivated();
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
    render_line();
    render_station();
    render_menu();
}

// Fonctions d'handle


void GraphDrawer::init_button()
{
    std::stringstream stringCreator;
    std::string buffer;

    for (int i = 0; i < 16; i++) {
        showLine[id_to_string(i)] = true;
        linesButton[i].setActivated(false);
    }
    for (int i = 0; i < 16; i++) {
        stringCreator << "ligne_" << id_to_string(i) << ".png";
        linesButton[i].setIdleTexture(stringCreator.str());
        linesButton[i].setPosition(sf::Vector2f(5 + i * 48, 10));
        linesButton[i].setDimension(sf::Vector2f(32.f, 32.f));
        stringCreator.str("");
    }
}

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
                
                std::list<Vertex> vertexBuffer = graph.dijkstra(selected_station[0]->getId(), selected_station[1]->getId());
                std::list<std::string> stringBuffer = graph.vertex_to_string(vertexBuffer);
                for(auto& i : stringBuffer)
                    std::cout << i << "\n";
                printf("\n\n");
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
    ThickLine line;

    line.setThickness(4);
    window.setView(rightPanel);
    for (auto& i : temp)
    {
        std::string buffer = i.second.getName();
        if (showLine[i.second.getLine()])
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

void GraphDrawer::render_menu()
{
    sf::RenderTexture texture;
    sf::Sprite menuSprite;

    window.setView(leftPanel);
    texture.create(2 * 1920 / 5, 1080);
    render_menu_background(texture);
    render_menu_destination(texture);
    render_menu_boutons(texture);
    for (int i = 0; i < 16; i++)
        texture.draw(linesButton[i]);
    texture.display();
    menuSprite.setTexture(texture.getTexture());
    menuSprite.setScale(leftPanel.getSize().x / texture.getSize().x, leftPanel.getSize().y / texture.getSize().y);
    window.draw(menuSprite);
    
}


void GraphDrawer::render_menu_background(sf::RenderTexture& texture)
{
    sf::RectangleShape rec;

    rec.setPosition(0, 0);
    rec.setFillColor(sf::Color(101, 180, 229));
    rec.setSize(sf::Vector2f(texture.getSize().x, texture.getSize().y));
    texture.draw(rec);

    rec.setPosition(texture.getSize().x - 5, 0);
    rec.setSize(sf::Vector2f(5, texture.getSize().y));
    rec.setFillColor(sf::Color::White);
    texture.draw(rec);
}

void GraphDrawer::render_menu_destination(sf::RenderTexture& texture)
{
    sf::Text temp;
    std::string buffer;

    temp.setFont(font);
    temp.setCharacterSize(20);
    temp.setFillColor(sf::Color(53, 48, 54));
    temp.setString("Depart");
    temp.setPosition(sf::Vector2f(texture.getSize().x / 2 - temp.getGlobalBounds().width / 2, 100));
    temp.setStyle(sf::Text::Bold);
    texture.draw(temp);
    temp.setStyle(sf::Text::Regular);
    if (selected_station[0]) {
        temp.setString(selected_station[0]->getName());
        temp.setPosition(sf::Vector2f(texture.getSize().x / 2 - temp.getGlobalBounds().width / 2, 125));
        texture.draw (temp);temp.setStyle(sf::Text::Regular);    
    }

    temp.setString("Destination");
    temp.setStyle(sf::Text::Bold);
    temp.setPosition(sf::Vector2f(texture.getSize().x / 2 - temp.getGlobalBounds().width / 2, 150));
    texture.draw(temp);
    temp.setStyle(sf::Text::Regular);
    if (selected_station[1]) {
        temp.setString(selected_station[1]->getName());
        temp.setPosition(sf::Vector2f(texture.getSize().x / 2 - temp.getGlobalBounds().width / 2, 175));
        texture.draw (temp);
    }
}

void GraphDrawer::render_menu_boutons(sf::RenderTexture& texture)
{

}