#include "pesto.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "../version.h"

static int getVersion(lua_State* L)
{
    lua_pushinteger(L, PESTO_VERSION_MAJOR);
    lua_pushinteger(L, PESTO_VERSION_MINOR);
    lua_pushinteger(L, PESTO_VERSION_PATCH);
    lua_pushstring(L, PESTO_VERSION_CODENAME);

    return 4;
}

int luaopen_pesto(lua_State* L)
{
    lua_getglobal(L, "pesto");

    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        lua_newtable(L);
        lua_pushvalue(L, -1);
        lua_setglobal(L, "pesto");
    } // mmh figure out why i need this

    lua_pushcfunction(L, getVersion);
    lua_setfield(L, -2, "getVersion");

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
