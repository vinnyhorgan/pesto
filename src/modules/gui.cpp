#include "api.h"

#include "../lib/imgui/imgui.h"
#include "../lib/imgui/rlImGui.h"

static int setup(lua_State* L)
{
    rlImGuiSetup(true);

    return 0;
}

static int beginDrawing(lua_State* L)
{
    rlImGuiBegin();

    return 0;
}

static int endDrawing(lua_State* L)
{
    rlImGuiEnd();

    return 0;
}

static int demo(lua_State* L)
{
    bool open = true;
    ImGui::ShowDemoWindow(&open);

    return 0;
}

static int shutdown(lua_State* L)
{
    rlImGuiShutdown();

    return 0;
}

static const luaL_Reg functions[] = {
    { "setup", setup },
    { "beginDrawing", beginDrawing },
    { "endDrawing", endDrawing },
    { "demo", demo },
    { "shutdown", shutdown },
    { NULL, NULL }
};

int luaopen_gui(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "gui");

    lua_pop(L, 1);

    return 1;
}
