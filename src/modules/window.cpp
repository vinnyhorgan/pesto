#include "api.h"

#include "../../assets/icon.png.h"
#include "../../assets/noto.ttf.h"

Font font;

static int init(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    const char* title = luaL_checkstring(L, 3);

    InitWindow(width, height, title);

    Image icon;
    icon.data = ICON_DATA;
    icon.width = ICON_WIDTH;
    icon.height = ICON_HEIGHT;
    icon.format = ICON_FORMAT;
    icon.mipmaps = 1;

    SetWindowIcon(icon);

    // Generating the font header requires opengl context

    // Font font = LoadFontEx(PROJECT_PATH "assets/noto.ttf", 18, NULL, 0);
    // ExportFontAsCode(font, PROJECT_PATH "assets/noto.ttf.h");
    // UnloadFont(font);

    font = LoadFont_Noto();

    SetExitKey(KEY_NULL);

    return 0;
}

static int isReady(lua_State* L)
{
    lua_pushboolean(L, IsWindowReady());

    return 1;
}

static int close(lua_State* L)
{
    CloseWindow();

    return 0;
}

static int shouldClose(lua_State* L)
{
    lua_pushboolean(L, WindowShouldClose());

    return 1;
}

static int beginDrawing(lua_State* L)
{
    BeginDrawing();

    return 0;
}

static int endDrawing(lua_State* L)
{
    EndDrawing();

    return 0;
}

static int setTargetFPS(lua_State* L)
{
    int fps = (int)luaL_checkinteger(L, 1);

    SetTargetFPS(fps);

    return 0;
}

static int getDelta(lua_State* L)
{
    lua_pushnumber(L, GetFrameTime());

    return 1;
}

static int getFPS(lua_State* L)
{
    lua_pushnumber(L, GetFPS());

    return 1;
}

static const luaL_Reg functions[] = {
    { "init", init },
    { "isReady", isReady },
    { "close", close },
    { "shouldClose", shouldClose },
    { "beginDrawing", beginDrawing },
    { "endDrawing", endDrawing },
    { "setTargetFPS", setTargetFPS },
    { "getDelta", getDelta },
    { "getFPS", getFPS },
    { NULL, NULL }
};

int luaopen_window(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "window");

    return 1;
}
