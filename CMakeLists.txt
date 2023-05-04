cmake_minimum_required(VERSION 3.5)
project(graph)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("graph_node")
add_subdirectory("directed_graph")
add_subdirectory("util")
add_subdirectory("directed_graph_iterator")
add_subdirectory("adjacent_nodes_iterator")

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
          util
          graph_node
          directed_graph
          directed_graph_iterator
)