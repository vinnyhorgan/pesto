#include "api.h"

#include <stdio.h>
#include <time.h>

static void customLog(int msgType, const char* text, va_list args)
{
    char timeStr[64] = { 0 };
    time_t now = time(NULL);
    struct tm* tm_info = localtime(&now);

    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("[%s] ", timeStr);

    switch (msgType) {
    case LOG_TRACE:
        printf("[\x1b[34mTRACE\x1b[0m]: ");
        break;
    case LOG_DEBUG:
        printf("[\x1b[36mDEBUG\x1b[0m]: ");
        break;
    case LOG_INFO:
        printf("[\x1b[32mINFO\x1b[0m] : ");
        break;
    case LOG_WARNING:
        printf("[\x1b[33mWARN\x1b[0m] : ");
        break;
    case LOG_ERROR:
        printf("[\x1b[31mERROR\x1b[0m]: ");
        break;
    case LOG_FATAL:
        printf("[\x1b[35mFATAL\x1b[0m]: ");
        break;
    default:
        break;
    }

    vprintf(text, args);
    printf("\n");
}

static int trace(lua_State* L)
{
    TraceLog(LOG_TRACE, lua_tostring(L, 1));

    return 0;
}

static int debug(lua_State* L)
{
    TraceLog(LOG_DEBUG, lua_tostring(L, 1));

    return 0;
}

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

static int level(lua_State* L)
{
    const char* level = lua_tostring(L, 1);

    if (TextIsEqual(level, "trace")) {
        SetTraceLogLevel(LOG_TRACE);
    } else if (TextIsEqual(level, "debug")) {
        SetTraceLogLevel(LOG_DEBUG);
    } else if (TextIsEqual(level, "info")) {
        SetTraceLogLevel(LOG_INFO);
    } else if (TextIsEqual(level, "warn")) {
        SetTraceLogLevel(LOG_WARNING);
    } else if (TextIsEqual(level, "error")) {
        SetTraceLogLevel(LOG_ERROR);
    } else if (TextIsEqual(level, "fatal")) {
        SetTraceLogLevel(LOG_FATAL);
    } else {
        return luaL_error(L, "Invalid log level");
    }

    return 0;
}

static const luaL_Reg functions[] = {
    { "trace", trace },
    { "debug", debug },
    { "info", info },
    { "warn", warn },
    { "error", error },
    { "fatal", fatal },
    { "level", level },
    { NULL, NULL }
};

int luaopen_log(lua_State* L)
{
    SetTraceLogCallback(customLog);
    SetTraceLogLevel(LOG_WARNING);

    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "log");

    return 1;
}
