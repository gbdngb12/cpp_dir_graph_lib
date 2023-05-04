project(graph_node)

add_library(${PROJECT_NAME} "graph_node.cpp")

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        directed_graph
)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "graph_node.h")

# specify the include directory for the library
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})