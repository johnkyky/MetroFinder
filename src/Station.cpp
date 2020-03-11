#include "Station.hpp"

Station::Station(std::string newName, int x, int y) : name(newName), position(x, y)
{

}

Station::Station()
{

}

Station::~Station()
{

}

int Station::handleEvent(const sf::RenderWindow& window, bool isClicked)
{
    sf::Mouse mouse;
    sf::Vector2i temp = mouse.getPosition(window);
    sf::Vector2f coords = window.mapPixelToCoords(temp);
    double distance = pow(coords.x - position.x, 2) + pow(coords.y - position.y, 2);

    if (distance <= ((is_hovered || is_selected) ? 100 : 25))
    {
        is_hovered = true;
        if (isClicked) 
            is_selected = !is_selected;
    }
    else
        is_hovered = false;
    return (is_hovered) ? (is_selected) ? 2 : 1 : 0;
}

void Station::draw(sf::RenderWindow& window)
{
    sf::CircleShape temp(5);

    temp.setOrigin(sf::Vector2f(5, 5));
    temp.setPosition(position);
    if (is_selected)
        temp.setFillColor(sf::Color(5, 234, 250));
    else if (is_hovered)
        temp.setFillColor(sf::Color(67, 149, 153));
    else
        temp.setFillColor(sf::Color(121, 154, 156));
    if (is_hovered || is_selected)
        temp.setScale(2, 2);
    window.draw(temp);
}

std::string Station::getName() {return name;}
sf::Vector2f Station::getPosition() {return position;}
bool Station::isHovered() {return is_hovered;}
bool Station::isSelected() {return is_selected;}