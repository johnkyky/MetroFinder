#include <iostream>

#include "Graph.hpp"
    


int main()
{
    Graph graph;
    graph.load_from_file("metro.txt");
    graph.render();
    return 0;
}