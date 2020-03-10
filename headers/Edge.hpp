#pragma once

#include <iostream>
#include <string>
#include <vector>





class Edge
{
private:
	unsigned int idSource, idDestination;
	unsigned int duration;
	int color = 0;
	bool isMetro = true;

public:
	Edge();

	//list d'init
	Edge(const unsigned int source, const unsigned int destination, const unsigned int duration, bool isMetro = true);
	~Edge();

	unsigned int getSource();
	void setSource(const unsigned int val);

	unsigned int getDestination();
	void setDestination(const unsigned int val);

	unsigned int getDuration();
	void setDuration(const unsigned int val);

	bool getMetro();
	void setMetro(bool val);

	void print();
};
