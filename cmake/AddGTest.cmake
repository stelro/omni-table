# Function to add a Google Test
function(add_gtest test_name test_file)
    # Initialize variables for libraries and includes
    set(libraries)
    set(includes)
    set(sources)

    # Parse arguments
    set(state "SOURCES")
    foreach(arg ${ARGN})
        if(arg STREQUAL "LIB")
            set(state "LIBRARIES")
        elseif(arg STREQUAL "INCLUDES")
            set(state "INCLUDES")
        elseif(arg STREQUAL "SOURCES")
            set(state "SOURCES")
        else()
            if(state STREQUAL "LIBRARIES")
                list(APPEND libraries ${arg})
            elseif(state STREQUAL "INCLUDES")
                list(APPEND includes ${arg})
            elseif(state STREQUAL "SOURCES")
                list(APPEND sources ${arg})
            endif()
        endif()
    endforeach()

    include_directories(${includes})
    add_executable(${test_name} ${test_file} ${sources})
    target_link_libraries(${test_name} gtest_main ${libraries})
    target_compile_options(${test_name} PUBLIC
        -Wno-unused-parameter
        -Wno-unused-function
        -Wno-unused-variable
        -Wno-double-promotion
        )
    add_test(NAME ${test_name} COMMAND ${test_name})

endfunction(add_gtest)

# usage example
# add_gtest(
#     my_test 
#     my_test.cpp 
#     LIB
#     my_additional_library1 my_additional_library2
#     INCLUDES
#     my_include_directory1 my_include_directory2
# )


