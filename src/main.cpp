#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include "GraphDrawer.hpp"


int main()
{
    Graph graph;
    
    graph.load_from_file("metro.txt");
    std::list<Vertex> vertex = graph.dijkstra(110, 142);
    graph.vertex_to_string(vertex);

    GraphDrawer my_draw(graph, "positions.txt");
    my_draw.display();
    return 0;
}