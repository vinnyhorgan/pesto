#include "api.h"

static int getAxisCount(lua_State* L)
{
    int gamepad = (int)luaL_checkinteger(L, 1);
    int result = GetGamepadAxisCount(gamepad);
    lua_pushinteger(L, result);

    return 1;
}

static int getAxisMovement(lua_State* L)
{
    int gamepad = (int)luaL_checkinteger(L, 1);
    int axis = (int)luaL_checkinteger(L, 2);
    float result = GetGamepadAxisMovement(gamepad, axis);
    lua_pushnumber(L, result);

    return 1;
}

static int getName(lua_State* L)
{
    int gamepad = (int)luaL_checkinteger(L, 1);
    const char* result = GetGamepadName(gamepad);
    lua_pushstring(L, result);

    return 1;
}

static int getPressed(lua_State* L)
{
    int result = GetGamepadButtonPressed();
    lua_pushinteger(L, result);

    return 1;
}

static int isAvailable(lua_State* L)
{
    int gamepad = (int)luaL_checkinteger(L, 1);
    bool result = IsGamepadAvailable(gamepad);
    lua_pushboolean(L, result);

    return 1;
}

static int isDown(lua_State* L)
{
    int gamepad = (int)luaL_checkinteger(L, 1);
    int button = (int)luaL_checkinteger(L, 2);
    bool result = IsGamepadButtonDown(gamepad, button);
    lua_pushboolean(L, result);

    return 1;
}

static int isPressed(lua_State* L)
{
    int gamepad = (int)luaL_checkinteger(L, 1);
    int button = (int)luaL_checkinteger(L, 2);
    bool result = IsGamepadButtonPressed(gamepad, button);
    lua_pushboolean(L, result);

    return 1;
}

static int isReleased(lua_State* L)
{
    int gamepad = (int)luaL_checkinteger(L, 1);
    int button = (int)luaL_checkinteger(L, 2);
    bool result = IsGamepadButtonReleased(gamepad, button);
    lua_pushboolean(L, result);

    return 1;
}

static int isUp(lua_State* L)
{
    int gamepad = (int)luaL_checkinteger(L, 1);
    int button = (int)luaL_checkinteger(L, 2);
    bool result = IsGamepadButtonUp(gamepad, button);
    lua_pushboolean(L, result);

    return 1;
}

static int setMappings(lua_State* L)
{
    const char* mappings = luaL_checkstring(L, 1);
    SetGamepadMappings(mappings);

    return 0;
}

static const luaL_Reg functions[] = {
    { "getAxisCount", getAxisCount },
    { "getAxisMovement", getAxisMovement },
    { "getName", getName },
    { "getPressed", getPressed },
    { "isAvailable", isAvailable },
    { "isDown", isDown },
    { "isPressed", isPressed },
    { "isReleased", isReleased },
    { "isUp", isUp },
    { "setMappings", setMappings },
    { NULL, NULL }
};

int luaopen_pesto_gamepad(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "gamepad");

    lua_pop(L, 1);

    return 1;
}
