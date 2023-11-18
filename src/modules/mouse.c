#include "api.h"

static int isDown(lua_State* L)
{
    int button = (int)luaL_checkinteger(L, 1);
    bool result = IsMouseButtonDown(button);
    lua_pushboolean(L, result);

    return 1;
}

static int getPosition(lua_State* L)
{
    int x = GetMouseX();
    int y = GetMouseY();
    lua_pushinteger(L, x);
    lua_pushinteger(L, y);

    return 2;
}

// Temporary

static int random(lua_State* L)
{
    int min = (int)luaL_checkinteger(L, 1);
    int max = (int)luaL_checkinteger(L, 2);

    lua_pushinteger(L, GetRandomValue(min, max));

    return 1;
}

static const luaL_Reg functions[] = {
    { "isDown", isDown },
    { "getPosition", getPosition },
    { "random", random },
    { NULL, NULL }
};

int luaopen_mouse(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "mouse");

    return 1;
}
