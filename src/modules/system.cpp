#include "api.h"

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

static int getClipboardText(lua_State* L)
{
    const char* result = GetClipboardText();
    lua_pushstring(L, result);

    return 1;
}

static int takeScreenshot(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    TakeScreenshot(filename);

    return 0;
}

static int openURL(lua_State* L)
{
    const char* url = luaL_checkstring(L, 1);
    OpenURL(url);

    return 0;
}

static int getOS(lua_State* L)
{
#ifdef _WIN32
    lua_pushstring(L, "windows");

    return 1;
#elif __APPLE__
    lua_pushstring(L, "macos");

    return 1;
#elif __linux__
    lua_pushstring(L, "linux");

    return 1;
#else
    lua_pushstring(L, "unknown");

    return 1;
#endif
}

static const luaL_Reg functions[] = {
    { "quit", quit },
    { "setClipboardText", setClipboardText },
    { "getClipboardText", getClipboardText },
    { "takeScreenshot", takeScreenshot },
    { "openURL", openURL },
    { NULL, NULL }
};

int luaopen_system(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "system");

    return 1;
}
