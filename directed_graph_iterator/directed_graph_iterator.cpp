#include "directed_graph_iterator.h"

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph>::const_directed_graph_iterator(
    iterator_type it, const DirectedGraph* graph)
    : m_nodeIterator{it}, m_graph{graph} {}

template <typename DirectedGraph>
typename const_directed_graph_iterator<DirectedGraph>::reference
const_directed_graph_iterator<DirectedGraph>::operator*() const {
    return m_nodeIterator->value();  // 참조를 리턴
}

template <typename DirectedGraph>
typename const_directed_graph_iterator<DirectedGraph>::pointer
const_directed_graph_iterator<DirectedGraph>::operator->() const {
    return &(m_nodeIterator->value());  // 포인터를 리턴
}

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph>&
const_directed_graph_iterator<DirectedGraph>::operator++() {
    increment();
    return *this;
}

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph>
const_directed_graph_iterator<DirectedGraph>::operator++(int) {
    auto oldIt{*this};
    increment();
    return oldIt;
}

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph>&
const_directed_graph_iterator<DirectedGraph>::operator--() {
    decrement();
    return *this;
}

template <typename DirectedGraph>
const_directed_graph_iterator<DirectedGraph>
const_directed_graph_iterator<DirectedGraph>::operator--(int) {
    auto oldIt{*this};
    decrement();
    return oldIt;
}

template <typename DirectedGraph>
void const_directed_graph_iterator<DirectedGraph>::increment() {
    // vector의 반복자 증가
    ++m_nodeIterator;
}

template <typename DirectedGraph>
void const_directed_graph_iterator<DirectedGraph>::decrement() {
    // vector의 반복자 증가
    // m_nodeIterator가 이미 첫 번째 요소를 참조하는 경우
    // 동작이 정의되지 않거나 그렇지 않으면 유효하지 않습니다.
    --m_nodeIterator;
}

template <typename DirectedGraph>
directed_graph_iterator<DirectedGraph>::directed_graph_iterator(
    iterator_type it, const DirectedGraph* graph)
    : const_directed_graph_iterator<DirectedGraph>{it, graph} {}

template <typename DirectedGraph>
directed_graph_iterator<DirectedGraph>::reference
directed_graph_iterator<DirectedGraph>::operator*() {
    return const_cast<reference>(this->m_nodeIterator->value());
}

template <typename DirectedGraph>
directed_graph_iterator<DirectedGraph>::pointer
directed_graph_iterator<DirectedGraph>::operator->() {
    return const_cast<pointer>(&(this->m_nodeIterator->value()));
}

template <typename DirectedGraph>
directed_graph_iterator<DirectedGraph>&
directed_graph_iterator<DirectedGraph>::operator++() {
    this->increment();
    return *this;
}

template <typename DirectedGraph>
directed_graph_iterator<DirectedGraph>
directed_graph_iterator<DirectedGraph>::operator++(int) {
    auto oldIt{*this};
    this->increment();
    return oldIt;
}

template <typename DirectedGraph>
directed_graph_iterator<DirectedGraph>&
directed_graph_iterator<DirectedGraph>::operator--() {
    this->decrement();
    return *this;
}

template <typename DirectedGraph>
directed_graph_iterator<DirectedGraph>
directed_graph_iterator<DirectedGraph>::operator--(int) {
    auto oldIt{*this};
    this->decrement();
    return oldIt;
}

// 클래스 템플릿 인스턴스화
template class const_directed_graph_iterator<directed_graph<int>>;
template class directed_graph_iterator<directed_graph<int>>;