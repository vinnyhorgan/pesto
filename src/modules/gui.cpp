#include "api.h"

#include "../lib/imgui/imgui.h"
#include "../lib/imgui/rlImGui.h"

static int close(lua_State* L)
{
    rlImGuiShutdown();

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

static int init(lua_State* L)
{
    rlImGuiSetup(true);

    return 0;
}

static int beginMainMenuBar(lua_State* L)
{
    bool result = ImGui::BeginMainMenuBar();
    lua_pushboolean(L, result);

    return 1;
}

static int endMainMenuBar(lua_State* L)
{
    ImGui::EndMainMenuBar();

    return 0;
}

static int beginMenu(lua_State* L)
{
    const char* label = luaL_checkstring(L, 1);
    bool enabled = lua_toboolean(L, 2);
    bool result = ImGui::BeginMenu(label, enabled);
    lua_pushboolean(L, result);

    return 1;
}

static int endMenu(lua_State* L)
{
    ImGui::EndMenu();

    return 0;
}

static int menuItem(lua_State* L)
{
    const char* label = luaL_checkstring(L, 1);
    bool result = ImGui::MenuItem(label);
    lua_pushboolean(L, result);

    return 1;
}

static int text(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    ImGui::Text(text);

    return 0;
}

static int colorEdit3(lua_State* L)
{
    const char* label = luaL_checkstring(L, 1);

    float col[3];
    col[0] = (float)luaL_checknumber(L, 2);
    col[1] = (float)luaL_checknumber(L, 3);
    col[2] = (float)luaL_checknumber(L, 4);

    bool result = ImGui::ColorEdit3(label, col);

    lua_pushboolean(L, result);

    lua_pushnumber(L, col[0]);
    lua_pushnumber(L, col[1]);
    lua_pushnumber(L, col[2]);

    return 4;
}

static int sliderFloat(lua_State* L)
{
    const char* label = luaL_checkstring(L, 1);
    float v = (float)luaL_checknumber(L, 2);
    float min = (float)luaL_checknumber(L, 3);
    float max = (float)luaL_checknumber(L, 4);

    bool result = ImGui::SliderFloat(label, &v, min, max);

    lua_pushboolean(L, result);

    lua_pushnumber(L, v);

    return 2;
}

static int sliderFloat2(lua_State* L)
{
    const char* label = luaL_checkstring(L, 1);

    float v[2];
    v[0] = (float)luaL_checknumber(L, 2);
    v[1] = (float)luaL_checknumber(L, 3);

    float min = (float)luaL_checknumber(L, 4);
    float max = (float)luaL_checknumber(L, 5);

    bool result = ImGui::SliderFloat2(label, v, min, max);

    lua_pushboolean(L, result);

    lua_pushnumber(L, v[0]);
    lua_pushnumber(L, v[1]);

    return 3;
}

static int button(lua_State* L)
{
    const char* label = luaL_checkstring(L, 1);
    bool result = ImGui::Button(label);
    lua_pushboolean(L, result);

    return 1;
}

static int setNextWindowPos(lua_State* L)
{
    float x = (float)luaL_checknumber(L, 1);
    float y = (float)luaL_checknumber(L, 2);
    const char* cond = luaL_checkstring(L, 3);

    if (TextIsEqual(cond, "none")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_None);
    } else if (TextIsEqual(cond, "always")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_Always);
    } else if (TextIsEqual(cond, "once")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_Once);
    } else if (TextIsEqual(cond, "firstuseever")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_FirstUseEver);
    } else if (TextIsEqual(cond, "appearing")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_Appearing);
    } else {
        return luaL_error(L, "Invalid condition");
    }

    return 0;
}

static int beginWindow(lua_State* L)
{
    const char* name = luaL_checkstring(L, 1);
    bool open = lua_toboolean(L, 2);
    bool result = ImGui::Begin(name, &open);
    lua_pushboolean(L, result);
    lua_pushboolean(L, open);

    return 2;
}

static int endWindow(lua_State* L)
{
    ImGui::End();

    return 0;
}

static int showDemoWindow(lua_State* L)
{
    bool open = lua_toboolean(L, 1);
    ImGui::ShowDemoWindow(&open);
    lua_pushboolean(L, open);

    return 1;
}

static const luaL_Reg functions[] = {
    { "beginDrawing", beginDrawing },
    { "close", close },
    { "endDrawing", endDrawing },
    { "init", init },
    { "beginMainMenuBar", beginMainMenuBar },
    { "endMainMenuBar", endMainMenuBar },
    { "beginMenu", beginMenu },
    { "endMenu", endMenu },
    { "menuItem", menuItem },
    { "text", text },
    { "colorEdit3", colorEdit3 },
    { "sliderFloat", sliderFloat },
    { "sliderFloat2", sliderFloat2 },
    { "button", button },
    { "setNextWindowPos", setNextWindowPos },
    { "beginWindow", beginWindow },
    { "endWindow", endWindow },
    { "showDemoWindow", showDemoWindow },
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
