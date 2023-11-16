#include "api.h"

static int init(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    const char* title = luaL_checkstring(L, 3);

    InitWindow(width, height, title);

    return 0;
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

static const luaL_Reg functions[] = {
    { "init", init },
    { "close", close },
    { "shouldClose", shouldClose },
    { "beginDrawing", beginDrawing },
    { "endDrawing", endDrawing },
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
