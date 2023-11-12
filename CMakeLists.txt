cmake_minimum_required(VERSION 3.12)
project(pesto)

set(CMAKE_C_STANDARD 11)

add_subdirectory(deps/raylib)
add_subdirectory(deps/lua)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")

if(WIN32)
    list(REMOVE_ITEM SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/luasocket/serial.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/luasocket/unix.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/luasocket/unixdgram.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/luasocket/unixstream.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/luasocket/usocket.c"
    )
else()
    list(REMOVE_ITEM SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/lib/luasocket/wsocket.c"
    )
endif()

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} raylib lua_static)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
