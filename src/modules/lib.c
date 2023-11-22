#include "api.h"

#include "../lib/lua/brinevector.lua.h"
#include "../lib/lua/bump.lua.h"
#include "../lib/lua/classic.lua.h"
#include "../lib/lua/flux.lua.h"
#include "../lib/lua/inspect.lua.h"
#include "../lib/lua/json.lua.h"
#include "../lib/lua/lume.lua.h"
#include "../lib/lua/signal.lua.h"
#include "../lib/lua/tick.lua.h"
#include "../lib/lua/tiny.lua.h"

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

// Lua libraries
int luaopen_brinevector(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)BRINEVECTOR_DATA, sizeof(BRINEVECTOR_DATA), "brinevector.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

int luaopen_bump(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)BUMP_DATA, sizeof(BUMP_DATA), "bump.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

int luaopen_classic(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)CLASSIC_DATA, sizeof(CLASSIC_DATA), "classic.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

int luaopen_flux(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)FLUX_DATA, sizeof(FLUX_DATA), "flux.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

int luaopen_inspect(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)INSPECT_DATA, sizeof(INSPECT_DATA), "inspect.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

int luaopen_json(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)JSON_DATA, sizeof(JSON_DATA), "json.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

int luaopen_lume(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)LUME_DATA, sizeof(LUME_DATA), "lume.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

int luaopen_signal(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)SIGNAL_DATA, sizeof(SIGNAL_DATA), "signal.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

int luaopen_tick(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)TICK_DATA, sizeof(TICK_DATA), "tick.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

int luaopen_tiny(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)TINY_DATA, sizeof(TINY_DATA), "tiny.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

// Luasocket
int luaopen_ftp(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)FTP_DATA, sizeof(FTP_DATA), "ftp.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

int luaopen_headers(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)HEADERS_DATA, sizeof(HEADERS_DATA), "headers.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

int luaopen_http(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)HTTP_DATA, sizeof(HTTP_DATA), "http.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

int luaopen_ltn12(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)LTN12_DATA, sizeof(LTN12_DATA), "ltn12.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

int luaopen_mbox(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)MBOX_DATA, sizeof(MBOX_DATA), "mbox.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

int luaopen_mime(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)MIME_DATA, sizeof(MIME_DATA), "mime.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

int luaopen_smtp(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)SMTP_DATA, sizeof(SMTP_DATA), "smtp.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

int luaopen_socket(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)SOCKET_DATA, sizeof(SOCKET_DATA), "socket.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

int luaopen_tp(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)TP_DATA, sizeof(TP_DATA), "tp.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}

int luaopen_url(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)URL_DATA, sizeof(URL_DATA), "url.lua") == 0) {
        lua_call(L, 0, LUA_MULTRET);
    }

    return 1;
}
