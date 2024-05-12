function(enable_sanitizers project_name)

option(ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)

    if (ENABLE_SANITIZER_ADDRESS)
        target_compile_options(${project_name} INTERFACE -fno-omit-frame-pointer -fsanitize=address,undefined)
        target_link_options(${project_name} INTERFACE -fno-omit-frame-pointer -fsanitize=address,undefined)

        if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
            target_link_options(${project_name} INTERFACE -static-libasan)
        endif()
    endif()

    if (ENABLE_SANITIZER_THREAD)
        if (ENABLE_SANITIZER_ADDRESS)
            message(FATAL_ERROR "Can't intermix tsan and asan")
        endif()

        target_compile_options(${project_name} INTERFACE -fno-omit-frame-pointer -fsanitize=thread)
        target_link_options(${project_name} INTERFACE -fno-omit-frame-pointer -fsanitize=thread)

        if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
            target_link_options(${project_name} INTERFACE -static-libtsan)
        endif()
    endif()

endfunction()
