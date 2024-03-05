#include "MultiGraph.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Remove Vertex" << std::endl;
    std::cout << std::endl;

    MultiGraph graph;

    std::cout << "Inserting \"A\"" << std::endl;
    graph.InsertVertex("A");
    std::cout << "Inserting \"B\"" << std::endl;
    graph.InsertVertex("B");
    std::cout << "Inserting \"C\"" << std::endl;
    graph.InsertVertex("C");

    graph.PrintEntireGraph();

    std::cout << "Removing \"A\"" << std::endl;
    graph.RemoveVertex("A");

    try
    {
        std::cout << "Removing \"A\" again..." << std::endl;
        graph.RemoveVertex("A");
    }
    catch(VertexNotFoundException& e)
    {
        std::cout << e.ToString() << std::endl;
    }

	return 0;
}