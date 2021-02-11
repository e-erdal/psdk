file(GLOB_RECURSE source *.cpp)

add_library(shared
    ${source}
)

target_link_libraries(shared
    PUBLIC
)