#pragma once
#include <cstddef>
#include <iterator>

#include "directed_graph.h"


template <typename T>
class directed_graph;

template <typename DirectedGraph>
class const_directed_graph_iterator {
   public:
    /**
     * @brief iterator_traits 5가지 정의
     *
     */
    using value_type = typename DirectedGraph::value_type;

    using difference_type = std::ptrdiff_t;
    /**
     * @brief 양방향 반복자
     *
     */
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = const value_type*;
    using reference = const value_type&;

    /**
     * @brief vector의 const_iterator
     *
     */
    using iterator_type = typename DirectedGraph::nodes_container_type::const_iterator;

    // 양방향 반복자는 기본 생성자를 제공해야 합니다.
    // 기본 생성자로 생성된 반복자를 사용하는 것은
    // 정의되지 않으므로 초기화 방법은 중요하지 않습니다.
    /**
     * @brief const_directed_graph_iterator의 기본 생성자
     *
     */
    const_directed_graph_iterator() = default;

    // 그래프의 소유권을 양도하지 않습니다.
    const_directed_graph_iterator(iterator_type it, const DirectedGraph* graph);

    /**
     * @brief 간접 참조 연산
     *
     * @return reference 노드의 값에대한 참조
     */
    reference operator*() const;

    // 리턴 타입은 ->를 적용할 수 있는 포인터
    /**
     * @brief 포인터로 멤버 메서드 접근 연산
     *
     * @return pointer 노드의 값에 대한 포인터
     */
    pointer operator->() const;

    /**
     * @brief 전위 증가 연산자
     *
     * @return const_directed_graph_iterator&
     */
    const_directed_graph_iterator& operator++();
    /**
     * @brief 후위 증가 연산자
     *
     * @return const_directed_graph_iterator
     */
    const_directed_graph_iterator operator++(int);

    /**
     * @brief 전위 감소 연산자
     *
     * @return const_directed_graph_iterator&
     */
    const_directed_graph_iterator& operator--();
    /**
     * @brief 후위 감소 연산자
     *
     * @return const_directed_graph_iterator
     */
    const_directed_graph_iterator operator--(int);

    // C++20 default operator==
    bool operator==(const const_directed_graph_iterator&) const = default;
    /*
    template <typename DirectedGraph>
    bool const_directed_graph_iterator<DirectedGraph>::operator==(
    const const_directed_graph_iterator<DirectedGraph>& rhs) const {
        // All fields, including the directed_graph to which the iterators refer,
        // must be equal.
        return (m_graph == rhs.m_graph && m_nodeIterator == rhs.m_nodeIterator);
    }
    template <typename DirectedGraph>
    bool const_directed_graph_iterator<DirectedGraph>::operator!=(
    const const_directed_graph_iterator<DirectedGraph>& rhs) const {
        return !(*this == rhs);
    }
    */
   protected:
    friend class directed_graph<value_type>;

    /**
     * @brief vector의 const_iterator
     *
     */
    iterator_type m_nodeIterator;
    const DirectedGraph* m_graph{nullptr};

    /**
     * @brief operator++, operator--에 대한 헬퍼 메서드
     *
     */
    void increment();
    void decrement();
};

/**
 * @brief 즉, directed_graph_iterator 클래스는
 * const_directed_graph_iterator와 마찬가지로
 * directed_graph 클래스의 반복자 역할을 합니다.
 * 다만 반복자가 참조하는 요소를 변경할 수 있는(non-const) 참조자와
 * 포인터를 반환하며, operator* 및 operator->는 상수성(const)을 갖지 않습니다.
 *
 */

template <typename DirectedGraph>
class directed_graph_iterator : public const_directed_graph_iterator<DirectedGraph> {
   public:
    /**
     * @brief iterator_traits 5가지 정의
     *
     */
    using value_type = typename DirectedGraph::value_type;

    using difference_type = std::ptrdiff_t;
    /**
     * @brief 양방향 반복자
     *
     */
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = const value_type*;
    using reference = const value_type&;

    /**
     * @brief vector의 const_iterator
     *
     */
    using iterator_type = typename DirectedGraph::nodes_container_type::iterator;

    directed_graph_iterator() = default;
    directed_graph_iterator(iterator_type it, const DirectedGraph* graph);

    reference operator*();
    pointer operator->();

    directed_graph_iterator& operator++();
    directed_graph_iterator operator++(int);
    
    directed_graph_iterator& operator--();
    directed_graph_iterator operator--(int);
};