file(GLOB_RECURSE source *.cpp)

add_library(sdk STATIC
    ${source}
)

include_directories(
    ${GLFW_INCLUDE_DIRS}
)

target_precompile_headers(sdk PUBLIC pch.h)

target_include_directories(sdk PUBLIC .)

target_link_libraries(sdk
    PUBLIC
        glad
        glfw
        glm
)