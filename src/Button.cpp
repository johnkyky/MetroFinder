#include "Button.hpp"


Button::Button()
{

}

Button::Button(sf::Vector2f pos, sf::Vector2f dim) : dimension(dim), actived(false)
{
	this->setPosition(pos);
}


Button::~Button()
{

}


const bool Button::isActivated() {return actived;}

void Button::setActivated(const bool val) {actived = val;}