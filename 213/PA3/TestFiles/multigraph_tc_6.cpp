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
    std::cout << "Testing Filtered Shortest Path" << std::endl;
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

    std::cout << "Calling filtered shortest path from A->F, weight: 0.1f empty filter" << std::endl;
    std::vector<int> result;
    bool found = graph.FilteredShortestPath(result, "A", "F", 0.1f,
                                            std::vector<std::string>());
    std::cout << "Return value: " << (found ? ("True") : ("False")) << std::endl;
    graph.PrintPath(result, 0.5f, true);

    std::cout << "-------------------------------" << std::endl;

    std::vector<std::string> filter = {"E50"};
    result.clear();
    std::cout << "Calling filtered shortest path from A->F, weight: 0.1f filter={\"E50\"}" << std::endl;
    found = graph.FilteredShortestPath(result, "A", "F", 0.1f, filter);
    std::cout << "Return value: " << (found ? ("True") : ("False")) << std::endl;
    if(found)
    {
        graph.PrintPath(result, 0.5f, true);
    }

	return 0;
}