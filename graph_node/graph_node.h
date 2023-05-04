#pragma once
#include <set>
#include <utility>
template <typename T>
class directed_graph;
namespace details {
/**
 * @brief 방향 그래프에서 사용할 노드의 구조
 *
 * @tparam T
 */
template <typename T>
class graph_node {
   public:
    /**
     * @brief graph_node를 특정한 값으로 생성한다.
     *
     * @param graph 연결할 방향 그래프의 포인터
     * @param t 저장할 값
     */
    graph_node(directed_graph<T>* graph, const T& t);
    /**
     * @brief graph_node를 특정한 값으로 생성한다.
     * 
     * @param graph 연결할 방향 그래프의 포인터
     * @param t 저장할 값
     */
    graph_node(directed_graph<T>* graph, T&& t);

    /**
     * @brief 저장된 값에대한 레퍼런스를 리턴한다.
     *
     * @return T& 저장된 값에 대한 레퍼런스
     */
    [[nodiscard]] T& value() noexcept;
    [[nodiscard]] const T& value() const noexcept;

    /**
     * @brief C+20 default operator==
     * 기본적으로 opeartor!=도 자동으로 구현 (C++20)
     */
    bool operator==(const graph_node&) const = default;

   private:
    /**
     * @brief directed_graph 클래스는 graph_node에 접근해야 하므로 friend class로 정의한다.
     *
     */
    friend class directed_graph<T>;

    /**
     * @brief 이 노드가 있는 그래프에 대한 포인터.
     * 
     * @if 참조로 변경한다면, 복사/이동 대입 연산자도 직접 구현해야함
     */
    directed_graph<T>* m_graph;

    /**
     * @brief 인접 노드 목록 컨테이너의 타입 앨리어스
     *
     */
    using adjacency_list_type = std::set<std::size_t>;

    /**
     * @brief 인접노드 목록에대한 레퍼런스를 리턴한다.
     *
     */
    [[nodiscard]] adjacency_list_type& get_adjacent_nodes_indices();
    [[nodiscard]] const adjacency_list_type& get_adjacent_nodes_indices() const;

    /**
     * @brief 노드안의 값
     * 
     */
    T m_data;
    
    /**
     * @brief 인접 노드 인덱스 리스트
     *
     */
    adjacency_list_type m_adjacentNodeIndices;
};
}  // namespace details
#include "directed_graph.h"