#include "directed_graph.h"

template <typename T>
typename directed_graph<T>::nodes_container_type::iterator directed_graph<T>::findNode(const T& node_value) {
    return std::find_if(std::begin(m_nodes), std::end(m_nodes),
                        [&node_value](const auto& node) {
                            return node.value() == node_value;
                        });
}

template <typename T>
typename directed_graph<T>::nodes_container_type::const_iterator directed_graph<T>::findNode(const T& node_value) const {
    // 코드 중복을 피하기 위해 const_cast 적용
    return const_cast<directed_graph<T>*>(this)->findNode(node_value);
}

template <typename T>
std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(T&& node_value) {
    auto iter{findNode(node_value)};
    // 1. 중복이 있는지 확인한다.
    if (iter != std::end(m_nodes)) {
        // 중복이 있다면 return false
        return {iterator{iter, this}, false};
    }
    // 값이 없다면 추가한다.
    // graph_node(directed_graph<T>* graph, T&& t) 임시 객체 생성후 emplace_back
    m_nodes.emplace_back(this, std::move(node_value));  // details::graph_node<T> 객체를 만든다.
    return {iterator{--std::end(m_nodes), this}, true};
}

template <typename T>
std::pair<typename directed_graph<T>::iterator, bool> directed_graph<T>::insert(const T& node_value) {
    // 코드 중복 최소화
    T copy{node_value};
    return insert(std::move(copy));
}

template <typename T>
typename directed_graph<T>::iterator
directed_graph<T>::insert(const_iterator hint, const T& node_value) {
    // Ignore the hint, just forward to another insert().
    return insert(node_value).first;
}

template <typename T>
typename directed_graph<T>::iterator
directed_graph<T>::insert(const_iterator hint, T&& node_value) {
    // Ignore the hint, just forward to another insert().
    return insert(std::move(node_value)).first;
}

template <typename T>
template <typename Iter>
void directed_graph<T>::insert(Iter first, Iter last) {
    // insert_iterator 어댑터를 사용하여 범위의 각 요소를 복사합니다.
    // begin()을 더미 위치로 지정하십시오. 삽입은 어쨌든 이를 무시합니다.
    std::copy(first, last, std::insert_iterator{*this, begin()});
}

template <typename T>
bool directed_graph<T>::insert_edge(const T& from_node_value, const T& to_node_value) {
    const auto from{findNode(from_node_value)};
    const auto to{findNode(to_node_value)};

    // 노드가 존재 하지 않는다면 false
    if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
        return false;
    }
    // 노드가 모두 존재한다면, 간선 삽입
    /**
     * @brief 목적지의 인덱스
     *
     */
    const size_t to_index{get_index_of_node(to)};
    /**
     * @brief 출발지의 반복자에서 인접노트 리스트를 가져온후,
     * 인접노드 리스트에 목적지의 인덱스를 삽입한다.
     * set의 insert()메서드는 iterator와 bool의 쌍을 반환하며 bool은 성공여부를 나타낸다.
     */
    return from->get_adjacent_nodes_indices().insert(to_index).second;
}

template <typename T>
size_t directed_graph<T>::get_index_of_node(const typename nodes_container_type::const_iterator& node) const noexcept {
    const auto index{std::distance(std::cbegin(m_nodes), node)};  // 인덱스를 계산후 리턴
    return static_cast<size_t>(index);
}

template <typename T>
void directed_graph<T>::remove_all_links_to(typename nodes_container_type::const_iterator node_iter) {
    const size_t node_index{get_index_of_node(node_iter)};

    // 모든 노드의 모든 인접 리스트에 대해 반복
    for (auto&& node : m_nodes) {
        auto& adjacencyIndices{node.get_adjacent_nodes_indices()};
        // 인접 리스트에서 해당 노드의 인덱스를 제거한다.
        adjacencyIndices.erase(node_index);
        // 노드 제거를 고려하여 모든 인접 인덱스를 수정합니다.

        std::vector<size_t> indices{std::begin(adjacencyIndices), std::end(adjacencyIndices)};

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
    // 값에 대한 노드가 없다면 false 리턴
    if (iter == std::end(m_nodes)) {
        return false;
    }

    // 1. 노드가 존재한다면, 인접리스트제거 및 인접리스트 인덱스 정리
    remove_all_links_to(iter);
    // 2. 실제 노드 삭제
    m_nodes.erase(iter);
    return true;
}

template <typename T>
typename directed_graph<T>::iterator
directed_graph<T>::erase(const_iterator pos) {
    if (pos.m_nodeIterator == std::end(m_nodes)) {
        return iterator{std::end(m_nodes), this};
    }
    remove_all_links_to(pos.m_nodeIterator);
    return iterator{m_nodes.erase(pos.m_nodeIterator), this};
}

template <typename T>
typename directed_graph<T>::iterator
directed_graph<T>::erase(const_iterator first, const_iterator last) {
    for (auto iter{first}; iter != last; ++iter) {
        if (iter.m_nodeIterator != std::end(m_nodes)) {
            remove_all_links_to(iter.m_nodeIterator);
        }
    }
    return iterator{m_nodes.erase(first.m_nodeIterator, last.m_nodeIterator), this};
}

template <typename T>
bool directed_graph<T>::erase_edge(const T& from_node_value,
                                   const T& to_node_value) {
    const auto from{findNode(from_node_value)};
    const auto to{findNode(to_node_value)};
    // 주어진 노드를 찾지 못했다면 false 리턴
    if (from == std::end(m_nodes) || to == std::end(m_nodes)) {
        return false;
    }

    /**
     * @brief 삭제할 간선 목적지의 인덱스
     *
     */
    const size_t to_index{get_index_of_node(to)};

    /**
     * @brief 출발지의 반복자에서 인접노트 리스트를 가져온후,
     * 인접노드 리스트에 목적지의 인덱스를 삭제한다.
     * set의 insert()메서드는 iterator와 bool의 쌍을 반환하며 bool은 성공여부를 나타낸다.
     */
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

template <typename T>
void swap(directed_graph<T>& first, directed_graph<T>& second) {
    first.swap(second);
}

template <typename T>
T& directed_graph<T>::operator[](size_t index) {
    // 경계 검사를 수행하지 않는다.
    return m_nodes[index].value();
}
template <typename T>
const T& directed_graph<T>::operator[](size_t index) const {
    // 경계 검사를 수행하지 않는다.
    return const_cast<directed_graph<T>*>(this)->operator[](index);
}

template <typename T>
bool directed_graph<T>::operator==(const directed_graph& rhs) const {
    if (m_nodes.size() != rhs.m_nodes.size()) {
        return false;
    }
    // 크기가 같은 경우에만 확인한다.

    for (auto&& node : m_nodes) {
        // 일치하는 값의 노드가 있는지 확인한다.
        const auto rhsNodeIter{rhs.findNode(node.value())};
        if (rhsNodeIter == std::end(rhs.m_nodes)) {
            // 일치하는 값의 노드가 없다면 false
            return false;
        }

        // 현재노드와 일치하는 값의 노드가 있다면
        // 그 노드의 인접 인덱스 리스트에서 인접 리스트의 값을 가져온다.
        const auto adjacent_value_lhs{
            get_adjacent_nodes_values(node.get_adjacent_nodes_indices())};
        const auto adjacent_values_rhs{
            rhs.get_adjacent_nodes_values(rhsNodeIter->get_adjacent_nodes_indices())};

        // 인접리스트의 값이 같은지 비교한다.
        if (adjacent_value_lhs != adjacent_values_rhs) {
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

/*template <typename T>
size_t directed_graph<T>::size() const noexcept {
    return m_nodes.size();
}*/

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
typename directed_graph<T>::reference directed_graph<T>::at(size_type index) {
    return m_nodes.at(index).value();
}

template <typename T>
typename directed_graph<T>::const_reference directed_graph<T>::at(size_type index) const {
    return m_nodes.at(index).value();
}

template <typename T>
typename directed_graph<T>::iterator directed_graph<T>::begin() noexcept {
    return iterator{std::begin(m_nodes) /*const iterator*/, this /*directed graph*/};
}

template <typename T>
typename directed_graph<T>::iterator directed_graph<T>::end() noexcept {
    return iterator{std::end(m_nodes) /*const iterator*/, this /*directed graph*/};
}

template <typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::begin() const noexcept {
    return const_cast<directed_graph*>(this)->begin();
}

template <typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::end() const noexcept {
    return const_cast<directed_graph*>(this)->end();
}

template <typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::cbegin() const noexcept {
    return begin();
}

template <typename T>
typename directed_graph<T>::const_iterator directed_graph<T>::cend() const noexcept {
    return end();
}

template <typename T>
typename directed_graph<T>::iterator directed_graph<T>::find(const T& node_value) {
    return iterator{findNode(node_value), this};
}

template <typename T>
typename directed_graph<T>::const_iterator
directed_graph<T>::find(const T& node_value) const {
    return iterator{findNode(node_value), this};
}

template <typename T>
typename directed_graph<T>::reverse_iterator
directed_graph<T>::rbegin() noexcept {
    return reverse_iterator{end()};
}

template <typename T>
typename directed_graph<T>::reverse_iterator
directed_graph<T>::rend() noexcept {
    return reverse_iterator{begin()};
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator
directed_graph<T>::rbegin() const noexcept {
    return const_reverse_iterator{end()};
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator
directed_graph<T>::rend() const noexcept {
    return const_reverse_iterator{begin()};
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator
directed_graph<T>::crbegin() const noexcept {
    return rbegin();
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator
directed_graph<T>::crend() const noexcept {
    return rend();
}

template <typename T>
typename directed_graph<T>::iterator_adjacent_nodes
directed_graph<T>::begin(const T& node_value) noexcept {
    auto iter{findNode(node_value)};
    if (iter == std::end(m_nodes)) {
        // Return a default constructed end iterator.
        return iterator_adjacent_nodes{};
    }
    return iterator_adjacent_nodes{
        std::begin(iter->get_adjacent_nodes_indices()), this};
}

template <typename T>
typename directed_graph<T>::iterator_adjacent_nodes
directed_graph<T>::end(const T& node_value) noexcept {
    auto iter{findNode(node_value)};
    if (iter == std::end(m_nodes)) {
        // Return a default constructed end iterator.
        return iterator_adjacent_nodes{};
    }
    return iterator_adjacent_nodes{std::end(iter->get_adjacent_nodes_indices()), this};
}

template <typename T>
typename directed_graph<T>::const_iterator_adjacent_nodes
directed_graph<T>::cbegin(const T& node_value) const noexcept {
    auto iter{findNode(node_value)};
    if (iter == std::end(m_nodes)) {
        // Return a default constructed end iterator.
        return const_iterator_adjacent_nodes{};
    }
    return const_iterator_adjacent_nodes{std::cbegin(iter->get_adjacent_nodes_indices()), this};
}

template <typename T>
typename directed_graph<T>::const_iterator_adjacent_nodes
directed_graph<T>::cend(const T& node_value) const noexcept {
    auto iter{findNode(node_value)};
    if (iter == std::end(m_nodes)) {
        // Return a default constructed end iterator.
        return const_iterator_adjacent_nodes{};
    }
    return const_iterator_adjacent_nodes{std::cend(iter->get_adjacent_nodes_indices()), this};
}

template <typename T>
typename directed_graph<T>::const_iterator_adjacent_nodes
directed_graph<T>::begin(const T& node_value) const noexcept {
    return cbegin(node_value);
}

template <typename T>
typename directed_graph<T>::const_iterator_adjacent_nodes
directed_graph<T>::end(const T& node_value) const noexcept {
    return cend(node_value);
}

template <typename T>
typename directed_graph<T>::reverse_iterator_adjacent_nodes
directed_graph<T>::rbegin(const T& node_value) noexcept {
    return reverse_iterator_adjacent_nodes{end(node_value)};
}

template <typename T>
typename directed_graph<T>::reverse_iterator_adjacent_nodes
directed_graph<T>::rend(const T& node_value) noexcept {
    return reverse_iterator_adjacent_nodes{begin(node_value)};
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator_adjacent_nodes
directed_graph<T>::rbegin(const T& node_value) const noexcept {
    return const_reverse_iterator_adjacent_nodes{end(node_value)};
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator_adjacent_nodes
directed_graph<T>::rend(const T& node_value) const noexcept {
    return const_reverse_iterator_adjacent_nodes{begin(node_value)};
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator_adjacent_nodes
directed_graph<T>::crbegin(const T& node_value) const noexcept {
    return rbegin(node_value);
}

template <typename T>
typename directed_graph<T>::const_reverse_iterator_adjacent_nodes
directed_graph<T>::crend(const T& node_value) const noexcept {
    return rend(node_value);
}

template<typename T>
template<typename Iter>
void directed_graph<T>::assign(Iter first, Iter last) {
    clear();
    for(auto iter { first }; iter != last; ++iter) {
        insert(*iter);
    }
}

template<typename T>
void directed_graph<T>::assign(std::initializer_list<T> init) {
    assign(std::begin(init), std::end(init));
}

template<typename T>
void directed_graph<T>::insert(std::initializer_list<T> init) {
    insert(std::begin(init), std::end(init));
}

template<typename T>
directed_graph<T>::directed_graph(std::initializer_list<T> init) {
    assign(std::begin(init), std::end(init));
}

template<typename T>
directed_graph<T>& directed_graph<T>::operator=(std::initializer_list<T> init) {
    //copy-and-swap 패턴사용 (예외 안정성을 위해)
    directed_graph new_graph { init };//1. 임시 복제본 생성
    swap(new_graph);
    return *this;
}

// 인스턴스화
template class directed_graph<int>;