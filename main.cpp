#include <algorithm>
#include <iostream>

#include "directed_graph.h"
#include "directed_graph_to_dot.cpp"

using namespace std;
int main() {
    directed_graph<int> graph;
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
    wcout << L"Size: " << graph.size() << endl;

    auto [iter22, inserted]{graph.insert(22)};
    if (!inserted) {
        wcout << "Duplicate element.\n";
    }

    for (auto iter{graph.cbegin()}; iter != graph.cend(); ++iter) {
        wcout << *iter << " ";
    }
    wcout << std::endl;

    for (auto iter{std::cbegin(graph)}; iter != std::cend(graph); ++iter) {
        wcout << *iter << " ";
    }
    wcout << std::endl;

    for (auto& node : graph) {
        wcout << node << std::endl;
    }
    wcout << std::endl;

    auto result{std::find(std::begin(graph), std::end(graph), 22)};
    if (result != std::end(graph)) {
        wcout << "Node 22 found" << std::endl;
    } else {
        wcout << "Node 22 NOT found" << std::endl;
    }

    auto count{std::count_if(std::begin(graph), std::end(graph), [](const auto& node) {
        return node > 22;
    })};

    wcout << count << std::endl;

    //graph.erase(std::find(std::begin(graph), std::end(graph), 33));

    for (auto iter{graph.rbegin()}; iter != graph.rend(); ++iter) {
        wcout << *iter << " ";
    }

    wcout << std::endl;

    /*wcout << "Adjacency list for node 22: ";

    auto iterBegin { graph.cbegin(22) };
    auto iterEnd { graph.cend(22) };

    if(iterBegin == directed_graph<int>::const_iterator_adjacent_nodes{}) {
        wcout << "Value 22 not found." << std::endl;
    } else {
        for(auto iter{iterBegin}; iter != iterEnd;++iter) {
            wcout << *iter << " ";
        }
    }*/
    directed_graph<int> graph2 { 11, 22, 33 };
    wcout << to_dot(graph2, L"Graph2") << endl;
    graph2 = { 44, 55, 66};
    wcout << to_dot(graph2, L"Graph2") << endl;
    return 0;
}