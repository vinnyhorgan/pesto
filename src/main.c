#include <stdio.h>
#include <string.h>

#include "modules/api.h"
#include "util.h"

int main(int argc, char* argv[])
{
    generateBootHeader(); // Remove before release

    int retval = 0;

    if (argc > 1 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)) {
        printf("Pesto %d.%d.%d (%s)\n", PESTO_VERSION_MAJOR, PESTO_VERSION_MINOR, PESTO_VERSION_PATCH, PESTO_VERSION_CODENAME);
        return 0;
    }

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // arg table
    lua_newtable(L);

    for (int i = 1; i < argc; i++) {
        lua_pushstring(L, argv[i]);
        lua_rawseti(L, -2, i);
    }

    lua_setglobal(L, "arg");

    // setup pesto module
    preload(L, luaopen_pesto, "pesto");
    require(L, "pesto");

    // run boot.lua
    require(L, "pesto.boot");

    lua_call(L, 0, 1);

    // get return value
    if (lua_isnumber(L, -1))
        retval = (int)lua_tonumber(L, -1);

    lua_close(L);

    return retval;
}
