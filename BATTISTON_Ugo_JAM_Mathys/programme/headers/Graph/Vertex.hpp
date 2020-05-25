#pragma once

#include <iostream>
#include <string>
#include <list>

#include "Edge.hpp"



class Vertex
{
private:
	std::list<Edge> edges; // connexions sortantes
	std::string name;      // noms de la station/quais, sans accents
	std::string line;      // nom de la ligne
	unsigned int id;       // id unique
	int marked;
	bool is_terminus;


public:
	Vertex();
	Vertex(const std::string name, const unsigned int id, const std::string line = "Undefined");
	~Vertex();

	std::list<Edge>& getEdges();
	Edge& getEdge(unsigned int id);

	unsigned int getId();
	void setId(const unsigned int val);

	std::string getLine();
	void setLine(const std::string val);
	std::string getName();
	void setName(std::string val);

	void add_edge(const unsigned int source, const unsigned int destination, const unsigned int duration, bool isMetro = true);
	void add_edge(Edge val);

	int getMarked();
	void setMarked(int val);
	void setTerminus(bool val);
	bool getTerminus();
};