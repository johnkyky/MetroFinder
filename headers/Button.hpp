#pragma once

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"


class Button
	: public sf::Transformable, public sf::Drawable
{
public:
	Button();
	Button(sf::Vector2f pos, sf::Vector2f dim);
	virtual ~Button();

	virtual bool button_pressed(sf::RenderWindow& window, const sf::Event& event) = 0;
	virtual bool button_activated(sf::RenderWindow& window, const sf::Event& event) = 0;

	const bool isActivated();
	void setActivated(const bool val);

	void setDimension(const sf::Vector2f dim);

protected:
	sf::Vector2f dimension;
	bool actived;
};	