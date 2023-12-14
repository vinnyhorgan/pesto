#include "api.h"

#define FNL_IMPL
#include <FastNoiseLite.h>

static fnl_state fnlState = fnlCreateState();

static int noise2d(lua_State* L)
{
    float x = (float)luaL_checknumber(L, 1);
    float y = (float)luaL_checknumber(L, 2);
    float result = fnlGetNoise2D(&fnlState, (FNLfloat)x, (FNLfloat)y);
    lua_pushnumber(L, result);

    return 1;
}

static int noise3d(lua_State* L)
{
    float x = (float)luaL_checknumber(L, 1);
    float y = (float)luaL_checknumber(L, 2);
    float z = (float)luaL_checknumber(L, 3);
    float result = fnlGetNoise3D(&fnlState, (FNLfloat)x, (FNLfloat)y, (FNLfloat)z);

    return 1;
}

static int random(lua_State* L)
{
    int min = (int)luaL_checkinteger(L, 1);
    int max = (int)luaL_checkinteger(L, 2);
    int result = GetRandomValue(min, max);
    lua_pushinteger(L, result);

    return 1;
}

static int setNoiseFrequency(lua_State* L)
{
    float frequency = (float)luaL_checknumber(L, 1);
    fnlState.frequency = frequency;

    return 0;
}

static int setNoiseSeed(lua_State* L)
{
    int seed = (int)luaL_checkinteger(L, 1);
    fnlState.seed = seed;

    return 0;
}

static int setRandomSeed(lua_State* L)
{
    unsigned int seed = (unsigned int)luaL_checkinteger(L, 1);
    SetRandomSeed(seed);

    return 0;
}

static const luaL_Reg functions[] = {
    { "noise2d", noise2d },
    { "noise3d", noise3d },
    { "random", random },
    { "setNoiseFrequency", setNoiseFrequency },
    { "setNoiseSeed", setNoiseSeed },
    { "setRandomSeed", setRandomSeed },
    { NULL, NULL }
};

int luaopen_pmath(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "math");

    lua_pop(L, 1);

    return 1;
}
