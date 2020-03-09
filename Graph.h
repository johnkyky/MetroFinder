#pragma once

#include <iostream>
#include <string>
#include <map>


#include "Vertex.h"



class Graph
{
private:
	std::map<unsigned int, Vertex> vertices;


public:
	Graph();
	~Graph();

	void add_vertex(const std::string name, const unsigned int id);
	void add_edge(const unsigned int id1, const unsigned int id2, const unsigned int time);

	void render();
};
