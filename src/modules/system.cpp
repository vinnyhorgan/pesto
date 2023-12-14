#include "api.h"

static int getClipboardText(lua_State* L)
{
    const char* result = GetClipboardText();
    lua_pushstring(L, result);

    return 1;
}

static int getOS(lua_State* L)
{
#ifdef _WIN32
    lua_pushstring(L, "windows");
#elif __APPLE__
    lua_pushstring(L, "macos");
#elif __linux__
    lua_pushstring(L, "linux");
#else
    lua_pushstring(L, "unknown");
#endif

    return 1;
}

static int getTime(lua_State* L)
{
    double result = GetTime();
    lua_pushnumber(L, result);

    return 1;
}

static int openURL(lua_State* L)
{
    const char* url = luaL_checkstring(L, 1);
    OpenURL(url);

    return 0;
}

static int quit(lua_State* L)
{
    shouldQuit = true;

    return 0;
}

static int setClipboardText(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    SetClipboardText(text);

    return 0;
}

static int sleep(lua_State* L)
{
    double seconds = luaL_checknumber(L, 1);
    WaitTime(seconds);

    return 0;
}

static int takeScreenshot(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    TakeScreenshot(filename);

    return 0;
}

static const luaL_Reg functions[] = {
    { "getClipboardText", getClipboardText },
    { "getOS", getOS },
    { "getTime", getTime },
    { "openURL", openURL },
    { "quit", quit },
    { "setClipboardText", setClipboardText },
    { "sleep", sleep },
    { "takeScreenshot", takeScreenshot },
    { NULL, NULL }
};

int luaopen_pesto_system(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "system");

    lua_pop(L, 1);

    return 1;
}
