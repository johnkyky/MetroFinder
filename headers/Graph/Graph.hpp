#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <stack>
#include <climits>


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
  	std::list<Vertex> dijkstra(unsigned int source, unsigned int destination);
  
	int add_vertex(const std::string name, const unsigned int id, std::string line = "");
	int add_edge(const unsigned int id1, const unsigned int id2, const unsigned int duration, bool isMetro = true);

	std::list<std::string> vertex_to_string(std::list<Vertex>& vertices_path);

private:
	void load_line();
	std::list<Edge> dijkstra_find_valid_edge(const unsigned int id, const std::vector<unsigned int> &V);
	unsigned int dijkstra_find_indice_min_distance(unsigned int *d, const std::vector<unsigned int> &V);
	std::list<Vertex> dijkstra_get_path(const unsigned int idSource, const unsigned int idDestintion, const unsigned int *pere);
	unsigned int get_duration_edge_list(std::list<Edge>& edges, const unsigned int idSource, const unsigned int idDestination);
	std::string convert_second_to_string(const unsigned int duration);
	std::string calcul_terminus(unsigned int id1, unsigned int id2);
	void unmarkAll();
};
