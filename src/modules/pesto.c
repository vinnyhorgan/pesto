#include "pesto.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "../version.h"
#include "filesystem.h"

static int luaopen_boot(lua_State* L)
{
    if (luaL_loadfile(L, ASSETS_PATH "boot.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

static const luaL_Reg modules[] = {
    { "pesto.filesystem", luaopen_filesystem },
    { "pesto.boot", luaopen_boot },
    { NULL, NULL }
};

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
    lua_newtable(L);
    lua_pushvalue(L, -1);
    lua_setglobal(L, "pesto");

    lua_pushcfunction(L, getVersion);
    lua_setfield(L, -2, "getVersion");

    for (int i = 0; modules[i].name; i++) {
        lua_getglobal(L, "package");
        lua_getfield(L, -1, "preload");
        lua_pushcfunction(L, modules[i].func);
        lua_setfield(L, -2, modules[i].name);
        lua_pop(L, 2);
    }

    return 1;
}
