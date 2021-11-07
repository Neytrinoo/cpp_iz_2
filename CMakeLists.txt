cmake_minimum_required(VERSION 3.20)
project(cpp_iz_2)

add_compile_options("--coverage")

set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -ftest-coverage -fprofile-arcs")

# synchronous static lib
aux_source_directory(sync_lib/src SOURCE_SYNC_LIB)
add_library(sync_library STATIC ${SOURCE_SYNC_LIB})
target_include_directories(sync_library PUBLIC sync_lib/include)

find_package(GTest REQUIRED)

# asynchronous dynamic lib
aux_source_directory(async_lib/src SOURCE_ASYNC_LIB)
add_library(async_library SHARED ${SOURCE_ASYNC_LIB})
target_include_directories(async_library PUBLIC async_lib/include)
target_link_libraries(async_library pthread)

add_executable(cpp_iz_2 main.c)
target_link_libraries(cpp_iz_2 async_library)

add_executable(unit_tests_sync unit_tests/main.cpp)
target_link_libraries(unit_tests_sync sync_library ${GTEST_LIBRARIES} Threads::Threads gcov)

add_executable(unit_tests_async unit_tests/main.cpp)
target_link_libraries(unit_tests_async async_library ${GTEST_LIBRARIES} Threads::Threads gcov)
