#include <iostream>

#include "Graph.h"
    


int main()
{
    Graph graph;


    graph.add_vertex("paris", 120);
    graph.add_vertex("tess la boissiere", 16);
    graph.add_vertex("versailles", 98);

    graph.add_edge(16, 120, 1000);
    graph.add_edge(16, 98, 1000);


    graph.render();

    return 0;
}