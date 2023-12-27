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

static int setNoiseFractalType(lua_State* L)
{
    const char* type = luaL_checkstring(L, 1);

    if (TextIsEqual(type, "none")) {
        fnlState.fractal_type = FNL_FRACTAL_NONE;
    } else if (TextIsEqual(type, "fbm")) {
        fnlState.fractal_type = FNL_FRACTAL_FBM;
    } else if (TextIsEqual(type, "ridged")) {
        fnlState.fractal_type = FNL_FRACTAL_RIDGED;
    } else if (TextIsEqual(type, "pingpong")) {
        fnlState.fractal_type = FNL_FRACTAL_PINGPONG;
    } else {
        return luaL_error(L, "Invalid fractal type: %s", type);
    }

    return 0;
}

static int setNoiseFrequency(lua_State* L)
{
    float frequency = (float)luaL_checknumber(L, 1);
    fnlState.frequency = frequency;

    return 0;
}

static int setNoiseGain(lua_State* L)
{
    float gain = (float)luaL_checknumber(L, 1);
    fnlState.gain = gain;

    return 0;
}

static int setNoiseLacunarity(lua_State* L)
{
    float lacunarity = (float)luaL_checknumber(L, 1);
    fnlState.lacunarity = lacunarity;

    return 0;
}

static int setNoiseOctaves(lua_State* L)
{
    int octaves = (int)luaL_checkinteger(L, 1);
    fnlState.octaves = octaves;

    return 0;
}

static int setNoiseSeed(lua_State* L)
{
    int seed = (int)luaL_checkinteger(L, 1);
    fnlState.seed = seed;

    return 0;
}

static int setNoiseType(lua_State* L)
{
    const char* type = luaL_checkstring(L, 1);

    if (TextIsEqual(type, "openSimplex2")) {
        fnlState.noise_type = FNL_NOISE_OPENSIMPLEX2;
    } else if (TextIsEqual(type, "openSimplex2S")) {
        fnlState.noise_type = FNL_NOISE_OPENSIMPLEX2S;
    } else if (TextIsEqual(type, "cellular")) {
        fnlState.noise_type = FNL_NOISE_CELLULAR;
    } else if (TextIsEqual(type, "perlin")) {
        fnlState.noise_type = FNL_NOISE_PERLIN;
    } else if (TextIsEqual(type, "valueCubic")) {
        fnlState.noise_type = FNL_NOISE_VALUE_CUBIC;
    } else if (TextIsEqual(type, "value")) {
        fnlState.noise_type = FNL_NOISE_VALUE;
    } else {
        return luaL_error(L, "Invalid noise type: %s", type);
    }

    return 0;
}

static int setNoiseWeightedStrength(lua_State* L)
{
    float weightedStrength = (float)luaL_checknumber(L, 1);
    fnlState.weighted_strength = weightedStrength;

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
    { "setNoiseFractalType", setNoiseFractalType },
    { "setNoiseFrequency", setNoiseFrequency },
    { "setNoiseGain", setNoiseGain },
    { "setNoiseLacunarity", setNoiseLacunarity },
    { "setNoiseOctaves", setNoiseOctaves },
    { "setNoiseSeed", setNoiseSeed },
    { "setNoiseType", setNoiseType },
    { "setNoiseWeightedStrength", setNoiseWeightedStrength },
    { "setRandomSeed", setRandomSeed },
    { NULL, NULL }
};

int luaopen_pesto_math(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "math");

    lua_pop(L, 1);

    return 1;
}
