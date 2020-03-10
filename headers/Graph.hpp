#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <stack>


#include "Vertex.hpp"



class Graph
{
private:
	std::map<unsigned int, Vertex> vertices;


public:
	Graph(std::string fileName);
	Graph();
	~Graph();

	int load_from_file(std::string fileName);

	std::map<unsigned int, Vertex>& getVertices();
	int add_vertex(const std::string name, const unsigned int id, std::string line = "");
	int add_edge(const unsigned int id1, const unsigned int id2, const unsigned int duration, bool isMetro = true);

	void render();
private:
	void load_line();

};
