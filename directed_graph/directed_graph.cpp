#include "directed_graph.h"

#include <algorithm>

template <typename T>
typename directed_graph<T>::nodes_container_type::iterator
directed_graph<T>::findNode(const T& node_value) {
    return std::find_if(std::begin(m_nodes), std::end(m_nodes),
                        [&node_value](const auto& node) {
                            return node.value() == node_value;
                        });
}

template <typename T>
typename directed_graph<T>::nodes_container_type::const_iterator
directed_graph<T>::findNode(const T& node_value) const {
    return const_cast<directed_graph<T>*>(this)->findNode(node_value);
}

template <typename T>
bool directed_graph<T>::insert(const T& node_value) {
    T copy{node_value};
    return insert(std::move(copy));
}

template <typename T>
bool directed_graph<T>::insert(T&& node_value) {
    auto iter{findNode(node_value)};
    if (iter != std::end(m_nodes)) {
        return false;
    }
    m_nodes.emplace_back(this, std::move(node_value));  // graph_node<directed_graph<T>*, T&&) 생성자 호출
    return true;
}

template <typename T>
std::size_t directed_graph<T>::get_index_of_node(
    const typename nodes_container_type::const_iterator& node)
    const noexcept {
    const auto index{std::distance(std::cbegin(m_nodes), node)};
    return static_cast<std::size_t>(index);
}

template <typename T>
bool directed_graph<T>::insert_edge(const T& from_node_value,
                                    const T& to_node_value) {
    const auto from{findNode(from_node_value)};
    const auto to{findNode(to_node_value)};
    if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
        return false;
    }
    const std::size_t to_index{get_index_of_node(to)};
    return from->get_adjacent_nodes_indices().insert(to_index).second;
}

template <typename T>
void directed_graph<T>::remove_all_links_to(typename nodes_container_type::const_iterator node_iter) {
    const size_t node_index{get_index_of_node(node_iter)};

    // 모든 노드 반복
    for (auto&& node : m_nodes) {
        auto& adjacencyIndices{node.get_adjacent_nodes_indices()};
        // 인접 리스트에서 해당 노드의 인덱스를 제거한다.
        adjacencyIndices.erase(node_index);
        // 노드 제거를 고려하여 모든 인접 인덱스를 수정합니다.

        std::vector<size_t> indices{std::begin(adjacencyIndices), std::end(adjacencyIndices)};

        // 모든 인접 리스트 반복
        std::for_each(std::begin(indices), std::end(indices),
                      [node_index](size_t& index) {
                          // 삭제한 노드의 인덱스보다 큰곳의 인덱스는 1을 빼야함
                          if (index > node_index) {
                              --index;
                          }
                      });
        adjacencyIndices.clear();
        // 수정된 인덱스를 원본에 삽입
        adjacencyIndices.insert(std::begin(indices), std::end(indices));
    }
}

template <typename T>
bool directed_graph<T>::erase(const T& node_value) {
    auto iter{findNode(node_value)};
    if (iter == std::end(m_nodes)) {
        return false;
    }
    remove_all_links_to(iter);
    m_nodes.erase(iter);
    return true;
}

template <typename T>
bool directed_graph<T>::erase_edge(const T& from_node_value, const T& to_node_value) {
    const auto from{findNode(from_node_value)};
    const auto to{findNode(to_node_value)};
    if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
        return false;  // nothing to erase
    }
    const size_t to_index{get_index_of_node(to)};
    from->get_adjacent_nodes_indices().erase(to_index);
    return true;
}

template <typename T>
void directed_graph<T>::clear() noexcept {
    m_nodes.clear();
}

template <typename T>
void directed_graph<T>::swap(directed_graph& other_graph) noexcept {
    m_nodes.swap(other_graph.m_nodes);
}

/**
 * @brief 전역 방향 그래프 swap 함수
 *
 * @tparam T 방향 그래프의 값 타입
 * @param first
 * @param second
 */
template <typename T>
void swap(directed_graph<T>& first, directed_graph<T>& second) {
    first.swap(second);
}

template <typename T>
T& directed_graph<T>::operator[](size_t index) {
    return m_nodes[index].value();
}
template <typename T>
const T& directed_graph<T>::operator[](size_t index) const {
    return m_nodes[index].value();
}

template <typename T>
bool directed_graph<T>::operator==(const directed_graph& rhs) const {
    if (m_nodes.size() != rhs.m_nodes.size()) {
        return false;
    }
    // 노드의 값과 노드의 인접 리스트의 값이 같은지 확인한다.
    for (auto&& node : m_nodes) {
        const auto rhsNodeIter{rhs.findNode(node.value())};
        if (rhsNodeIter == std::end(rhs.m_nodes)) {
            return false;
        }
        const auto adjacent_values_lhs{
            get_adjacent_nodes_values(node.get_adjacent_nodes_indices())};
        const auto adjacent_values_rhs{rhs.get_adjacent_nodes_values(
            rhsNodeIter->get_adjacent_nodes_indices())};
        if (adjacent_values_lhs != adjacent_values_rhs) {
            return false;
        }
    }
    return true;
}

template <typename T>
std::set<T> directed_graph<T>::get_adjacent_nodes_values(
    const typename details::graph_node<T>::adjacency_list_type& indices) const {
    std::set<T> values;
    for (auto&& index : indices) {
        values.insert(m_nodes[index].value());
    }
    return values;
}

template <typename T>
bool directed_graph<T>::operator!=(const directed_graph& rhs) const {
    return !(*this == rhs);
}

template <typename T>
std::set<T> directed_graph<T>::get_adjacent_nodes_values(const T& node_value) const {
    auto iter{findNode(node_value)};
    if (iter == std::end(m_nodes)) {
        return std::set<T>{};
    }
    return get_adjacent_nodes_values(iter->get_adjacent_nodes_indices());
}


template <typename T>
typename directed_graph<T>::size_type directed_graph<T>::size() const noexcept {
    return m_nodes.size();
}
template <typename T>
typename directed_graph<T>::size_type directed_graph<T>::max_size() const noexcept {
    return m_nodes.max_size();
}
template <typename T>
bool directed_graph<T>::empty() const noexcept {
    return m_nodes.empty();
}

template <typename T>
typename directed_graph<T>::reference
directed_graph<T>::at(size_type index) {
    return m_nodes.at(index).value();
}
template <typename T>
typename directed_graph<T>::const_reference
directed_graph<T>::at(size_type index) const {
    return m_nodes.at(index).value();
}

// 템플릿 클래스 인스턴스화
template class directed_graph<int>;