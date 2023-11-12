#include "api.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "../lib/luasocket/luasocket.h"
#include "../lib/luasocket/mime.h"

#include "../lib/lua/classic.lua.h"
#include "../lib/luasocket/ftp.lua.h"
#include "../lib/luasocket/headers.lua.h"
#include "../lib/luasocket/http.lua.h"
#include "../lib/luasocket/ltn12.lua.h"
#include "../lib/luasocket/mbox.lua.h"
#include "../lib/luasocket/mime.lua.h"
#include "../lib/luasocket/smtp.lua.h"
#include "../lib/luasocket/socket.lua.h"
#include "../lib/luasocket/tp.lua.h"
#include "../lib/luasocket/url.lua.h"
#include "../scripts/boot.lua.h"
#include "../util.h"

static int luaopen_ftp(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)FTP_DATA, sizeof(FTP_DATA), "ftp.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_headers(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)HEADERS_DATA, sizeof(HEADERS_DATA), "headers.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_http(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)HTTP_DATA, sizeof(HTTP_DATA), "http.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_ltn12(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)LTN12_DATA, sizeof(LTN12_DATA), "ltn12.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_mbox(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)MBOX_DATA, sizeof(MBOX_DATA), "mbox.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_mime(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)MIME_DATA, sizeof(MIME_DATA), "mime.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_smtp(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)SMTP_DATA, sizeof(SMTP_DATA), "smtp.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_socket(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)SOCKET_DATA, sizeof(SOCKET_DATA), "socket.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_tp(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)TP_DATA, sizeof(TP_DATA), "tp.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_url(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)URL_DATA, sizeof(URL_DATA), "url.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

static int luaopen_classic(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)CLASSIC_DATA, sizeof(CLASSIC_DATA), "classic.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

static int luaopen_boot(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)BOOT_DATA, sizeof(BOOT_DATA), "boot.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

static const luaL_Reg modules[] = {
    { "pesto.window", luaopen_window },
    { "pesto.filesystem", luaopen_filesystem },
    { "classic", luaopen_classic },
    { "pesto.boot", luaopen_boot },
    // Luasocket
    { "socket.core", luaopen_socket_core },
    { "mime.core", luaopen_mime_core },
    { "socket", luaopen_socket },
    { "socket.ftp", luaopen_ftp },
    { "socket.http", luaopen_http },
    { "ltn12", luaopen_ltn12 },
    { "mime", luaopen_mime },
    { "socket.smtp", luaopen_smtp },
    { "socket.tp", luaopen_tp },
    { "socket.url", luaopen_url },
    { "socket.headers", luaopen_headers },
    { "mbox", luaopen_mbox },
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
