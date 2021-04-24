cmake_minimum_required(VERSION 3.16)
project(my_cURL)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/23ef29555ef4789f555f1ba8c51b4c52975f0907.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB my_cURL_SRC CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )

file(GLOB my_cURL_tests_SRC CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )

list(REMOVE_ITEM my_cURL_tests_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

message("${my_cURL_tests_SRC}")

add_executable(my_cURL ${my_cURL_SRC})
add_executable(my_cURL_tests ${my_cURL_tests_SRC})
target_link_libraries(my_cURL_tests gtest_main)
