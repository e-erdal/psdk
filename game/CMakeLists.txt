file(GLOB_RECURSE source src/*.cpp)

add_executable(game
    ${source}
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(game
    PUBLIC
        sdk
)