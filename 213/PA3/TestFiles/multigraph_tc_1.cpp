#include "MultiGraph.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Insert Vertex" << std::endl;
    std::cout << std::endl;

    MultiGraph graph;

    std::cout << "Inserting \"A\"" << std::endl;
    graph.InsertVertex("A");
    std::cout << "Inserting \"B\"" << std::endl;
    graph.InsertVertex("B");

    graph.PrintEntireGraph();

    try
    {
        std::cout << "Inserting \"B\" again..." << std::endl;
        graph.InsertVertex("B");
    }
    catch(DuplicateVertexException& e)
    {
        std::cout << e.ToString() << std::endl;
    }

	return 0;
}