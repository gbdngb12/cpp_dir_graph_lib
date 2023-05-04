#pragma once
#include <cstddef>
#include <set>
#include <vector>

#include "graph_node.h"

template <typename T>
class directed_graph {
   public:
    /**
     * @brief 노드의 값으로 노드를 삽입한다.
     *
     * @param node_value 노드의 값
     * @return true 노드가 성공적으로 삽입
     * @return false 노드가 이미 존재
     */
    bool insert(const T& node_value);
    /**
     * @brief 노드의 값으로 노드를 삽입
     *
     * @param node_value 노드의 값
     * @return true 노드가 성공적으로 삽입
     * @return false 노드가 이미 존재
     */
    bool insert(T&& node_value);

    /**
     * @brief 노드의 값으로 노드를 제거
     *
     * @param node_value 제거할 노드의 값
     * @return true 노드가 성공적으로 제거
     * @return false 노드 제거 실패(없는 경우)
     */
    bool erase(const T& node_value);

    /**
     * @brief 간선(edge) 삽입
     *
     * @param from_node_value 시작 노드 값
     * @param to_node_value 목적지 노드 값
     * @return true 간선 삽입 성공
     * @return false 간선 삽입 실패
     */
    bool insert_edge(const T& from_node_value, const T& to_node_value);

    /**
     * @brief 간선(edge) 삭제
     *
     * @param from_node_value 간선의 출발지 노드 값
     * @param to_node_value 간선의 목적지 노드 값
     * @return true
     * @return false
     */
    bool erase_edge(const T& from_node_value, const T& to_node_value);

    /**
     * @brief 모든 간선 및 노드 제거
     *
     */
    void clear() noexcept;

    /**
     * @brief 인덱스로 노드 값의 레퍼런스 접근
     *
     * @param index 인덱스
     * @return T& 노드 값의 레퍼런스
     */
    T& operator[](std::size_t index);
    /**
     * @brief 인덱스로 노드 값의 const 레퍼런스 접근
     *
     * @param index 인덱스
     * @return const T& 노드 값의 const 레퍼런스
     */
    const T& operator[](std::size_t index) const;

    /**
     * @brief 두 방향 그래프가 일치하는지 확인한다.
     *
     * @param rhs 비교할 방향 그래프
     * @return true
     * @return false
     */
    bool operator==(const directed_graph& rhs) const;
    /**
     * @brief 두 방향 그래프가 일치하지 않는지 확인한다.
     *
     * @param rhs 비교할 방향 그래프
     * @return true
     * @return false
     */
    bool operator!=(const directed_graph& rhs) const;

    /**
     * @brief 다른 방향그래프와 노드 및 인접리스트등의 모든것을 교체한다.
     *
     * @param other_graph 교체할 방향 그래프
     */
    void swap(directed_graph& other_graph) noexcept;

    /**
     * @brief 방향 그래프안의 모든 노드의 수를 리턴한다.
     *
     * @return std::size_t 방향 그래프 안의 모든 노드의 수
     */
    [[nodiscard]] std::size_t size() const noexcept;

    /**
     * @brief 노드의 값으로 인접 행렬의 값 리스트를 가져온다.
     *
     * @param node_value 노드의 값
     * @return std::set<T> 인접 행렬의 값 리스트
     */
    [[nodiscard]] std::set<T> get_adjacent_nodes_values(const T& node_value) const;

   private:
    /**
     * @brief 노드들을 저장하는 타입 (vector<graph_node>)
     *
     */
    using nodes_container_type = std::vector<details::graph_node<T>>;

    /**
     * @brief 노드들을 저장하는 벡터 변수
     *
     */
    nodes_container_type m_nodes;

    /**
     * @brief 노드의 값으로 노드의 반복자를 리턴한다.
     *
     * @param node_value 노드의 값
     * @return nodes_container_type::iterator 찾은 노드의 반복자
     */
    typename nodes_container_type::iterator findNode(const T& node_value);

    /**
     * @brief 노드의 값으로 노드의 const 반복자를 리턴한다.
     *
     * @param node_value 노드의 값
     * @return nodes_container_type::const_iterator 찾은 노드의 const 반복자
     */
    typename nodes_container_type::const_iterator findNode(const T& node_value) const;

    /**
     * @brief 노드의 반복자로부터 노드의 인덱스를 얻는 함수
     *
     * @param node 노드의 반복자
     * @return std::size_t 노드의 인덱스
     */
    [[nodiscard]] std::size_t get_index_of_node(
        const typename nodes_container_type::const_iterator& node)
        const noexcept;

    /**
     * @brief 해당 노드를 참조하는 인접리스트도 삭제하고 노드도 삭제한다.
     *
     * @param node_iter 삭제하고자 하는 노드의 반복자
     */
    void remove_all_links_to(typename nodes_container_type::const_iterator node_iter);

    /**
     * @brief 인덱스 인접리스트로 부터 값 인접 리스트를 얻는다.
     *
     * @tparam T
     * @param indices 인덱스 인접 리스트
     * @return std::set<T> 값 인접 리스트
     */
    [[nodiscard]] std::set<T> get_adjacent_nodes_values(
        const typename details::graph_node<T>::adjacency_list_type& indices) const;
};