#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>    
#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>

#include "Graph.hpp"
#include "Station.hpp"
#include "ButtonTexture.hpp"
#include "ButtonColor.hpp"


class MenuDrawer
{
private:
    sf::RenderWindow& window;
    sf::Font font;

    ButtonColor swapMode;
    ButtonTexture linesButton[16];

    std::map<std::string, bool> lineIsDisplayed;
    std::list<std::string> pathString;

    const Station* source;
    const Station* destination;

public:
    enum handleRes{StartDijkstra, ModeSwap, Exit, None};
    enum mode{Selection, DisplayPath};

    MenuDrawer(sf::RenderWindow& newWindow);
    ~MenuDrawer();
    void init();

    MenuDrawer::handleRes handleEvent(sf::Event& evt);
    void render();

    bool showLine(int id);
    bool showLine(std::string line);
    void setMode(MenuDrawer::mode newMode);
    void setPathString(const std::list<std::string>&& path);

    void setFont(const sf::Font& f);

    void setSource(const Station* newSource);
    void setDestination(const Station* newDestination);
    void resetSourceDestination();

    ButtonColor& getSwapMode();

private:
    void init_buttons();
    void render_background();
    void render_destsrc();
    void render_buttons();
    void render_path();
    void  render_return();
    mode currentMode;
};