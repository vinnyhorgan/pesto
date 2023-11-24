cmake_minimum_required(VERSION 3.12)
project(pesto)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
    add_compile_options(/wd4018 /wd4090)
endif()

set(OPENGL_VERSION 4.3 CACHE STRING "")
add_subdirectory(deps/raylib)

add_subdirectory(deps/luajit)
include_directories(deps/luajit/src)

set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "")
add_subdirectory(deps/box2d)

add_definitions(-DNO_FONT_AWESOME)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c src/*.cpp)

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

target_link_libraries(${PROJECT_NAME} raylib libluajit box2d)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")
