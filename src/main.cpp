#include <iostream>

#include "Graph.hpp"
    


int main()
{
    Graph graph;
    //graph.load_from_file("metro.txt");

    graph.add_vertex("nbr0", 0);
    graph.add_vertex("nbr1", 1);
    graph.add_vertex("nbr2", 2);
    graph.add_vertex("nbr3", 3);
    graph.add_vertex("nbr4", 4);

    graph.add_edge(0, 1, 1);
    graph.add_edge(0, 3, 2);
    graph.add_edge(0, 4, 6);
    graph.add_edge(1, 2, 3);
    graph.add_edge(1, 3, 4);
    graph.add_edge(2, 4, 1);


    graph.render();

    graph.dijkstra(4, 3);

    return 0;
}