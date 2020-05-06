#include "Vertex.hpp"

Vertex::Vertex() : marked(false)
{
	is_terminus = false;
}

Vertex::Vertex(const std::string nname, const unsigned int nid, const std::string nline) : name(nname), line(nline), id(nid), marked(0), is_terminus(false)
{

}

Vertex::~Vertex()
{

}

std::list<Edge>& Vertex::getEdges() {return edges;}
Edge& Vertex::getEdge(int id)
{
	for (Edge& i : edges)
	{
		if (i.getDestination() == id)
		{
			return i;
		}
	}
	throw std::runtime_error("Invalid argument");
}

unsigned int Vertex::getId() {return id;}

void Vertex::setId(const int unsigned val) {id = val;}

std::string Vertex::getLine() {return line;}

void Vertex::setLine(const std::string val) {line = val;}

std::string Vertex::getName() {return name;}

void Vertex::setName(std::string val) {name = val;}


void Vertex::add_edge(unsigned int idSource, unsigned int idDestination, unsigned int duration, bool isMetro)
{
	edges.emplace_front(idSource, idDestination, duration, isMetro);
}


void Vertex::add_edge(Edge val) {edges.push_front(val);}
int Vertex::getMarked() {return marked;}
void Vertex::setMarked(int val) {marked = val;}
void Vertex::setTerminus(bool val) {is_terminus = val;}
bool Vertex::getTerminus() {return is_terminus;}