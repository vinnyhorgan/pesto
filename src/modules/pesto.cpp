#include "api.h"

#include "../util.h"

#include "../scripts/animation.lua.h"
#include "../scripts/boot.lua.h"
#include "../scripts/ldtk.lua.h"
#include "../scripts/reload.lua.h"
#include "../scripts/state.lua.h"

extern "C" {
#include "../lib/luasocket/luasocket.h"
#include "../lib/luasocket/mime.h"
}

static int luaopen_animation(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)ANIMATION_DATA, sizeof(ANIMATION_DATA), "animation.lua") == 0) {
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

static int luaopen_ldtk(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)LDTK_DATA, sizeof(LDTK_DATA), "ldtk.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

static int luaopen_reload(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)RELOAD_DATA, sizeof(RELOAD_DATA), "reload.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

static int luaopen_state(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)STATE_DATA, sizeof(STATE_DATA), "state.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

static const luaL_Reg modules[] = {
    // Pesto modules
    { "pesto.audio", luaopen_audio },
    { "pesto.filesystem", luaopen_filesystem },
    { "pesto.gamepad", luaopen_gamepad },
    { "pesto.graphics", luaopen_graphics },
    { "pesto.gui", luaopen_gui },
    { "pesto.keyboard", luaopen_keyboard },
    { "pesto.log", luaopen_log },
    { "pesto.math", luaopen_pmath },
    { "pesto.mouse", luaopen_mouse },
    { "pesto.physics", luaopen_physics },
    { "pesto.rres", luaopen_rres },
    { "pesto.system", luaopen_system },
    { "pesto.window", luaopen_window },
    // Lua libraries
    { "astar", luaopen_astar },
    { "brinevector", luaopen_brinevector },
    { "bump", luaopen_bump },
    { "classic", luaopen_classic },
    { "flux", luaopen_flux },
    { "inspect", luaopen_inspect },
    { "json", luaopen_json },
    { "lume", luaopen_lume },
    { "signal", luaopen_signal },
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
    // Scripts
    { "pesto.animation", luaopen_animation },
    { "pesto.boot", luaopen_boot },
    { "pesto.ldtk", luaopen_ldtk },
    { "pesto.reload", luaopen_reload },
    { "pesto.state", luaopen_state },
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
    lua_pushcfunction(L, getVersion);
    lua_setfield(L, -2, "getVersion");
    lua_setglobal(L, "pesto");

    for (int i = 0; modules[i].name; i++) {
        preload(L, modules[i].func, modules[i].name);
    }

    return 1;
}
