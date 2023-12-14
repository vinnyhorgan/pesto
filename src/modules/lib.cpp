#include "api.h"

#include "../lib/lua/astar.lua.h"
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
