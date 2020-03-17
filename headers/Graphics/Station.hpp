#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <math.h>


class Station
{
private:
    std::string name;
    sf::Vector2f position;
    bool is_hovered = false;
    bool is_selected = false;
    enum stationSize {size_basic = 5, size_highligted = 10};
    int id;

public:
    enum status{Hovered, Selected, Unselected,None};

    Station(std::string newName, int x, int y);
    Station();
    ~Station();
    status handleEvent(const sf::RenderWindow& window, const bool isClicked = false);
    void draw(sf::RenderWindow& window);

    std::string getName() const;
    sf::Vector2f getPosition() const;
    bool isHovered() const;
    bool isSelected() const;
    void setSelected(bool val);
    int getId() const;
    void setId(int val);
};