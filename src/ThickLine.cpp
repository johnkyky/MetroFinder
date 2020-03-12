#include "ThickLine.hpp"



ThickLine::ThickLine()
{
	
}

ThickLine::ThickLine(sf::Vector2f source, sf::Vector2f destination, sf::Color col, int thick)
	: posSource(source), posDestination(destination), color(col), thickness(thick)
{
	setSource(source);
	setDestination(destination);
}

ThickLine::~ThickLine()
{

}



void ThickLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::VertexArray tri1(sf::Triangles, 3);
	sf::VertexArray tri2(sf::Triangles, 3);

	tri1[0].position = triangle1[0];
	tri1[1].position = triangle1[1];
	tri1[2].position = triangle1[2];
	tri2[0].position = triangle2[0];
	tri2[1].position = triangle2[1];
	tri2[2].position = triangle2[2];

	tri1[0].color = color;
	tri1[1].color = color;
	tri1[2].color = color;
	tri2[0].color = color;
	tri2[1].color = color;
	tri2[2].color = color;

	target.draw(tri1);
	target.draw(tri2);
}


void ThickLine::setSource(sf::Vector2f position)
{
	posSource = position;
	refreshPosition();
}

void ThickLine::setDestination(sf::Vector2f position)
{
	posDestination = position;
	refreshPosition();
}

void ThickLine::setColor(sf::Color col)
{
	color = col;
}

void ThickLine::setThickness(const int thick)
{
	thickness = thick;
}


void ThickLine::refreshPosition()
{
	angle = atan((posDestination.y - posSource.y) / (posDestination.x - posSource.x));

	triangle1[0] = sf::Vector2f(posSource.x - (thickness / 2) * sin(angle),
								posSource.y + (thickness / 2) * cos(angle));
	triangle1[1] = sf::Vector2f(posSource.x + (thickness / 2) * sin(angle),
								posSource.y - (thickness / 2) * cos(angle));
	triangle1[2] = sf::Vector2f(posDestination.x + (thickness / 2) * sin(angle),
								posDestination.y - (thickness / 2) * cos(angle));
	
	triangle2[0] = sf::Vector2f(posDestination.x - (thickness / 2) * sin(angle),
								posDestination.y + (thickness / 2) * cos(angle));
	triangle2[1] = sf::Vector2f(posDestination.x + (thickness / 2) * sin(angle),
								posDestination.y - (thickness / 2) * cos(angle));
	triangle2[2] = sf::Vector2f(posSource.x - (thickness / 2) * sin(angle),
								posSource.y + (thickness / 2) * cos(angle));
}
