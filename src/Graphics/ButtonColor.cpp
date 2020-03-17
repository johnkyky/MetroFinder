#include "ButtonColor.hpp"


ButtonColor::ButtonColor()
{

}

ButtonColor::ButtonColor(sf::Vector2f pos, sf::Vector2f dim)
	: Button(pos, dim), color_idle(sf::Color::White), color_active(sf::Color::White),\
		color_pressed(sf::Color::White), color_outline(sf::Color::White), color_current(sf::Color::White),\
		thickness(0.f)
{	

}

ButtonColor::~ButtonColor()
{

}


bool ButtonColor::button_pressed(sf::RenderWindow& window, const sf::Event& event)
{
	if(sf::Mouse::getPosition(window).x >= this->getPosition().x &&
		sf::Mouse::getPosition(window).x <= this->getPosition().x + dimension.x &&
		sf::Mouse::getPosition(window).y >= this->getPosition().y &&
		sf::Mouse::getPosition(window).y <= this->getPosition().y + dimension.y)
	{
		if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			color_current = color_pressed;
			return true;
		}
		color_current = color_active;
		return false;
	}
	color_current = color_idle;
	return false;
}

bool ButtonColor::button_activated(sf::RenderWindow& window, const sf::Event& event)
{
	if(sf::Mouse::getPosition(window).x >= this->getPosition().x &&
		sf::Mouse::getPosition(window).x <= this->getPosition().x + dimension.x &&
		sf::Mouse::getPosition(window).y >= this->getPosition().y &&
		sf::Mouse::getPosition(window).y <= this->getPosition().y + dimension.y)
	{
		if(event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			actived = !actived;
			color_current = color_pressed;
			return true;
		}
		color_current = color_active;
		return false;
	}
	if(!actived)
		color_current = color_idle;
	return false;
}


void ButtonColor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(sf::Vector2f(this->getPosition().x + thickness, this->getPosition().y + thickness));
	rectangle.setSize(sf::Vector2f(dimension.x - 2.f * thickness, dimension.y - 2.f * thickness));
	rectangle.setFillColor(color_current);
	rectangle.setOutlineThickness(thickness);
	rectangle.setOutlineColor(color_outline);

	sf::CircleShape temp(2);
	temp.setFillColor(sf::Color::Black);
	temp.setOrigin(2, 2);
	temp.setPosition(text.getPosition());

	target.draw(rectangle);
	target.draw(text);
	target.draw(temp);
}


void ButtonColor::setPosition(const sf::Vector2f& position)
{
	sf::Transformable::setPosition(position);
	refreshText();
}

void ButtonColor::setIdleColor(const sf::Color color) {color_idle = color;}

void ButtonColor::setActiveColor(const sf::Color color) {color_active = color;}

void ButtonColor::setPressedColor(const sf::Color color) {color_pressed = color;}

void ButtonColor::setOutlineColor(const sf::Color color) {color_outline = color;}

void ButtonColor::setOutlineThickness(const float thick) 
{
	thickness = thick;
	refreshText();
}

void ButtonColor::setFont(const sf::Font& f)
{
	font = &f;
	text.setFont(f);
	refreshText();
}

void ButtonColor::setString(const sf::String string)
{
	text.setString(string);
	refreshText();
}

void ButtonColor::setCharacterSize(const unsigned int size)
{
	text.setCharacterSize(size);
	refreshText();	
}

void ButtonColor::setDimension(const sf::Vector2f dim)
{
	Button::setDimension(dim);
	refreshText();
}

void ButtonColor::setColor(const sf::Color color) {text.setFillColor(color);}

void ButtonColor::refreshText()
{
	text.setPosition((this->getPosition().x + dimension.x / 2.f) - text.getGlobalBounds().width / 2, (this->getPosition().y + dimension.y / 2.f) - text.getGlobalBounds().height/ 2);
}


void ButtonColor::setDimension(const sf::Vector2f dim)
{
	dimension = dim;
	refreshText();
}