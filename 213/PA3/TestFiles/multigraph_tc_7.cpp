#include "MultiGraph.h"
#include "Exceptions.h"
#include <iostream>

void InsertEdge(MultiGraph& graph,
                const std::string& E,
                const std::string& V0,
                const std::string& V1,
                float w0, float w1)
{
    std::cout << "Inserting \"" << E << "\" (w0: "
              << w0 << ", w1: " << w1 << ") to "<< V0 << "->" << V1 << std::endl;
    graph.AddEdge(E, V0, V1, w0, w1);
}

int main()
{
    std::cout << "Testing Bidir Edge Count" << std::endl;
    std::cout << std::endl;

    MultiGraph graph;

    std::cout << "Inserting \"A\"" << std::endl;
    graph.InsertVertex("A");
    std::cout << "Inserting \"B\"" << std::endl;
    graph.InsertVertex("B");
    std::cout << "Inserting \"C\"" << std::endl;
    graph.InsertVertex("C");
    std::cout << "Inserting \"D\"" << std::endl;
    graph.InsertVertex("D");
    std::cout << "Inserting \"E\"" << std::endl;
    graph.InsertVertex("E");
    std::cout << "Inserting \"F\"" << std::endl;
    graph.InsertVertex("F");

    // Bidir Edge
    InsertEdge(graph, "E01", "A", "B", 2.3f, 4.12f);
    InsertEdge(graph, "E01", "B", "A", 1.2f, 2.12f);
    
    // Non Bidir Edges
    InsertEdge(graph, "E50", "C", "E", 0.2f, 0.02f);
    InsertEdge(graph, "E55", "E", "C", 0.2f, 0.02f);
    InsertEdge(graph, "E90", "E", "F", 0.1f, 4.122f);
    
    InsertEdge(graph, "E90", "A", "E", 0.1f, 4.122f);
    InsertEdge(graph, "E90", "E", "B", 0.1f, 4.122f);

    graph.PrintEntireGraph();

    std::cout << "Calling BidirEdgeCount" << std::endl;
    int amount = graph.BiDirectionalEdgeCount();
    std::cout << "BidirEdge Count Amount: " << amount << std::endl;

    std::cout << "-------------------------------" << std::endl;

    // Add two more bidir edge
    InsertEdge(graph, "E90", "E", "A", 0.1f, 4.122f);
    InsertEdge(graph, "E90", "B", "E", 0.1f, 4.122f);
    
    std::cout << "Calling BidirEdgeCount" << std::endl;
    amount = graph.BiDirectionalEdgeCount();
    std::cout << "BidirEdge Count Amount: " << amount << std::endl;

	return 0;
}