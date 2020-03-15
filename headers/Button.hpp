#pragma once

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

class Button
	: public sf::Transformable, public sf::Drawable
{
public:
	Button();
	Button(sf::Vector2f pos, sf::Vector2f dim);
	virtual ~Button();

	virtual bool button_pressed(sf::Window& window, const sf::Event& event) = 0;
	virtual bool button_activated(sf::Window& window, const sf::Event& event) = 0;

	bool isActivated();
	void setActivated(const bool val);

protected:
	sf::Vector2f dimension;
	bool actived;
};	