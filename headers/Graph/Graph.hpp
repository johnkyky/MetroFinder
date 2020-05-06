#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <stack>
#include <climits>
#include <memory>


#include "Vertex.hpp"



class Graph
{
private:
	std::map<unsigned int, Vertex> vertices;


public:
	Graph(std::string fileName);
	Graph();
	~Graph();

	// charge un graph à partir d'un fichier
	int load_from_file(std::string fileName);

	// return la map des <indice, sommet> du graph
  	std::map<unsigned int, Vertex>& getVertices();

  	// algo de pathfinding return la list des sommets dans l'ordre de passage
  	std::list<Vertex> dijkstra(unsigned int source, unsigned int destination);
  	
  	// ajoute un sommet au graph
	int add_vertex(const std::string name, const unsigned int id, std::string line = "");
	
	// ajoute une arrete au graph
	int add_edge(const unsigned int id1, const unsigned int id2, const unsigned int duration, bool isMetro = true);

	// permet de convertir la liste des sommets du pathfinding en une liste de string des points de passages
	std::list<std::string> vertex_to_string(std::list<Vertex>& vertices_path);

private:
	// regroupe les somment en lignes grace au terminus
	void spread_line();
	// return la liste valide d'arrete utilisé dans le dijkstra
	std::list<Edge> dijkstra_find_valid_edge(const unsigned int id, const std::vector<unsigned int> &V);
	// return l'indice min de distance utilisé dans le dijkstra
	unsigned int dijkstra_find_indice_min_distance(unsigned int *d, const std::vector<unsigned int> &V);
	// construit et return la liste des sommets du pathfinding
	std::list<Vertex> dijkstra_get_path(const unsigned int idSource, const unsigned int idDestintion, const unsigned int *pere);
	// return le poid d'une arrete en cherchant les 2 sommets dans une liste grace au 2 id des sommets
	unsigned int get_duration_edge_list(std::list<Edge>& edges, const unsigned int idSource, const unsigned int idDestination);
	// converti des seconde en h:m:s
	std::string convert_second_to_string(const unsigned int duration);
	// return le nom du terminus de id1 et id2 (sens id1->id2)
	std::string calcul_terminus(unsigned int id1, unsigned int id2);
	// reinitialise le marcage de tous les sommets du graph
	void unmarkAll();
};
