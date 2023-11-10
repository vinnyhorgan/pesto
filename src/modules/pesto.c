#include "pesto.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

int luaopen_pesto(lua_State* L)
{
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    lua_pushcfunction(L, luaopen_boot);
    lua_setfield(L, -2, "pesto.boot");
    lua_pop(L, 2);

    return 1;
}

int luaopen_boot(lua_State* L)
{
    if (luaL_loadfile(L, ASSETS_PATH "boot.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}
