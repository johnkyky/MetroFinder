#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include "GraphDrawer.hpp"

#include "ButtonColor.hpp"
#include "ButtonTexture.hpp"

int main()
{
    Graph graph;
    
    graph.load_from_file("metro.txt");
    GraphDrawer my_drawer(graph, "positions.txt");
    my_drawer.display();


    return 0;
}