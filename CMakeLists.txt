cmake_minimum_required(VERSION 3.12)
project(pesto)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS)
    add_compile_options(/wd4005 /wd4018 /wd4090 /wd4244 /wd4996)
endif()

add_subdirectory(deps/luajit)
include_directories(deps/luajit/src)

set(OPENGL_VERSION 4.3 CACHE STRING "")
set(CUSTOMIZE_BUILD ON CACHE BOOL "")
set(SUPPORT_FILEFORMAT_JPG ON CACHE BOOL "")
set(SUPPORT_FILEFORMAT_SVG ON CACHE BOOL "")
add_subdirectory(deps/raylib)

include_directories(deps/fastnoiselite)
include_directories(deps/imgui)
include_directories(deps/rlimgui)
include_directories(deps/rres)
include_directories(deps/utf8)

add_compile_definitions(NO_FONT_AWESOME PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")

set(LIB_SOURCES
    "deps/imgui/imgui_demo.cpp"
    "deps/imgui/imgui_draw.cpp"
    "deps/imgui/imgui_tables.cpp"
    "deps/imgui/imgui_widgets.cpp"
    "deps/imgui/imgui.cpp"
    "deps/rlimgui/rlImGui.cpp"
    "deps/utf8/lutf8lib.c"
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c" "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${LIB_SOURCES})
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
    add_executable(pesto_win ${SOURCES} ${LIB_SOURCES})
    target_link_libraries(pesto_win libluajit raylib ws2_32)
    target_link_options(pesto_win PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
    set_target_properties(pesto_win PROPERTIES OUTPUT_NAME "pesto")
endif()
