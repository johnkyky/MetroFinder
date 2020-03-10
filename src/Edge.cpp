#include "Edge.hpp"


Edge::Edge()
{

}

Edge::Edge(const unsigned int source, const unsigned int destination, const unsigned int duration, bool isMetro)
{
	idSource = source;
	idDestination = destination;
	this->duration = duration;
}


Edge::~Edge()
{
	
}

unsigned int Edge::getSource()
{
	return idSource;
}

void Edge::setSource(const unsigned int val)
{
	idSource = val;
}

unsigned int Edge::getDestination()
{
	return idDestination;
}

void Edge::setDestination(const unsigned int val)
{
	idDestination = val;
}

unsigned int Edge::getDuration()
{
	return duration;
}

void Edge::setDuration(const unsigned int val)
{
	duration = val;
}

bool Edge::getMetro()
{
	return isMetro;
}

void Edge::setMetro(bool val)
{
	isMetro = val;
}


void Edge::print()
{
	std::cout << "->" << idSource << " <-" << idDestination << " | duration " << duration << std::endl;
}