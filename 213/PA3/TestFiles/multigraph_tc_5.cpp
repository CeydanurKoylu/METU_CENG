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
    std::cout << "Testing Heuristic Shortest Path" << std::endl;
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

    InsertEdge(graph, "E01", "A", "B", 2.3f, 4.12f);
    InsertEdge(graph, "E20", "B", "C", 1.2f, 2.12f);
    InsertEdge(graph, "E50", "C", "E", 0.2f, 0.02f);
    InsertEdge(graph, "E90", "E", "F", 0.1f, 4.122f);

    graph.PrintEntireGraph();

    std::cout << "Calling shortest path from A->F, weight: 0.1f" << std::endl;
    std::vector<int> result;
    bool found = graph.HeuristicShortestPath(result, "A", "F", 0.1f);
    std::cout << "Return value: " << (found ? ("True") : ("False")) << std::endl;
    graph.PrintPath(result, 0.5f, true);

    std::cout << "-------------------------------" << std::endl;
    InsertEdge(graph, "E00", "A", "B", 0.3f, 2.12f);
    InsertEdge(graph, "E02", "A", "B", 1.3f, 0.62f);
    InsertEdge(graph, "E10", "B", "A", 0.3f, 2.12f);
    InsertEdge(graph, "E11", "B", "A", 1.3f, 4.12f);
    InsertEdge(graph, "E12", "B", "A", 2.3f, 1.12f);
    InsertEdge(graph, "E21", "B", "C", 1.2f, 2.12f);
    InsertEdge(graph, "E30", "E", "B", 1.2f, 22.12f);
    InsertEdge(graph, "E40", "B", "E", 21.2f, 22.12f);
    InsertEdge(graph, "E60", "A", "E", 0.4f, 0.02f);
    InsertEdge(graph, "E70", "A", "D", 0.4f, 0.02f);
    InsertEdge(graph, "E71", "A", "D", 1.4f, 1.02f);
    InsertEdge(graph, "E72", "A", "D", 2.4f, 2.02f);
    InsertEdge(graph, "E80", "D", "B", 2.1f, 3.122f);

    graph.PrintEntireGraph();

    result.clear();
    std::cout << "Calling shortest path from A->F, weight: 0.5f" << std::endl;
    found = graph.HeuristicShortestPath(result, "A", "F", 0.5f);
    std::cout << "Return value: " << (found ? ("True") : ("False")) << std::endl;
    graph.PrintPath(result, 0.5f, true);

	return 0;
}