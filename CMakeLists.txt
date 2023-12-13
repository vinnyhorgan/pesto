cmake_minimum_required(VERSION 3.12)
project(pesto)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS)
    add_compile_options(/wd4005 /wd4018 /wd4996)
endif()

add_subdirectory(deps/luajit)
include_directories(deps/luajit/src)

set(OPENGL_VERSION 4.3 CACHE STRING "")
set(CUSTOMIZE_BUILD ON CACHE BOOL "")
set(SUPPORT_FILEFORMAT_JPG ON CACHE BOOL "")
set(SUPPORT_FILEFORMAT_SVG ON CACHE BOOL "")
add_subdirectory(deps/raylib)

add_compile_definitions(NO_FONT_AWESOME PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c" "src/*.cpp")

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
target_link_libraries(${PROJECT_NAME} libluajit raylib)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "pestoc")
    add_executable(pesto_win ${SOURCES})
    target_link_libraries(pesto_win libluajit raylib ws2_32)
    target_link_options(pesto_win PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
    set_target_properties(pesto_win PROPERTIES OUTPUT_NAME "pesto")
endif()
