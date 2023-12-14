#include "api.h"

#include "../util.h"

#include <imgui.h>
#include <rlImGui.h>

static bool safe = false;

static int beginDrawing(lua_State* L)
{
    rlImGuiBegin();
    safe = true;

    return 0;
}

static int close(lua_State* L)
{
    rlImGuiShutdown();

    return 0;
}

static int endDrawing(lua_State* L)
{
    rlImGuiEnd();
    safe = false;

    return 0;
}

static int init(lua_State* L)
{
    rlImGuiSetup(true);

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;

    return 0;
}

// ImGui functions

static int beginWindow(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    int args = lua_gettop(L);

    if (args < 1 || !lua_isstring(L, 1)) {
        return luaL_error(L, "string expected, got %s", luaL_typename(L, 1));
    }

    const char* name = lua_tostring(L, 1);

    ImGuiWindowFlags flags = 0;

    for (int i = 2; i <= args; i++) {
        if (lua_isstring(L, i)) {
            const char* flag = lua_tostring(L, i);

            if (TextIsEqual(flag, "noTitleBar")) {
                flags |= ImGuiWindowFlags_NoTitleBar;
            } else if (TextIsEqual(flag, "noResize")) {
                flags |= ImGuiWindowFlags_NoResize;
            } else if (TextIsEqual(flag, "noMove")) {
                flags |= ImGuiWindowFlags_NoMove;
            } else if (TextIsEqual(flag, "noScrollbar")) {
                flags |= ImGuiWindowFlags_NoScrollbar;
            } else if (TextIsEqual(flag, "noScrollWithMouse")) {
                flags |= ImGuiWindowFlags_NoScrollWithMouse;
            } else if (TextIsEqual(flag, "noCollapse")) {
                flags |= ImGuiWindowFlags_NoCollapse;
            } else if (TextIsEqual(flag, "alwaysAutoResize")) {
                flags |= ImGuiWindowFlags_AlwaysAutoResize;
            } else if (TextIsEqual(flag, "noBackground")) {
                flags |= ImGuiWindowFlags_NoBackground;
            } else if (TextIsEqual(flag, "noSavedSettings")) {
                flags |= ImGuiWindowFlags_NoSavedSettings;
            } else if (TextIsEqual(flag, "noMouseInputs")) {
                flags |= ImGuiWindowFlags_NoMouseInputs;
            } else if (TextIsEqual(flag, "menuBar")) {
                flags |= ImGuiWindowFlags_MenuBar;
            } else if (TextIsEqual(flag, "horizontalScrollbar")) {
                flags |= ImGuiWindowFlags_HorizontalScrollbar;
            } else if (TextIsEqual(flag, "noFocusOnAppearing")) {
                flags |= ImGuiWindowFlags_NoFocusOnAppearing;
            } else if (TextIsEqual(flag, "noBringToFrontOnFocus")) {
                flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
            } else if (TextIsEqual(flag, "alwaysVerticalScrollbar")) {
                flags |= ImGuiWindowFlags_AlwaysVerticalScrollbar;
            } else if (TextIsEqual(flag, "alwaysHorizontalScrollbar")) {
                flags |= ImGuiWindowFlags_AlwaysHorizontalScrollbar;
            } else if (TextIsEqual(flag, "noNavInputs")) {
                flags |= ImGuiWindowFlags_NoNavInputs;
            } else if (TextIsEqual(flag, "noNavFocus")) {
                flags |= ImGuiWindowFlags_NoNavFocus;
            } else if (TextIsEqual(flag, "unsavedDocument")) {
                flags |= ImGuiWindowFlags_UnsavedDocument;
            } else if (TextIsEqual(flag, "noNav")) {
                flags |= ImGuiWindowFlags_NoNav;
            } else if (TextIsEqual(flag, "noDecoration")) {
                flags |= ImGuiWindowFlags_NoDecoration;
            } else if (TextIsEqual(flag, "noInputs")) {
                flags |= ImGuiWindowFlags_NoInputs;
            } else {
                return luaL_error(L, "Invalid flag: %s", flag);
            }
        }
    }

    bool open = true;
    bool result = ImGui::Begin(name, &open, flags);
    lua_pushboolean(L, open);
    lua_pushboolean(L, result);

    return 2;
}

static int endWindow(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    ImGui::End();

    return 0;
}

static int showDemoWindow(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    bool open = true;
    ImGui::ShowDemoWindow(&open);
    lua_pushboolean(L, open);

    return 1;
}

static int text(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* text = luaL_checkstring(L, 1);
    ImGui::Text(text);

    return 0;
}

static int button(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* label = luaL_checkstring(L, 1);
    float width = (float)luaL_optnumber(L, 2, 0);
    float height = (float)luaL_optnumber(L, 3, 0);
    bool result = ImGui::Button(label, ImVec2(width, height));
    lua_pushboolean(L, result);

    return 1;
}

static int checkbox(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* label = luaL_checkstring(L, 1);
    bool checked = check_boolean(L, 2);
    bool result = ImGui::Checkbox(label, &checked);
    lua_pushboolean(L, checked);
    lua_pushboolean(L, result);

    return 2;
}

static int inputText(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* label = luaL_checkstring(L, 1);
    char buffer[256];
    strcpy(buffer, luaL_checkstring(L, 2));
    bool result = ImGui::InputText(label, buffer, sizeof(buffer));
    lua_pushstring(L, buffer);
    lua_pushboolean(L, result);

    return 2;
}

static int sliderFloat(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* label = luaL_checkstring(L, 1);
    float value = (float)luaL_checknumber(L, 2);
    float min = (float)luaL_checknumber(L, 3);
    float max = (float)luaL_checknumber(L, 4);
    bool result = ImGui::SliderFloat(label, &value, min, max);
    lua_pushnumber(L, value);
    lua_pushboolean(L, result);

    return 2;
}

static int sliderInt(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* label = luaL_checkstring(L, 1);
    int value = (int)luaL_checkinteger(L, 2);
    int min = (int)luaL_checkinteger(L, 3);
    int max = (int)luaL_checkinteger(L, 4);
    bool result = ImGui::SliderInt(label, &value, min, max);
    lua_pushinteger(L, value);
    lua_pushboolean(L, result);

    return 2;
}

static int colorEdit3(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* label = luaL_checkstring(L, 1);

    float col[3];
    col[0] = (float)luaL_checknumber(L, 2);
    col[1] = (float)luaL_checknumber(L, 3);
    col[2] = (float)luaL_checknumber(L, 4);

    bool result = ImGui::ColorEdit3(label, col);
    lua_pushnumber(L, col[0]);
    lua_pushnumber(L, col[1]);
    lua_pushnumber(L, col[2]);
    lua_pushboolean(L, result);

    return 4;
}

static int colorEdit4(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* label = luaL_checkstring(L, 1);

    float col[4];
    col[0] = (float)luaL_checknumber(L, 2);
    col[1] = (float)luaL_checknumber(L, 3);
    col[2] = (float)luaL_checknumber(L, 4);
    col[3] = (float)luaL_checknumber(L, 5);

    bool result = ImGui::ColorEdit4(label, col);
    lua_pushnumber(L, col[0]);
    lua_pushnumber(L, col[1]);
    lua_pushnumber(L, col[2]);
    lua_pushnumber(L, col[3]);
    lua_pushboolean(L, result);

    return 5;
}

static int image(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    Texture* image = (Texture*)luaL_checkudata(L, 1, "Texture");
    rlImGuiImage(image);

    return 0;
}

static int separator(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    ImGui::Separator();

    return 0;
}

static int sameLine(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    float offset = (float)luaL_optnumber(L, 1, 0);
    float spacing = (float)luaL_optnumber(L, 2, -1);
    ImGui::SameLine(offset, spacing);

    return 0;
}

static int setNextWindowPos(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    float x = (float)luaL_checknumber(L, 1);
    float y = (float)luaL_checknumber(L, 2);
    const char* condition = luaL_optstring(L, 3, "none");

    if (TextIsEqual(condition, "none")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_None);
    } else if (TextIsEqual(condition, "always")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_Always);
    } else if (TextIsEqual(condition, "once")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_Once);
    } else if (TextIsEqual(condition, "firstUseEver")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_FirstUseEver);
    } else if (TextIsEqual(condition, "appearing")) {
        ImGui::SetNextWindowPos({ x, y }, ImGuiCond_Appearing);
    } else {
        return luaL_error(L, "Invalid condition: %s", condition);
    }

    return 0;
}

static int setNextWindowSize(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    float x = (float)luaL_checknumber(L, 1);
    float y = (float)luaL_checknumber(L, 2);
    const char* condition = luaL_optstring(L, 3, "none");

    if (TextIsEqual(condition, "none")) {
        ImGui::SetNextWindowSize({ x, y }, ImGuiCond_None);
    } else if (TextIsEqual(condition, "always")) {
        ImGui::SetNextWindowSize({ x, y }, ImGuiCond_Always);
    } else if (TextIsEqual(condition, "once")) {
        ImGui::SetNextWindowSize({ x, y }, ImGuiCond_Once);
    } else if (TextIsEqual(condition, "firstUseEver")) {
        ImGui::SetNextWindowSize({ x, y }, ImGuiCond_FirstUseEver);
    } else if (TextIsEqual(condition, "appearing")) {
        ImGui::SetNextWindowSize({ x, y }, ImGuiCond_Appearing);
    } else {
        return luaL_error(L, "Invalid condition: %s", condition);
    }

    return 0;
}

static int beginMainMenuBar(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    bool result = ImGui::BeginMainMenuBar();
    lua_pushboolean(L, result);

    return 1;
}

static int endMainMenuBar(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    ImGui::EndMainMenuBar();

    return 0;
}

static int beginMenuBar(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    bool result = ImGui::BeginMenuBar();
    lua_pushboolean(L, result);

    return 1;
}

static int endMenuBar(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    ImGui::EndMenuBar();

    return 0;
}

static int beginMenu(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* label = luaL_checkstring(L, 1);
    bool enabled = true;

    if (lua_gettop(L) >= 2) {
        enabled = lua_toboolean(L, 2);
    }

    bool result = ImGui::BeginMenu(label, enabled);
    lua_pushboolean(L, result);

    return 1;
}

static int endMenu(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    ImGui::EndMenu();

    return 0;
}

static int menuItem(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "pesto.imgui calls can only be made in the pesto.gui callback.");
    }

    const char* label = luaL_checkstring(L, 1);
    const char* shortcut = luaL_optstring(L, 2, NULL);
    bool selected = false;
    bool enabled = true;

    if (lua_gettop(L) >= 3) {
        selected = lua_toboolean(L, 3);
    }

    if (lua_gettop(L) >= 4) {
        enabled = lua_toboolean(L, 4);
    }

    bool result = ImGui::MenuItem(label, shortcut, selected, enabled);
    lua_pushboolean(L, result);

    return 1;
}

static const luaL_Reg functions[] = {
    { "beginDrawing", beginDrawing },
    { "close", close },
    { "endDrawing", endDrawing },
    { "init", init },
    // ImGui functions
    { "beginWindow", beginWindow },
    { "endWindow", endWindow },
    { "showDemoWindow", showDemoWindow },
    { "text", text },
    { "button", button },
    { "checkbox", checkbox },
    { "inputText", inputText },
    { "sliderFloat", sliderFloat },
    { "sliderInt", sliderInt },
    { "colorEdit3", colorEdit3 },
    { "colorEdit4", colorEdit4 },
    { "image", image },
    { "separator", separator },
    { "sameLine", sameLine },
    { "setNextWindowPos", setNextWindowPos },
    { "setNextWindowSize", setNextWindowSize },
    { "beginMainMenuBar", beginMainMenuBar },
    { "endMainMenuBar", endMainMenuBar },
    { "beginMenuBar", beginMenuBar },
    { "endMenuBar", endMenuBar },
    { "beginMenu", beginMenu },
    { "endMenu", endMenu },
    { "menuItem", menuItem },
    { NULL, NULL }
};

int luaopen_imgui(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "imgui");

    lua_pop(L, 1);

    return 1;
}
