#include "Edge.hpp"


Edge::Edge(const unsigned int source, const unsigned int destination, const unsigned int time)
{
	idSource = source;
	idDestination = destination;
	this->time = time;
}


Edge::~Edge()
{
	
}


void Edge::render()
{
	std::cout << "->" << idSource << " <-" << idDestination << " | time " << time << std::endl;
}