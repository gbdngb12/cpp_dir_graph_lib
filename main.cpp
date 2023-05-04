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

    // Try to insert a duplicate, and use structured bindings for the result.
    auto [iter22, inserted]{graph.insert(22)};
    if (!inserted) {
        wcout << "Duplicate element.\n";
    }
    // Print nodes using a for loop and iterators.
    for (auto iter{graph.cbegin()}; iter != graph.cend(); ++iter) {
        wcout << *iter << " ";
    }
    wcout << std::endl;
    // Print nodes using a for loop and iterators retrieved with the non-member
    // functions std::cbegin() and std::cend().
    for (auto iter{std::cbegin(graph)}; iter != std::cend(graph); ++iter) {
        wcout << *iter << " ";
    }
    wcout << std::endl;
    // Print nodes using a range-based for loop.
    for (auto& node : graph) {
        wcout << node << std::endl;
    }
    wcout << std::endl;
    // Search a node using the std::find() Standard Library algorithm.
    auto result{std::find(std::begin(graph), std::end(graph), 22)};
    if (result != std::end(graph)) {
        wcout << "Node 22 found." << std::endl;
    } else {
        wcout << "Node 22 NOT found." << std::endl;
    }
    // Count all nodes with values > 22.
    auto count{std::count_if(std::begin(graph), std::end(graph),
                             [](const auto& node) { return node > 22; })};
    // Use the iterator-based erase() method in combination with std::find().
    graph.erase(std::find(std::begin(graph), std::end(graph), 44));
}