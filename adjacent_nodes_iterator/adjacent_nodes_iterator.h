#pragma once
#include <cstddef>
#include <iterator>
#include <set>
template <typename GraphType>
class const_adjacent_nodes_iterator {
   public:
    using value_type = typename GraphType::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = const value_type*;
    using reference = const value_type&;
    using iterator_type = std::set<size_t>::const_iterator;

    // Bidirectional iterators must supply a default constructor.
    // In this case, the default-constructed iterator serves as an
    // end iterator.
    const_adjacent_nodes_iterator() = default;

    // No transfer of ownership of graph.
    const_adjacent_nodes_iterator(iterator_type it, const GraphType* graph);

    reference operator*() const;

    // Return type must be something to which -> can be applied.
    // Return a pointer to a node, to which the compiler
    // will apply -> again.
    pointer operator->() const;

    const_adjacent_nodes_iterator& operator++();
    const_adjacent_nodes_iterator operator++(int);

    const_adjacent_nodes_iterator& operator--();
    const_adjacent_nodes_iterator operator--(int);

    // The following are ok as member functions because we don't
    // support comparisons of different types to this one.
    bool operator==(const const_adjacent_nodes_iterator& rhs) const;
    bool operator!=(const const_adjacent_nodes_iterator& rhs) const;

   protected:
    iterator_type m_adjacentNodeIterator;
    // If nullptr, then this instance is an end iterator.
    const GraphType* m_graph{nullptr};

    // Helper methods for operator++ and operator--
    void increment();
    void decrement();
};

template <typename GraphType>
class adjacent_nodes_iterator : public const_adjacent_nodes_iterator<GraphType> {
   public:
    using value_type = typename GraphType::value_type;
    using difference_type = ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_type = std::set<size_t>::iterator;

    // Bidirectional iterators must supply a default constructor.
    // In this case, the default-constructed iterator serves as an
    // end iterator.
    adjacent_nodes_iterator() = default;

    // No transfer of ownership of graph.
    adjacent_nodes_iterator(iterator_type it, const GraphType* graph);

    reference operator*();

    // Return type must be something to which -> can be applied.
    // Return a pointer to a node, to which the compiler
    // will apply -> again.
    pointer operator->();

    adjacent_nodes_iterator& operator++();
    adjacent_nodes_iterator operator++(int);

    adjacent_nodes_iterator& operator--();
    adjacent_nodes_iterator operator--(int);
};