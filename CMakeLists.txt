cmake_minimum_required(VERSION 3.12)
project(pesto)

set(CMAKE_C_STANDARD 11)

add_subdirectory(deps/raylib)
add_subdirectory(deps/lua)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib lua_static)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
