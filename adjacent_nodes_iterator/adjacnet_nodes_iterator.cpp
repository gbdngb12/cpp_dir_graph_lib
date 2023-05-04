#include "adjacent_nodes_iterator.h"
#include "directed_graph.h"

template <typename GraphType>
const_adjacent_nodes_iterator<GraphType>::const_adjacent_nodes_iterator(
    iterator_type it, const GraphType* graph)
    : m_adjacentNodeIterator{it}, m_graph{graph} {
}

// Return a reference to the node.
template <typename GraphType>
typename const_adjacent_nodes_iterator<GraphType>::reference
const_adjacent_nodes_iterator<GraphType>::operator*() const {
    // Return an reference to the actual node, not the index to the node.
    return (*m_graph)[*m_adjacentNodeIterator];
}

// Return a pointer to the actual node, so the compiler can
// apply -> to it to access the actual desired field.
template <typename GraphType>
typename const_adjacent_nodes_iterator<GraphType>::pointer
const_adjacent_nodes_iterator<GraphType>::operator->() const {
    return &((*m_graph)[*m_adjacentNodeIterator]);
}

// Defer the details to the increment() helper.
template <typename GraphType>
const_adjacent_nodes_iterator<GraphType>&
const_adjacent_nodes_iterator<GraphType>::operator++() {
    increment();
    return *this;
}

// Defer the details to the increment() helper.
template <typename GraphType>
const_adjacent_nodes_iterator<GraphType>
const_adjacent_nodes_iterator<GraphType>::operator++(int) {
    auto oldIt{*this};
    increment();
    return oldIt;
}

// Defer the details to the decrement() helper.
template <typename GraphType>
const_adjacent_nodes_iterator<GraphType>&
const_adjacent_nodes_iterator<GraphType>::operator--() {
    decrement();
    return *this;
}

// Defer the details to the decrement() helper.
template <typename GraphType>
const_adjacent_nodes_iterator<GraphType>
const_adjacent_nodes_iterator<GraphType>::operator--(int) {
    auto oldIt{*this};
    decrement();
    return oldIt;
}

// Behavior is undefined if m_adjacentNodeIterator already refers to the past-the-end
// element, or is otherwise invalid.
template <typename GraphType>
void const_adjacent_nodes_iterator<GraphType>::increment() {
    ++m_adjacentNodeIterator;
}

// Behavior is undefined if m_adjacentNodeIterator already refers to the first
// element, or is otherwise invalid.
template <typename GraphType>
void const_adjacent_nodes_iterator<GraphType>::decrement() {
    --m_adjacentNodeIterator;
}

template <typename GraphType>
bool const_adjacent_nodes_iterator<GraphType>::operator==(
    const const_adjacent_nodes_iterator<GraphType>& rhs) const {
    if (!m_graph && !rhs.m_graph) {
        // They are both end iterators.
        return true;
    }
    return (m_graph == rhs.m_graph &&
            m_adjacentNodeIterator == rhs.m_adjacentNodeIterator);
}

template <typename GraphType>
bool const_adjacent_nodes_iterator<GraphType>::operator!=(
    const const_adjacent_nodes_iterator<GraphType>& rhs) const {
    return !(*this == rhs);
}

template <typename GraphType>
adjacent_nodes_iterator<GraphType>::adjacent_nodes_iterator(
    iterator_type it, const GraphType* graph)
    : const_adjacent_nodes_iterator<GraphType>{it, graph} {
}

// Return a reference to the node.
template <typename GraphType>
typename adjacent_nodes_iterator<GraphType>::reference
adjacent_nodes_iterator<GraphType>::operator*() {
    // Return an reference to the actual node, not the index to the node.
    return const_cast<reference>((*(this->m_graph))[*(this->m_adjacentNodeIterator)]);
}

// Return a pointer to the actual node, so the compiler can
// apply -> to it to access the actual desired field.
template <typename GraphType>
typename adjacent_nodes_iterator<GraphType>::pointer
adjacent_nodes_iterator<GraphType>::operator->() {
    return const_cast<pointer>(&((*(this->m_graph))[*(this->m_adjacentNodeIterator)]));
}

// Defer the details to the increment() helper.
template <typename GraphType>
adjacent_nodes_iterator<GraphType>&
adjacent_nodes_iterator<GraphType>::operator++() {
    this->increment();
    return *this;
}

// Defer the details to the increment() helper.
template <typename GraphType>
adjacent_nodes_iterator<GraphType>
adjacent_nodes_iterator<GraphType>::operator++(int) {
    auto oldIt{*this};
    this->increment();
    return oldIt;
}

// Defer the details to the decrement() helper.
template <typename GraphType>
adjacent_nodes_iterator<GraphType>&
adjacent_nodes_iterator<GraphType>::operator--() {
    this->decrement();
    return *this;
}

// Defer the details to the decrement() helper.
template <typename GraphType>
adjacent_nodes_iterator<GraphType>
adjacent_nodes_iterator<GraphType>::operator--(int) {
    auto oldIt{*this};
    this->decrement();
    return oldIt;
}

// 인스턴스화
template class const_adjacent_nodes_iterator<directed_graph<int>>;
template class adjacent_nodes_iterator<directed_graph<int>>;