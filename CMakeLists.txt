cmake_minimum_required(VERSION 3.12)
project(pesto)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

add_compile_definitions(PROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/" NO_FONT_AWESOME)

if(MSVC)
    add_compile_options(/wd4013 /wd4090 /wd4244 /wd4996)
endif()

add_subdirectory(deps/enet)
include_directories(deps/enet/include)

add_subdirectory(deps/luajit)
include_directories(deps/luajit/src)

set(OPENGL_VERSION 4.3 CACHE STRING "")
set(CUSTOMIZE_BUILD ON CACHE BOOL "")
set(SUPPORT_FILEFORMAT_JPG ON CACHE BOOL "")
set(SUPPORT_FILEFORMAT_SVG ON CACHE BOOL "")
add_subdirectory(deps/raylib)

include_directories(deps/fastnoiselite)
include_directories(deps/imgui)
include_directories(deps/lua)
include_directories(deps/rlimgui)
include_directories(deps/rres)

set(DEPS_SOURCES
    "deps/imgui/imgui_demo.cpp"
    "deps/imgui/imgui_draw.cpp"
    "deps/imgui/imgui_tables.cpp"
    "deps/imgui/imgui_widgets.cpp"
    "deps/imgui/imgui.cpp"
    "deps/lua/enet.c"
    "deps/lua/http.c"
    "deps/lua/lutf8lib.c"
    "deps/rlimgui/rlImGui.cpp"
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES} ${DEPS_SOURCES})
target_link_libraries(${PROJECT_NAME} enet libluajit raylib)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32 wininet)
endif()

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "pestoc")
    add_executable(pesto_win ${SOURCES} ${DEPS_SOURCES})
    target_link_libraries(pesto_win enet libluajit raylib ws2_32 wininet)
    target_link_options(pesto_win PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
    set_target_properties(pesto_win PROPERTIES OUTPUT_NAME "pesto")
endif()
