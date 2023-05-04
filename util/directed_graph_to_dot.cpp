#pragma once
#include <cstddef>
#include <sstream>
#include <string>
#include <string_view>

#include "directed_graph.h"
/**
 * @brief graph를 표현하고 이해하고 그래픽 표현으로 변환할 수있는 형식
 *
 * @tparam T
 * @param graph
 * @param graph_name
 * @return std::wstring
 */
template <typename T>
std::wstring to_dot(const directed_graph<T>& graph, std::wstring_view graph_name) {
    std::wstringstream wss;

    wss << L"digraph " << graph_name.data() << L" {" << std::endl;
    for (auto&& node : graph) {
        // node는 graph의 반복자의 역참조로 순회
        const auto b{graph.cbegin(node)};  // 현재 노드의 인접노드 반복자를 가져온다.
        const auto e{graph.cend(node)};
        if (b == e) {//end반복자는 다음꺼를 참조하므로 인접노드가 하나라도 있다면 값이 다름
            wss << node << std::endl;
        } else {
            for (auto iter{b}; iter != e; ++iter) {
                wss << L"" << node << L" -> " << *iter << std::endl;
            }
        }
    }
    /*for (size_t index{0}; index < graph.size(); ++index) {
        const auto& node_value{graph[index]};
        const auto adjacent_nodes{graph.get_adjacent_nodes_values(node_value)};
        if (adjacent_nodes.empty()) {
            wss << node_value << std::endl;
        } else {
            for (auto&& node : adjacent_nodes) {
                wss << L"" << node_value << L" -> " << node << std::endl;  //<<std::format(L"{} -> {}", node_value, node) << std::endl;
            }
        }
    }*/
    wss << "}" << std::endl;

    return wss.str();
}