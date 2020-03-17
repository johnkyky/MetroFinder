#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>    
#include <unordered_map>
#include <math.h>
#include <chrono>
#include <memory>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Graph.hpp"
#include "Station.hpp"
#include "ThickLine.hpp"
#include "MenuDrawer.hpp"

class GraphDrawer
{
private:
    double zoom;
    Graph& graph;

    sf::View leftPanel;
    sf::View rightPanel;
    sf::RenderWindow window;
    sf::Font font;

    std::unordered_map<std::string, sf::Color>      lignesColor;
    std::unordered_map<std::string, Station>        stations;
    MenuDrawer menu;

    Station* hovered_station;
    Station* selected_station[2];

public:
    GraphDrawer(Graph& newGraph, const std::string stationPositions);
    ~GraphDrawer();

    void setSize(const unsigned int x, const unsigned int y);
    void setGraph(Graph& newGraph);

    void display();

private:
    void init_button();

    int load_station(const std::string fileName);
    void load_color();
    void handleEvent();
    void update();
    void render();

    void zoomToward(sf::Vector2i target, double zoom);
    void handle_zoom(sf::Event evt, sf::View& view, double& zoom);
    void handle_click(sf::Event evt, bool& clicked);
    void handle_station(sf::Event evt, const bool clicked);

    void render_station();
    void render_line();

    void render_menu();
    void render_menu_background(sf::RenderTexture& texture);
    void render_menu_destination(sf::RenderTexture& texture);
    void render_menu_boutons(sf::RenderTexture& texture);
};