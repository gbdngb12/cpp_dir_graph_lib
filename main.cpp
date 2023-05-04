#include <iostream>

#include "directed_graph.h"
#include "directed_graph_to_dot.cpp"

using namespace std;
int main() {
    directed_graph<int> graph;
    // Insert some nodes and edges.
    graph.insert(11);
    graph.insert(22);
    graph.insert(33);
    graph.insert(44);
    graph.insert(55);
    graph.insert_edge(11, 33);
    graph.insert_edge(22, 33);
    graph.insert_edge(22, 44);
    graph.insert_edge(22, 55);
    graph.insert_edge(33, 44);
    graph.insert_edge(44, 55);
    wcout << to_dot(graph, L"Graph1");
    // Remove an edge and a node.
    graph.erase_edge(22, 44);
    graph.erase(44);
    wcout << to_dot(graph, L"Graph1");
    // Print the size of the graph.
    wcout << "Size: " << graph.size() << endl;
}