add_executable(SimpleTable SimpleTable.cpp)
target_include_directories(SimpleTable PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(SimpleTable PRIVATE gc-table)