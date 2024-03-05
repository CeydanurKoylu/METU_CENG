#include <iostream>
#include <vector>

class MultiGraph {
private:
    int numNodes;
    std::vector<std::vector<std::pair<int, int>>> adjacencyMatrix; // Pair represents edge weight and edge count

public:
    MultiGraph(int nodes) : numNodes(nodes), adjacencyMatrix(nodes, std::vector<std::pair<int, int>>(nodes, {0, 0})) {}

    void addEdge(int source, int destination, int weight) {
        if (source >= 0 && source < numNodes && destination >= 0 && destination < numNodes) {
            adjacencyMatrix[source][destination].first += weight;
            adjacencyMatrix[destination][source].first += weight;
            adjacencyMatrix[source][destination].second++;
            adjacencyMatrix[destination][source].second++;
        } else {
            std::cerr << "Invalid node indices." << std::endl;
        }
    }

    void printGraph() {
        for (int i = 0; i < numNodes; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                if (adjacencyMatrix[i][j].second > 0) {
                    std::cout << "Edge from " << i << " to " << j << ": ";
                    std::cout << "Weight = " << adjacencyMatrix[i][j].first << ", Count = " << adjacencyMatrix[i][j].second << std::endl;
                }
            }
        }
    }
};

int main() {
    // Create a multigraph with 5 nodes
    MultiGraph multigraph(5);

    // Add edges with weights
    multigraph.addEdge(0, 1, 3);
    multigraph.addEdge(1, 2, 5);
    multigraph.addEdge(2, 3, 2);
    multigraph.addEdge(3, 4, 1);
    multigraph.addEdge(4, 0, 4);

    // Print the multigraph
    multigraph.printGraph();

    return 0;
}
