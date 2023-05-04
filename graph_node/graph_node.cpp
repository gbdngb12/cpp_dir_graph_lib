#include "graph_node.h"

#include <utility>
using namespace details;

template <typename T>
graph_node<T>::graph_node(directed_graph<T>* graph, const T& t)
    : m_graph{graph}, m_data{t} {}

template <typename T>
graph_node<T>::graph_node(directed_graph<T>* graph, T&& t)
    : m_graph{graph}, m_data{std::move(t)} {}

template <typename T>
T& graph_node<T>::value() noexcept {
    return m_data;
}
template <typename T>
const T& graph_node<T>::value() const noexcept {
    return m_data;
}

template<typename T>
typename graph_node<T>::adjacency_list_type& graph_node<T>::get_adjacent_nodes_indices() {
    return m_adjacentNodeIndices;
}

template<typename T>
const typename graph_node<T>::adjacency_list_type& graph_node<T>::get_adjacent_nodes_indices() const {
    return m_adjacentNodeIndices;
}

// 템플릿 클래스의 인스턴스화
template class graph_node<int>;