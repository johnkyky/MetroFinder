#include "Graph.h"


Graph::Graph()
{

}


Graph::~Graph()
{
	
}


void Graph::add_vertex(const std::string name, const unsigned int id)
{
	vertices.insert(std::pair<int, Vertex>(id, Vertex(name, id)));
}


void Graph::add_edge(const unsigned int id1, const unsigned int id2, const unsigned int time)
{
	std::map<unsigned int, Vertex>::iterator i;
	std::map<unsigned int, Vertex>::iterator j;
	
	i = vertices.find(id1);
	j = vertices.find(id2);

	if(i == vertices.end() || j == vertices.end())
		std::cout << "invalite id" << std::endl;
	else
	{
		vertices.find(id1)->second.add_edge(id1, id2, time);
		vertices.find(id2)->second.add_edge(id2, id1, time);
	}
}


void Graph::render()
{
	std::cout << vertices.size() << std::endl;
	for(auto &i : vertices)
		i.second.render();
}