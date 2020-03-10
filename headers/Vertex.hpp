#pragma once

#include <iostream>
#include <string>
#include <list>

#include "Edge.hpp"



class Vertex
{
private:
	std::list<Edge> edges;
	std::string name;
	std::string line;
	unsigned int id;

public:
	Vertex();
	Vertex(const std::string name, const unsigned int id, const std::string line = "Undefined");
	~Vertex();

	std::list<Edge>& getEdges();

	unsigned int getId();
	void setId(const unsigned int val);

	std::string getLine();
	void setLine(const std::string val);
	std::string getName();
	void setName(std::string val);

	void add_edge(const unsigned int source, const unsigned int destination, const unsigned int duration, bool isMetro = true);
	void add_edge(Edge val);

	void print();
};