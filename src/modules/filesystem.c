#include "filesystem.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include <raylib.h>

static int exists(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    lua_pushboolean(L, FileExists(filename));

    return 1;
}

static const luaL_Reg functions[] = {
    { "exists", exists },
    { NULL, NULL }
};

int luaopen_filesystem(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "filesystem");

    lua_pop(L, 1);

    return 1;
}
