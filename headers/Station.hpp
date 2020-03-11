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

public:
    Station(std::string newName, int x, int y);
    Station();
    ~Station();
    int handleEvent(const sf::RenderWindow& window, bool isClicked = false);
    void draw(sf::RenderWindow& window);

    std::string getName();
    sf::Vector2f getPosition();
    bool isHovered();
    bool isSelected();
};