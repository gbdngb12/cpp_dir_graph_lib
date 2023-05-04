project(directed_graph)

add_library(${PROJECT_NAME} "directed_graph.cpp")

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        graph_node
        directed_graph_iterator
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "directed_graph.h")

# specify the include directory for the library
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})