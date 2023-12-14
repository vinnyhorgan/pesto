#include "api.h"

#include <stdio.h>
#include <time.h>

static int logLevel = LOG_TRACE;

static void log(int msgType, const char* text)
{
    if (msgType < logLevel)
        return;

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

    printf("%s\n", text);
}

static void raylibLog(int msgType, const char* text, va_list args)
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

static int debug(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    log(LOG_DEBUG, text);

    return 0;
}

static int error(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    log(LOG_ERROR, text);

    return 0;
}

static int fatal(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    log(LOG_FATAL, text);

    return 0;
}

static int info(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    log(LOG_INFO, text);

    return 0;
}

static int level(lua_State* L)
{
    const char* level = luaL_checkstring(L, 1);

    if (TextIsEqual(level, "trace"))
        logLevel = LOG_TRACE;
    else if (TextIsEqual(level, "debug"))
        logLevel = LOG_DEBUG;
    else if (TextIsEqual(level, "info"))
        logLevel = LOG_INFO;
    else if (TextIsEqual(level, "warn"))
        logLevel = LOG_WARNING;
    else if (TextIsEqual(level, "error"))
        logLevel = LOG_ERROR;
    else if (TextIsEqual(level, "fatal"))
        logLevel = LOG_FATAL;
    else
        return luaL_error(L, "Invalid log level: %s", level);

    return 0;
}

static int trace(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    log(LOG_TRACE, text);

    return 0;
}

static int warn(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    log(LOG_WARNING, text);

    return 0;
}

static const luaL_Reg functions[] = {
    { "debug", debug },
    { "error", error },
    { "fatal", fatal },
    { "info", info },
    { "level", level },
    { "trace", trace },
    { "warn", warn },
    { NULL, NULL }
};

int luaopen_pesto_log(lua_State* L)
{
    // We set internal errors to warning to avoid spamming the console
    // Users can set their own log level
    SetTraceLogCallback(raylibLog);
    SetTraceLogLevel(LOG_WARNING);

    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "log");

    lua_pop(L, 1);

    return 1;
}
