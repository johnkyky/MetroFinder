#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include "GraphDrawer.hpp"


int main()
{
    Graph graph;
    
    graph.load_from_file("metro.txt");
    std::list<Vertex> vertex = graph.dijkstra(110, 142);
    std::list<std::string> demo = graph.vertex_to_string(vertex);
    for(auto& i : demo)
    	std::cout << i << "\n";



    //GraphDrawer my_draw(graph, "positions.txt");
    //my_draw.display();
    return 0;
}