#include "MultiGraph.h"
#include "Exceptions.h"
#include <iostream>

int main()
{
    std::cout << "Testing Add Edge" << std::endl;
    std::cout << std::endl;

    MultiGraph graph;

    std::cout << "Inserting \"A\"" << std::endl;
    graph.InsertVertex("A");
    std::cout << "Inserting \"B\"" << std::endl;
    graph.InsertVertex("B");
    std::cout << "Inserting \"C\"" << std::endl;
    graph.InsertVertex("C");
    
    std::cout << "Inserting \"E0\" (w0: 0.0, w1: 0.1) to A->B" << std::endl;
    graph.AddEdge("E0", "A", "B", 0.0f, 0.1f);
    std::cout << "Inserting \"E1\" (w0: 0.0, w1: 0.1) to A->B" << std::endl;
    graph.AddEdge("E1", "A", "B", 0.0f, 0.1f);
    std::cout << "Inserting \"E2\" (w0: 0.0, w1: 0.1) to B->A" << std::endl;
    graph.AddEdge("E2", "B", "A", 0.0f, 0.1f);
    
    std::cout << "Inserting \"E0\" (w0: 0.0, w1: 0.1) to C->A" << std::endl;
    graph.AddEdge("E0", "C", "A", 0.0f, 0.1f);
    
    graph.PrintEntireGraph();

    try
    {
        std::cout << "Inserting \"E0\" (w0: 0.0, w1: 99.1) to A->B again..." << std::endl;
        graph.AddEdge("E0", "A", "B", 0.0f, 99.1f);
    }
    catch(SameNamedEdgeException& e)
    {
        std::cout << e.ToString() << std::endl;
    }

	return 0;
}