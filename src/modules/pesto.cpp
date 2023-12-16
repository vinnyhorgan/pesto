#include "api.h"

#include "../util.h"

#include "../scripts/animation.lua.h"
#include "../scripts/boot.lua.h"
#include "../scripts/ldtk.lua.h"
#include "../scripts/manager.lua.h"
#include "../scripts/reload.lua.h"
#include "../scripts/state.lua.h"

#include "../scripts/external/astar.lua.h"
#include "../scripts/external/brinevector.lua.h"
#include "../scripts/external/bump.lua.h"
#include "../scripts/external/classic.lua.h"
#include "../scripts/external/flux.lua.h"
#include "../scripts/external/inspect.lua.h"
#include "../scripts/external/json.lua.h"
#include "../scripts/external/lume.lua.h"
#include "../scripts/external/signal.lua.h"
#include "../scripts/external/tick.lua.h"
#include "../scripts/external/tiny.lua.h"

#include <luadeps.h>

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

static int luaopen_manager(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)MANAGER_DATA, sizeof(MANAGER_DATA), "manager.lua") == 0) {
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

// Lua libraries
int luaopen_astar(lua_State* L)
{
    if (luaL_loadbuffer(L, (const char*)ASTAR_DATA, sizeof(ASTAR_DATA), "astar.lua") == 0) {
        lua_call(L, 0, 1);
    }

    return 1;
}

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

static const luaL_Reg modules[] = {
    // Pesto modules
    { "pesto.audio", luaopen_pesto_audio },
    { "pesto.filesystem", luaopen_pesto_filesystem },
    { "pesto.gamepad", luaopen_pesto_gamepad },
    { "pesto.graphics", luaopen_pesto_graphics },
    { "pesto.imgui", luaopen_pesto_imgui },
    { "pesto.keyboard", luaopen_pesto_keyboard },
    { "pesto.log", luaopen_pesto_log },
    { "pesto.math", luaopen_pesto_math },
    { "pesto.mouse", luaopen_pesto_mouse },
    { "pesto.rres", luaopen_pesto_rres },
    { "pesto.system", luaopen_pesto_system },
    { "pesto.window", luaopen_pesto_window },
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
    { "enet", luaopen_enet },
    { "http", luaopen_http },
    { "utf8", luaopen_utf8 },
    // Scripts
    { "pesto.animation", luaopen_animation },
    { "pesto.boot", luaopen_boot },
    { "pesto.ldtk", luaopen_ldtk },
    { "pesto.manager", luaopen_manager },
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
