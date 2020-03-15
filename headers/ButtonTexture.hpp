#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"

	
#include "Button.hpp"


class ButtonTexture : public Button
{
private:
	sf::Texture texture_idle, texture_active, texture_pressed;
	sf::Sprite sprite_idle, sprite_active, sprite_pressed, sprite_current;

public:
	ButtonTexture();
	ButtonTexture(sf::Vector2f pos, sf::Vector2f dim);
	virtual ~ButtonTexture();

	virtual bool button_pressed(sf::Window& window, const sf::Event& event);
	virtual bool button_activated(sf::Window& window, const sf::Event& event);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setPosition(const sf::Vector2f& position);

	void setIdleTexture(const std::string path);
	void setIdleTexture(const std::string path, const sf::IntRect rect);
	void setActiveTexture(const std::string path);
	void setActiveTexture(const std::string path, const sf::IntRect rect);
	void setPressedTexture(const std::string path);
	void setPressedTexture(const std::string path, const sf::IntRect rect);

private:
	void refreshSprite();
};