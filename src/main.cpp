#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include "GraphDrawer.hpp"
#include <map>    
#include <fstream>
#include <math.h>

int main()
{
    Graph graph;
    
    graph.load_from_file("metro.txt");
    graph.dijkstra(0, 111);
    GraphDrawer my_draw(graph, "positions.txt");
    my_draw.display();
    return 0;
}