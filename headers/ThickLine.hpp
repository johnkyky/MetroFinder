#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <array>



class ThickLine : public sf::Drawable
{
private:
	sf::Vector2f posSource, posDestination;
	sf::Color color;
	int thickness;
	double angle;

	std::array<sf::Vector2f, 3> triangle1;
	std::array<sf::Vector2f, 3> triangle2;

public:
	ThickLine();
	ThickLine(sf::Vector2f source, sf::Vector2f destination, sf::Color col, int thick);
	~ThickLine();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setSource(const sf::Vector2f position);
	void setDestination(const sf::Vector2f position);
	void setColor(const sf::Color col);
	void setThickness(const int thick);

private:
	void refreshPosition();
};