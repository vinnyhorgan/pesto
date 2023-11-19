cmake_minimum_required(VERSION 3.12)
project(pesto)

set(CMAKE_C_STANDARD 11)

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_WINSOCK_DEPRECATED_NO_WARNINGS)
    add_compile_options(/wd4018 /wd4090 /wd4244 /wd4267)
endif()

add_subdirectory(deps/raylib)

add_subdirectory(deps/luajit luajit)
set_target_properties(luajit PROPERTIES EXCLUDE_FROM_ALL 1)
include_directories(deps/luajit/src ${CMAKE_BINARY_DIR}/luajit)

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

target_link_libraries(${PROJECT_NAME} raylib libluajit)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")
