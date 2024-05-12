add_gtest(
    TableTest 
    TableTest.t.cpp
    LIB
    gc-table
    INCLUDES
    ${CMAKE_SOURCE_DIR}/src
)
