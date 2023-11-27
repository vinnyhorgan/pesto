#include "api.h"

static int setRandomSeed(lua_State* L)
{
    unsigned int seed = (unsigned int)luaL_checkinteger(L, 1);
    SetRandomSeed(seed);

    return 0;
}

static int random(lua_State* L)
{
    int min = (int)luaL_checkinteger(L, 1);
    int max = (int)luaL_checkinteger(L, 2);
    int result = GetRandomValue(min, max);
    lua_pushinteger(L, result);

    return 1;
}

static const luaL_Reg functions[] = {
    { "setRandomSeed", setRandomSeed },
    { "random", random },
    { NULL, NULL }
};

// luaopen_math conflicts with lua internals
int luaopen_pmath(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "math");

    return 1;
}
