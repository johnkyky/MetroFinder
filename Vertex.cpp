#include "Vertex.h"


Vertex::Vertex(std::string name, unsigned int id)
{
	this->name = name;
	this->id = id;
}


Vertex::~Vertex()
{

}


void Vertex::add_edge(unsigned int idSource, unsigned int idDestination, unsigned int time)
{
	edges.push_back(Edge(idSource, idDestination, time));
}


void Vertex::render()
{
	std::cout << id << " | " << name  << " | nbr edge " << edges.size() << std::endl;
	for(auto &i : edges)
		i.render();
}