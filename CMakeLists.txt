cmake_minimum_required(VERSION 3.13)
project(EVREN LANGUAGES CXX C)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_definitions("/MP")
endif()

add_subdirectory(sdk)
add_subdirectory(game)
add_subdirectory(vendor)