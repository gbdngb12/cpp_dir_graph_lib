#pragma once
#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>
#include <initializer_list>
#include "adjacent_nodes_iterator.h"
#include "directed_graph_iterator.h"
#include "graph_node.h"

template <typename T>
class const_directed_graph_iterator;

template <typename T>
class directed_graph_iterator;

template <typename T>
class adjacent_nodes_iterator;

template <typename T>
class const_adjacent_nodes_iterator;

template <typename T>
class directed_graph {
   public:
    /**
     * @brief type_alias 조건들
     * 아직 iterator, const_iterator는 생략
     */
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    /**
     * @brief 반복자 지원을 위한 type_alias 조건
     * iterator와 const_iterator는 모두 const_directed_graph_iterator의
     * 타입 별칭이며, directed_graph 반복자가 참조하는 값에 대해 사용자가 수정할 수 없음
     */
    using iterator = const_directed_graph_iterator<directed_graph>;
    using const_iterator = const_directed_graph_iterator<directed_graph>;
    /**
     * @brief 역방향 반복자 지원을 위한 타입 앨리어스
     *
     */
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    /**
     * @brief 역방향 반복자 지원을 위한 메서드
     *
     */
    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    const_reverse_iterator crend() const noexcept;

    /**
     * @brief 인접노드를 순회하기 위한 반복자 타입 앨리어스
     *
     */
    using iterator_adjacent_nodes = adjacent_nodes_iterator<directed_graph>;
    using const_iterator_adjacent_nodes = const_adjacent_nodes_iterator<directed_graph>;
    using reverse_iterator_adjacent_nodes = std::reverse_iterator<iterator_adjacent_nodes>;
    using const_reverse_iterator_adjacent_nodes = std::reverse_iterator<const_iterator_adjacent_nodes>;

    /**
     * @brief 인접 노드를 순회하는 반복자를 위한 메서드
     *
     */
    iterator_adjacent_nodes begin(const T& node_value) noexcept;
    iterator_adjacent_nodes end(const T& node_value) noexcept;
    const_iterator_adjacent_nodes begin(const T& node_value) const noexcept;
    const_iterator_adjacent_nodes end(const T& node_value) const noexcept;
    const_iterator_adjacent_nodes cbegin(const T& node_value) const noexcept;
    const_iterator_adjacent_nodes cend(const T& node_value) const noexcept;
    // Return reverse iterators to the list of adjacent nodes for a given node.
    // Return a default constructed one as end iterator if value is not found.
    reverse_iterator_adjacent_nodes rbegin(const T& node_value) noexcept;
    reverse_iterator_adjacent_nodes rend(const T& node_value) noexcept;
    const_reverse_iterator_adjacent_nodes rbegin(const T& node_value)
        const noexcept;
    const_reverse_iterator_adjacent_nodes rend(const T& node_value)
        const noexcept;
    const_reverse_iterator_adjacent_nodes crbegin(const T& node_value)
        const noexcept;
    const_reverse_iterator_adjacent_nodes crend(const T& node_value)
        const noexcept;

    /**
     * @brief 표준 라이브러리와 비슷한 기능을 하는 추가적인 함수
     * 
     */
    template<typename Iter>
    void assign(Iter first, Iter last);

    void assign(std::initializer_list<T> init);

    void insert(std::initializer_list<T> init);

    directed_graph() = default;
    directed_graph(std::initializer_list<T> init);

    directed_graph<T>& operator=(std::initializer_list<T> init);

    /**
     * @brief 표준 라이브러리를 위한 메서드 조건들
     */

    [[nodiscard]] size_type size() const noexcept;
    [[nodiscard]] size_type max_size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

    /**
     * @brief iterator 지원을 위한 메서드 조건들
     *
     */
    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    /**
     * @brief 경계 검사를 수행하는 멤버 인덱스 접근 함수
     *
     */
    reference at(size_type index);
    const_reference at(size_type index) const;

    /**
     * @brief 노드를 삽입한다. 삽입이 성공하려면 값이 아직 그래프에 없어야 합니다.
     *
     * @param node_value 삽입할 노드의 값
     * @return true 주어진 값을 가진 새 노드가 그래프에 추가된 경우
     * @return false 주어진 값을 가진 노드가 이미 있는 경우
     */
    /**
     * 표준 라이브러리의 철학을 따르기위해 std::pair<iterator, bool>을 리턴
     */
    std::pair<iterator, bool> insert(const T& node_value);
    std::pair<iterator, bool> insert(T&& node_value);
    /**
     * @brief iterator hint를 받도록 수정되었습니다. 이 hint는 directed_graph에는 쓸모가 없지만, std::set과 같은 다른 Standard Library container들과의 대칭성을 유지하기 위해 제공되었습니다. 이 hint는 무시되며, 그냥 hint 없는 버전의 insert()를 호출
     *
     */
    iterator insert(const_iterator hint, const T& node_value);
    iterator insert(const_iterator hint, T&& node_value);
    /**
     * @brief 반복자의 범위를 받는 insert
     *
     * @tparam Iter
     * @param first
     * @param last
     */
    template <typename Iter>
    void insert(Iter first, Iter last);

    /**
     * @brief 노드의 값을 지운다.
     *
     * @param node_value 노드의 값
     * @return true 주어진 노드 값이 지워진 경우
     * @return false 주어진 노드 값이 지워지지 않은 경우
     */
    /**
     * 표준 라이브러리의 원칙을 따르기위해 하나는 반복자가 참조하는 노드를 지운다.
     * 반복자 범위로 지정된 노드 지우기
     * 둘다 마지막 삭제된 노드 다음의 노드를 기리키는 반복자 리턴
     */
    bool erase(const T& node_value);
    /**
     * @brief 반복자가 참조하는 노드를 지운다
     *
     * @param pos 반복자 위치
     * @return iterator 삭제된 다음의 노드 반복자
     */
    iterator erase(const_iterator pos);
    /**
     * @brief 반복자 범위로 지정된 노드 지우기
     *
     * @param first 첫번째 노드
     * @param last 두번째 노드
     * @return iterator 삭제된 다음의 노드 반복자
     */
    iterator erase(const_iterator first, const_iterator last);

    /**
     * @brief 간선(Edge)이 생성한다.
     *
     * @param from_node_value 출발지 노드 값
     * @param to_node_value 목적지 노드 값
     * @return true 간선(Edge)가 성공적으로 생성
     * @return false 간선(Edge) 생성 실패
     */
    bool insert_edge(const T& from_node_value, const T& to_node_value);

    /**
     * @brief 주어진 간선(Edge)을 삭제한다.
     *
     * @param from_node_value 출발지 노드 값
     * @param to_node_value 목적지 노드 값
     * @return true 성공적으로 삭제한 경우
     * @return false 삭제에 실패한 경우
     */
    bool erase_edge(const T& from_node_value, const T& to_node_value);

    /**
     * @brief 그래프에서 모든 노드를 제거
     *
     */
    void clear() noexcept;

    /**
     * @brief 주어진 인덱스가 있는 노드에 대한 참조를 리턴
     *
     * @param index 노드값에 대한 인덱스
     * @return T& 노드값에 대한 참조
     */
    reference operator[](size_t index);
    const_reference operator[](size_t index) const;

    // 노드와 간선이 동일한 두 방향 그래프는 동일합니다.
    // 노드와 에지가 추가된 순서는 동등성에 영향을 미치지 않습니다.
    /**
     * @brief 두개의 방향 그래프가 동일한지 확인한다.
     *
     * @param rhs
     * @return true 두개의 방향그래프가 동일한 경우
     * @return false 두개의 방향그래프가 동일하지 않은 경우
     */
    bool operator==(const directed_graph& rhs) const;
    bool operator!=(const directed_graph& rhs) const;

    /**
     * @brief 이 그래프와 주어진 그래프 사이의 모든 노드를 교환
     *
     * @param other_graph 교환할 그래프
     */
    void swap(directed_graph& other_graph) noexcept;

    /**
     * @brief 그래프의 노드 수를 리턴
     *
     * @return size_t 그래프의 노드 수
     */
    //[[nodiscard]] size_t size() const noexcept;

    //
    // 주어진 노드가 존재하지 않으면 빈 집합이 반환됩니다.
    /**
     * @brief 주어진 노드의 인접 노드의 값리스트의 집합을 리턴
     *
     * @param node_value 찾고자하는 노드의 값
     * @return std::set<T> 인접노드의 값 리스트
     */
    [[nodiscard]] std::set<T> get_adjacent_nodes_values(const T& node_value) const;

   private:
    // friend details::graph_node<T>;
    using nodes_container_type = std::vector<details::graph_node<T>>;
    /**
     * @brief 노드들의 목록, std::vector로 관리
     *
     */
    nodes_container_type m_nodes;

    /**
     * @brief node를 찾아 반복자를 리턴
     *
     * @param node_value 노드 값
     * @return nodes_container_type::iterator 노드 값의 iterator
     */
    typename nodes_container_type::iterator findNode(const T& node_value);
    /**
     * @brief node를 찾아 반복자를 리턴
     *
     * @param node_value 노드 값
     * @return nodes_container_type::const_iterator 노드 값의 const_iterator
     */
    typename nodes_container_type::const_iterator findNode(const T& node_value) const;

    /**
     * @brief 표준 라이브러리 지원을 위한 find()
     *
     */
    iterator find(const T& node_value);
    const_iterator find(const T& node_value) const;

    /**
     * @brief 노드에 반복자에서 노드의 인덱스를 리턴
     *
     * @param node 노드의 반복자
     * @return size_t 해당 노드의 인덱스
     */
    [[nodiscard]] size_t get_index_of_node(const typename nodes_container_type::const_iterator& node) const noexcept;

    /**
     * @brief 노드에 반복자를 통해 다른 노드들의 인접 목록에서 해당 노드를 제거
     *
     * @param node_iter 노드의 반복자
     */
    void remove_all_links_to(typename nodes_container_type::const_iterator node_iter);

    /**
     * @brief 인접 노드 인덱스 집합을 해당 노드 값 집합을 변환
     *
     * @param indices 인접 인덱스 집합
     * @return std::set<T> 인접노드 값 집합
     */
    [[nodiscard]] std::set<T> get_adjacent_nodes_values(
        const typename details::graph_node<T>::adjacency_list_type& indices) const;

    /**
     * @brief const_directed_graph_iterator 클래스의 iterator_type 타입 앨리어스는
     * directed_graph의 private 타입 앨리어스인 nodes_container_type 타입 앨리어스를 사용하므로
     * friend 클래스로 선언
     *
     */
    friend class const_directed_graph_iterator<directed_graph>;
    friend class directed_graph_iterator<directed_graph>;
};