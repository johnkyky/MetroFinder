#pragma once

#include <iostream>
#include <string>
#include <list>

#include "Edge.hpp"



class Vertex
{
private:
	std::string name;
	unsigned int id;
	std::list<Edge> edges;

public:
	Vertex(const std::string name, const unsigned int id);
	~Vertex();

	void add_edge(const unsigned int source, const unsigned int destination, const unsigned int time);

	void render();
};