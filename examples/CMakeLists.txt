add_executable(simple_table simple_table.cpp)
target_include_directories(simple_table PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(simple_table PRIVATE omni-table)

add_executable(multiple_styling multiple_styling.cpp)
target_include_directories(multiple_styling PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(multiple_styling PRIVATE omni-table)

add_executable(non_subscript_table non_subscript_table.cpp)
target_include_directories(non_subscript_table PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(non_subscript_table PRIVATE omni-table)




