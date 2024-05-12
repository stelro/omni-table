
# Function to add a Benchmark Test
function(add_benchmark test_name test_file)
    # Initialize variables for libraries and includes
    set(libraries)
    set(includes)

    # Parse arguments
    set(state "SOURCES")
    foreach(arg ${ARGN})
        if(arg STREQUAL "LIB")
            set(state "LIBRARIES")
        elseif(arg STREQUAL "INCLUDES")
            set(state "INCLUDES")
        else()
            if(state STREQUAL "LIBRARIES")
                list(APPEND libraries ${arg})
            elseif(state STREQUAL "INCLUDES")
                list(APPEND includes ${arg})
            endif()
        endif()
    endforeach()

    if (ARCH_LNX86)
        set(BENCHMARK_PATH ${CMAKE_SOURCE_DIR}/external/google-benchmark/lnx86)
    else()
        set(BENCHMARK_PATH ${CMAKE_SOURCE_DIR}/external/google-benchmark/mca64)
    endif()

    include_directories(${includes})
    add_executable(${test_name} ${test_file})
    target_include_directories(${test_name} PRIVATE ${BENCHMARK_PATH}/include)
    target_link_libraries(${test_name} ${libraries})
    target_link_libraries(${test_name} PRIVATE Threads::Threads${libraries})
    target_link_libraries(${test_name} PRIVATE ${BENCHMARK_PATH}/lib/libbenchmark.a)
    target_compile_options(${test_name} PUBLIC
        -Wno-unused-parameter
        -Wno-unused-function
        -Wno-unused-variable
        -Wno-double-promotion
        )
    add_test(NAME ${test_name} COMMAND ${test_name})

endfunction(add_benchmark)

# usage example
# add_benchmark(
#     my_test 
#     my_test.cpp 
#     LIB
#     my_additional_library1 my_additional_library2
#     INCLUDES
#     my_include_directory1 my_include_directory2
# )

