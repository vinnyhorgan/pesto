#include "api.h"

static int clear(lua_State* L)
{
    int r = (int)luaL_optinteger(L, 1, 0);
    int g = (int)luaL_optinteger(L, 2, 0);
    int b = (int)luaL_optinteger(L, 3, 0);
    int a = (int)luaL_optinteger(L, 4, 255);

    ClearBackground((Color) { r, g, b, a });

    return 0;
}

static int text(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);

    DrawText(text, x, y, 20, WHITE);

    return 0;
}

static const luaL_Reg functions[] = {
    { "clear", clear },
    { "text", text },
    { NULL, NULL }
};

int luaopen_graphics(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "graphics");

    return 1;
}
