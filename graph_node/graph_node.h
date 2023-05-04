#pragma once
#include <cstddef>
#include <set>


/**
 * @brief 방향 그래프 클래스 전방 선언
 *
 * @tparam T
 */
template <typename T>
class directed_graph;

namespace details {
template <typename T>
class graph_node {
   public:
    /**
     * @brief 그래프 노드 객체 생성
     *
     * @param graph 연결할 원본 그래프
     * @param t 저장할 값
     */
    graph_node(directed_graph<T>* graph, const T& t);
    /**
     * @brief 그래프 노드 객체 생성
     *
     * @param graph 연결할 원본 그래프
     * @param t 저장할 값
     */
    graph_node(directed_graph<T>* graph, T&& t);

    /**
     * @brief 노드 값의 참조를 리턴
     *
     * @return T& 노드 값의 참조
     */
    [[nodiscard]] T& value() noexcept;
    /**
     * @brief 노드 값의 const 참조를 리턴
     *
     * @return const T& 노드 값의 const 참조
     */
    [[nodiscard]] const T& value() const noexcept;

    /**
     * @brief 노드값 비교함수
     *
     * @return true 노드의 값이 일치
     * @return false 노드의 값이 일치 하지 않음
     */
    bool operator==(const graph_node&) const = default;

   private:
    /**
     * @brief 바양 그래프에서 노드의 모든 값에 접근 하기위해서
     *
     */
    friend class directed_graph<T>;

    /**
     * @brief 원본 방향 그래프의 포인터
     *
     */
    directed_graph<T>* m_graph;

    /**
     * @brief 인접 인덱스 리스트의 타입
     *
     */
    using adjacency_list_type = std::set<std::size_t>;

    /**
     * @brief 인접노드 인덱스의 리스트의 참조를 가져오는 함수 getter
     *
     * @return adjacency_list_type& 인접 노드 인덱스 리스트의 참조
     */
    [[nodiscard]] adjacency_list_type& get_adjacent_nodes_indices();

    /**
     * @brief 인접노드 인덱스의 리스트의 const 참조를 가져오는 함수 getter
     *
     * @return const adjacency_list_type& 인접 노드 인덱스 리스트의 const 참조
     */
    [[nodiscard]] const adjacency_list_type& get_adjacent_nodes_indices() const;

    /**
     * @brief 노드의 값
     *
     */
    T m_data;
    /**
     * @brief 인접노드 인덱스 리스트
     *
     */
    adjacency_list_type m_adjacentNodeIndices;
};

}  // namespace details

#include "directed_graph.h"