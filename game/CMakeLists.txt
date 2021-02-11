file(GLOB_RECURSE source src/*.cpp)

add_executable(game WIN32
    ${source}
)

target_link_libraries(game
    PUBLIC
        shared
)