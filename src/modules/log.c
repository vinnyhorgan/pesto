#include "api.h"

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include <raylib.h>

static int info(lua_State* L)
{
    TraceLog(LOG_INFO, lua_tostring(L, 1));

    return 0;
}

static int warn(lua_State* L)
{
    TraceLog(LOG_WARNING, lua_tostring(L, 1));

    return 0;
}

static int error(lua_State* L)
{
    TraceLog(LOG_ERROR, lua_tostring(L, 1));

    return 0;
}

static int fatal(lua_State* L)
{
    TraceLog(LOG_FATAL, lua_tostring(L, 1));

    return 0;
}

static int debug(lua_State* L)
{
    TraceLog(LOG_DEBUG, lua_tostring(L, 1));

    return 0;
}

static int trace(lua_State* L)
{
    TraceLog(LOG_TRACE, lua_tostring(L, 1));

    return 0;
}

static int level(lua_State* L)
{
    const char* level = lua_tostring(L, 1);

    if (TextIsEqual(level, "info")) {
        SetTraceLogLevel(LOG_INFO);
    } else if (TextIsEqual(level, "warn")) {
        SetTraceLogLevel(LOG_WARNING);
    } else if (TextIsEqual(level, "error")) {
        SetTraceLogLevel(LOG_ERROR);
    } else if (TextIsEqual(level, "fatal")) {
        SetTraceLogLevel(LOG_FATAL);
    } else if (TextIsEqual(level, "debug")) {
        SetTraceLogLevel(LOG_DEBUG);
    } else if (TextIsEqual(level, "trace")) {
        SetTraceLogLevel(LOG_TRACE);
    } else {
        return luaL_error(L, "Invalid log level");
    }

    return 0;
}

static const luaL_Reg functions[] = {
    { "info", info },
    { "warn", warn },
    { "error", error },
    { "fatal", fatal },
    { "debug", debug },
    { "trace", trace },
    { "level", level },
    { NULL, NULL }
};

int luaopen_log(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "log");

    lua_pop(L, 1);

    return 1;
}
