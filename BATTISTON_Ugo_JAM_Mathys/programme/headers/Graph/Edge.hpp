#pragma once

#include <iostream>
#include <string>
#include <vector>


class Edge
{
private:
	unsigned int idSource, idDestination; // Les aretes sont orienté
	unsigned int duration;                // Durée du trajet, poids de l'arrete
	bool isMetro = true;                  // si la connexions corresponds a un trajet a pieds ou a métro

public:
	Edge();
	Edge(const unsigned int source, const unsigned int destination, const unsigned int duration, bool isMetro = true);
	~Edge();

	///Getter Setter
	unsigned int getSource();
	void setSource(const unsigned int val);

	unsigned int getDestination();
	void setDestination(const unsigned int val);

	unsigned int getDuration();
	void setDuration(const unsigned int val);

	bool getMetro();
	void setMetro(bool val);
};
