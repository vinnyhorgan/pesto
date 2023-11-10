#include <stdio.h>
#include <string.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "modules/pesto.h"

#define PESTO_VERSION_MAJOR 0
#define PESTO_VERSION_MINOR 1
#define PESTO_VERSION_PATCH 0
#define PESTO_VERSION_CODENAME "Saucy Serenade"

int main(int argc, char* argv[])
{
    if (argc > 1 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)) {
        printf("Pesto %d.%d.%d (%s)\n", PESTO_VERSION_MAJOR, PESTO_VERSION_MINOR, PESTO_VERSION_PATCH, PESTO_VERSION_CODENAME);
        return 0;
    }

    int retval = 0;

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);

    for (int i = 1; i < argc; i++) {
        lua_pushstring(L, argv[i]);
        lua_rawseti(L, -2, i);
    }

    lua_setglobal(L, "arg");

    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    lua_pushcfunction(L, luaopen_pesto);
    lua_setfield(L, -2, "pesto");
    lua_pop(L, 2);

    lua_getglobal(L, "require");
    lua_pushstring(L, "pesto");
    lua_call(L, 1, 1);

    lua_getglobal(L, "require");
    lua_pushstring(L, "pesto.boot");
    lua_call(L, 1, 1);

    lua_call(L, 0, 1);

    if (lua_isnumber(L, -1))
        retval = (int)lua_tonumber(L, -1);

    lua_close(L);

    return retval;
}
