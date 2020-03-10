#include "Vertex.hpp"

Vertex::Vertex()
{

}

Vertex::Vertex(const std::string nname, const unsigned int nid, const std::string nline) : name(nname), line(nline), id(nid)
{

}

Vertex::~Vertex()
{

}

std::list<Edge>& Vertex::getEdges()
{
	return edges;
}

unsigned int Vertex::getId()
{
	return id;
}

void Vertex::setId(const int unsigned val)
{
	id = val; 
}

std::string Vertex::getLine()
{
	return line;
}

void Vertex::setLine(const std::string val)
{
	line = val;
}

std::string Vertex::getName()
{
	return name;
}

void Vertex::setName(std::string val)
{
	name = val;
}


void Vertex::add_edge(unsigned int idSource, unsigned int idDestination, unsigned int duration, bool isMetro)
{
	edges.emplace_front(idSource, idDestination, duration, isMetro);
}


void Vertex::add_edge(Edge val)
{
	edges.push_front(val);
}


void Vertex::print()
{
	printf("\n[Station] %s : ligne : %s connectée a :\n", name.c_str(), line.c_str());
	for(auto& i : edges)
	{
		printf("\t%4i en %4i secondes", i.getDestination(), i.getDuration());
		if (!i.getMetro())
			printf(" via marche a pieds");
		printf(".\n");
	}
}