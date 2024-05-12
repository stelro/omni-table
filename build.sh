#!/bin/bash

clean_build=1
dev_only=0
rel_only=0
run_tests=0

parse_arguments() {
    for arg in "$@"
    do
        case $arg in
            --no-clean)
                clean_build=0
                shift
                ;;
            --dev)
                dev_only=1
                clean_build=0
                shift
                ;;
            --rel)
                rel_only=1
                clean_build=0
                shift
                ;;
            --test)
                run_tests=1
                shift
                ;;
            *)
                # Unknown option
                shift
                ;;
        esac
    done
}

# Function to clean build artifacts
clean_artifacts() {
    local build_type=$1
    echo "Cleaning build artifacts for $build_type..."
    rm -rf build/$build_type
}

# Function to build the project with specified build type
build_project() {
    local build_type=$1
    local build_name=$2
    local build_params=$3
    local start_time=$(date +%s)

    echo "*** Start building target $build_name ***"

    if [ $clean_build -eq 1 ]; then
        clean_artifacts $build_name
    fi

    mkdir -p build/$build_name
    cd build/$build_name

    # Run CMake with the specified build type and Ninja generator
    cmake -DCMAKE_BUILD_TYPE=$build_type $build_params -G Ninja ../..

    # Build the project
    ninja

    if [ "$build_type" == "Debug" ]; then
        cp compile_commands.json ../../
    fi

    echo "*** Finish building target $build_name ***"

    local end_time=$(date +%s)
    echo "Total build time for $build_name: $((end_time - start_time)) seconds"

    cd - > /dev/null
}

# Function to run unit tests
run_unit_tests() {
    echo "Running unit tests..."

    for dir in build/debug/tests; do
        if [ -d "$dir" ]; then
            echo "Running tests in $dir..."
            (cd "$dir" && ctest . -V)
        else
            echo "Test directory $dir does not exist."
        fi
    done
}

# Parse script arguments
parse_arguments "$@"

# Build based on the arguments
if [ $dev_only -eq 1 ]; then
    build_project Debug debug "-DENABLE_SANITIZER_ADDRESS=ON"
elif [ $run_tests -eq 1 ]; then
    run_unit_tests
elif [ $rel_only -eq 1 ]; then
    build_project Release release
else
    # debug build is by default built as asan
    build_project Release release
    build_project Debug debug "-DENABLE_SANITIZER_ADDRESS=ON"
    build_project Debug debug_noasan
fi

echo "*** Finish building project ***"
