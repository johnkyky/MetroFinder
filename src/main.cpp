#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include "GraphDrawer.hpp"


int main()
{
    Graph graph;
    
    graph.load_from_file("metro.txt");
    graph.dijkstra(130, 252);
    GraphDrawer my_draw(graph, "positions.txt");
    my_draw.display();
    return 0;
}