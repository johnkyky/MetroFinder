#pragma once

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

	
#include "Button.hpp"


class ButtonColor : public Button
{
private:
	sf::Color color_idle, color_active, color_pressed, color_outline;
	sf::Color color_current;
	float thickness;
	sf::Font font;
	sf::Text text;

public:
	ButtonColor();
	ButtonColor(sf::Vector2f pos, sf::Vector2f dim);
	virtual ~ButtonColor();

	virtual bool button_pressed(sf::RenderWindow& window, const sf::Event& event);
	virtual bool button_activated(sf::RenderWindow& window, const sf::Event& event);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setPosition(const sf::Vector2f& position);
	void setIdleColor(const sf::Color color);
	void setActiveColor(const sf::Color color);
	void setPressedColor(const sf::Color color);

	void setOutlineColor(const sf::Color color);
	void setOutlineThickness(const float thick);

	void setFont(const sf::Font& f);
	void setString(const sf::String string);
	void setCharacterSize(const unsigned int size);
	void setColor(const sf::Color color);
	void refreshText();

	void setDimension(const sf::Vector2f dim);
};