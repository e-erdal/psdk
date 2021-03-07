file(GLOB_RECURSE source src/*.cpp)

add_executable(itemeditor WIN32
    ${source}
)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(itemeditor
    PUBLIC
        sdk
)

install(TARGETS itemeditor DESTINATION bin/${CMAKE_BUILD_TYPE})