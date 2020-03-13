#include <iostream>
#include <SFML/Graphics.hpp>

#include "ThickLine.hpp"



int main()
{
    sf::RenderWindow window(sf::VideoMode(720, 480), "SFML works!");

    ThickLine demo[10000];
    for (int i = 0; i < 10000; ++i)
    {
        demo[i].setSource(sf::Vector2f(360.f, 240.f));
        demo[i].setDestination(sf::Vector2f(300.f, 300.f));
        demo[i].setColor(sf::Color::Cyan);
        demo[i].setThickness(40);
    }

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

        for (int i = 0; i < 10000; ++i)
            demo[i].setDestination(pos);         


        window.clear();

        for (int i = 0; i < 10000; ++i)
            window.draw(demo[i]);

        window.display();
    }

    return 0;
}