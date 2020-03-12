#include <iostream>
#include <SFML/Graphics.hpp>

#include "ThickLine.hpp"



int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 480), "SFML works!");

    ThickLine demo(sf::Vector2f(360.f, 240.f), sf::Vector2f(300.f, 300.f), sf::Color::Cyan, 40);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f pos = sf::Vector2f(1.f, 1.f);
        pos.x = (float)sf::Mouse::getPosition(window).x;
        pos.y = (float)sf::Mouse::getPosition(window).y;

        demo.setSource(pos);

        window.clear();

        window.draw(demo);

        window.display();
    }

    while(1)
    {
        sf::Vector2f pos = sf::Vector2f(1.f, 1.f);
        demo.setDestination(pos);
    }

    return 0;
}