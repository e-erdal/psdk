file(GLOB_RECURSE source *.cpp)

add_library(shared STATIC
    ${source}
)

include_directories(
    ${GLFW_INCLUDE_DIRS}
)

target_precompile_headers(shared PUBLIC pch.h)

target_include_directories(shared PUBLIC .)

target_link_libraries(shared
    PUBLIC
        glad
        glfw
)