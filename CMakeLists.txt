cmake_minimum_required (VERSION 3.13)

project ("Homework 1: Bracket Checking")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library target for stack
#add_library(stack STATIC)

#target_sources(stack PRIVATE src/StackDynamicArray.h)


# Library target for the solution
add_library(solution STATIC)

target_sources(solution PRIVATE src/solution.cpp src/solution.h)

#target_link_libraries(solution PRIVATE stack)


# Executable target for the application
add_executable(checker)

target_link_libraries(checker PRIVATE solution Catch2::Catch2WithMain)

target_sources(checker PRIVATE src/application.cpp)


#
# Make Catch2 available. For more information check
# https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md
#
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.1.1)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)


# Executable target for the solution tests
add_executable(testing_solution)

target_link_libraries(testing_solution PRIVATE solution Catch2::Catch2WithMain)

target_include_directories(testing_solution PRIVATE "src")

target_sources(testing_solution PRIVATE test/solution.cpp)


# Executable target for the stack tests
add_executable(testing_stack)

target_link_libraries(testing_stack PRIVATE Catch2::Catch2WithMain)

target_include_directories(testing_stack PRIVATE "src")

target_sources(testing_stack PRIVATE test/StackDynamicArray_test.cpp)


# Automatically register all tests
include(CTest)
include(Catch)
catch_discover_tests(testing_solution)
catch_discover_tests(testing_stack)
