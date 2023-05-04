#pragma once
#include <cstddef>
#include <iterator>

#include "directed_graph.h"

/**
 * @brief 전방 선언
 *
 * @tparam T
 */
template <typename T>
class directed_graph;

template <typename DirectedGraph>
class const_directed_graph_iterator {
   public:
    /**
     * @brief 표준 라이브러리 반복자를 위한 5가지 iterator_traits
     *
     */
    using value_type = typename DirectedGraph::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = const value_type*;
    using reference = const value_type&;
    using iterator_type =
        typename DirectedGraph::nodes_container_type::const_iterator;
    // Bidirectional iterators must supply a default constructor.
    // Using an iterator constructed with the default constructor
    // is undefined, so it doesn't matter how it's initialized.
    const_directed_graph_iterator() = default;
    // No transfer of ownership of graph.
    const_directed_graph_iterator(iterator_type it,
                                  const DirectedGraph* graph);
    reference operator*() const;
    // Return type must be something to which -> can be applied.
    // So, return a pointer.
    pointer operator->() const;
    const_directed_graph_iterator& operator++();
    const_directed_graph_iterator operator++(int);
    const_directed_graph_iterator& operator--();
    const_directed_graph_iterator operator--(int);
    // C++20 defaulted operator==.
    bool operator==(const const_directed_graph_iterator&) const = default;

   protected:
    friend class directed_graph<value_type>;
    iterator_type m_nodeIterator;
    const DirectedGraph* m_graph{nullptr};
    // Helper methods for operator++ and operator--
    void increment();
    void decrement();
};

template <typename DirectedGraph>
class directed_graph_iterator : public const_directed_graph_iterator<DirectedGraph> {
    /**
     * @brief 표준 라이브러리 반복자를 위한 5가지 iterator_traits
     * 
     */
   public:
    using value_type = typename DirectedGraph::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_type =
        typename DirectedGraph::nodes_container_type::iterator;
    
    directed_graph_iterator() = default;
    directed_graph_iterator(iterator_type it, const DirectedGraph* graph);

    reference operator*();
    pointer operator->();

    directed_graph_iterator& operator++();
    directed_graph_iterator operator++(int);

    directed_graph_iterator& operator--();
    directed_graph_iterator operator--(int);
};