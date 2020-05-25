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

Station::status Station::handleEvent(const sf::RenderWindow& window, const bool isClicked)
{
    sf::Mouse mouse;
    sf::Vector2i temp = mouse.getPosition(window);
    sf::Vector2f coords = window.mapPixelToCoords(temp);
    double distance = pow(coords.x - position.x, 2) + pow(coords.y - position.y, 2);

    if (distance <= ((is_hovered || is_selected) ? 100 : 25))
    {
        is_hovered = true;
        if (isClicked) {
            is_selected = !is_selected;
            return is_selected ? status::Selected : status::Unselected;
        }
        return status::Hovered;
    }
    else
        is_hovered = false;
    return status::None;
}

void Station::draw(sf::RenderWindow& window)
{
    sf::CircleShape temp(size_basic);

    temp.setOrigin(sf::Vector2f(size_basic, size_basic));
    temp.setPosition(position);
    temp.setOutlineColor(sf::Color::Black);
    temp.setOutlineThickness(1);
    if (is_selected)
        temp.setFillColor(sf::Color(0,166,251));
    else if (is_hovered)
        temp.setFillColor(sf::Color(5,130,202));
    else
        temp.setFillColor(sf::Color(118,123,145));
    if (is_hovered || is_selected)
        temp.setScale(2, 2);
    window.draw(temp);
}

std::string Station::getName() const {return name;}
sf::Vector2f Station::getPosition() const {return position;}
bool Station::isHovered() const {return is_hovered;}
bool Station::isSelected() const {return is_selected;}
void Station::setSelected(bool val){is_selected = val;}
int Station::getId() const {return id;};
void Station::setId(int val){id = val;};