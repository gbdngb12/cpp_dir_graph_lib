project(adjacnet_nodes_iterator)

add_library(${PROJECT_NAME} "adjacnet_nodes_iterator.cpp")

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        directed_graph
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "adjacnet_nodes_iterator.h")

# specify the include directory for the library
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})