#pragma once

#include <iostream>
#include <string>
#include <vector>





class Edge
{
private:
	unsigned int idSource, idDestination;
	unsigned int time;
	int color = 0;
	bool isMetro = true;

public:
	Edge(const unsigned int source, const unsigned int destination, const unsigned int time);
	~Edge();

	void render();
};
