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
	bool is_terminus;	   // bool pour separer les stations terminus et non terminus
	int marked;


public:
	Vertex();
	Vertex(const std::string name, const unsigned int id, const std::string line = "Undefined");
	~Vertex();

	///return la liste des arretes d'un sommet
	std::list<Edge>& getEdges();
	///return l'arrete qui va du sommet this au sommet id 
	Edge& getEdge(unsigned int id);

	///ajoute une arrete a sommet en construisant l'objet
	void add_edge(const unsigned int source, const unsigned int destination, const unsigned int duration, bool isMetro = true);
	///ajoute une arrete au sommet (objet existant deja)
	void add_edge(Edge val);
	
	///Getter Setter
	unsigned int getId();
	void setId(const unsigned int val);

	std::string getLine();
	void setLine(const std::string val);

	std::string getName();
	void setName(std::string val);

	int getMarked();
	void setMarked(int val);

	void setTerminus(bool val);
	bool getTerminus();
};