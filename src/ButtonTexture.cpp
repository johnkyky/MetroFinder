#include "ButtonTexture.hpp"


ButtonTexture::ButtonTexture()
{

}

ButtonTexture::ButtonTexture(sf::Vector2f pos, sf::Vector2f dim) : Button(pos, dim)
{	
	refreshSprite();
}

ButtonTexture::~ButtonTexture()
{

}


bool ButtonTexture::button_pressed(sf::RenderWindow& window, const sf::Event& event)
{
	if(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x >= this->getPosition().x &&
		window.mapPixelToCoords(sf::Mouse::getPosition(window)).x <= this->getPosition().x + dimension.x &&
		window.mapPixelToCoords(sf::Mouse::getPosition(window)).y >= this->getPosition().y &&
		window.mapPixelToCoords(sf::Mouse::getPosition(window)).y <= this->getPosition().y + dimension.y)
	{
		if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sprite_current = sprite_pressed;
			return true;
		}
		sprite_current = sprite_active;
		return false;
	}
	sprite_current = sprite_idle;
	return false;
}

bool ButtonTexture::button_activated(sf::RenderWindow& window, const sf::Event& event)
{
	if(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x >= this->getPosition().x &&
		window.mapPixelToCoords(sf::Mouse::getPosition(window)).x <= this->getPosition().x + dimension.x &&
		window.mapPixelToCoords(sf::Mouse::getPosition(window)).y >= this->getPosition().y &&
		window.mapPixelToCoords(sf::Mouse::getPosition(window)).y <= this->getPosition().y + dimension.y)
	{
		if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			actived = !actived;
			sprite_current = sprite_pressed;
			return true;
		}
		sprite_current = sprite_active;
		return false;
	}
	if (!actived)
		sprite_current = sprite_idle;
	return false;
}


void ButtonTexture::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_current);
}


void ButtonTexture::setPosition(const sf::Vector2f& position)
{
	sf::Transformable::setPosition(position);
	refreshSprite();
}


void ButtonTexture::setIdleTexture(const std::string path)
{
	std::cout << "Loading texture " << path << "...\n";
	if (texture_idle.loadFromFile(path) == false) 
	{
		std::cout << "\tFailed to load texture ! exiting\n";
		exit(1);
	}
	sprite_idle.setTexture(texture_idle);

	sprite_current = sprite_idle;
}

void ButtonTexture::setIdleTexture(const std::string path, const sf::IntRect rect)
{
	texture_idle.loadFromFile(path, rect);
	sprite_idle.setTexture(texture_idle);

	sprite_current = sprite_idle;
}


void ButtonTexture::setActiveTexture(const std::string path)
{
	texture_active.loadFromFile(path);
	sprite_active.setTexture(texture_active);
}

void ButtonTexture::setActiveTexture(const std::string path, const sf::IntRect rect)
{
	texture_active.loadFromFile(path, rect);
	sprite_active.setTexture(texture_active);
}


void ButtonTexture::setPressedTexture(const std::string path)
{
	texture_pressed.loadFromFile(path);
	sprite_pressed.setTexture(texture_pressed);
}


void ButtonTexture::setPressedTexture(const std::string path, const sf::IntRect rect)
{
	texture_pressed.loadFromFile(path, rect);
	sprite_pressed.setTexture(texture_pressed);
}


void ButtonTexture::refreshSprite()
{
	sprite_idle.setPosition(this->getPosition());
	sprite_active.setPosition(this->getPosition());
	sprite_pressed.setPosition(this->getPosition());
	sprite_current.setPosition(this->getPosition());
}