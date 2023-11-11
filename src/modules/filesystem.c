#include "filesystem.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

static int create(lua_State* L)
{
    lua_pushinteger(L, 26072004);

    return 1;
}

static const luaL_Reg functions[] = {
    { "create", create },
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
