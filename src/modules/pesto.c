#include "api.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "../lib/luasocket/luasocket.h"
#include "../lib/luasocket/mime.h"

#include "../scripts/boot.lua.h"
#include "../util.h"

static int luaopen_boot(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)BOOT_DATA, sizeof(BOOT_DATA), "boot.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

static const luaL_Reg modules[] = {
    // Pesto modules
    { "pesto.filesystem", luaopen_filesystem },
    { "pesto.window", luaopen_window },
    // Lua libraries
    { "bump", luaopen_bump },
    { "classic", luaopen_classic },
    { "flux", luaopen_flux },
    { "inspect", luaopen_inspect },
    { "json", luaopen_json },
    { "lume", luaopen_lume },
    { "tick", luaopen_tick },
    { "tiny", luaopen_tiny },
    // Luasocket (C core)
    { "socket.core", luaopen_socket_core },
    { "mime.core", luaopen_mime_core },
    // Luasocket
    { "socket.ftp", luaopen_ftp },
    { "socket.headers", luaopen_headers },
    { "socket.http", luaopen_http },
    { "ltn12", luaopen_ltn12 },
    { "mbox", luaopen_mbox },
    { "mime", luaopen_mime },
    { "socket.smtp", luaopen_smtp },
    { "socket", luaopen_socket },
    { "socket.tp", luaopen_tp },
    { "socket.url", luaopen_url },
    // Boot script
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
        preload(L, modules[i].func, modules[i].name);
    }

    return 1;
}
