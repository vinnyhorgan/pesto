#include "api.h"

#include "../util.h"

#include "../../assets/icon.png.h"
#include "../../assets/noto.ttf.h"

bool shouldQuit = false;
Font currentFont;

static int close(lua_State* L)
{
    CloseWindow();

    return 0;
}

static int getCurrentMonitor(lua_State* L)
{
    int result = GetCurrentMonitor();
    lua_pushinteger(L, result);

    return 1;
}

static int getDPIScale(lua_State* L)
{
    Vector2 result = GetWindowScaleDPI();
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int getHeight(lua_State* L)
{
    int result = GetRenderHeight();
    lua_pushinteger(L, result);

    return 1;
}

static int getMonitorCount(lua_State* L)
{
    int result = GetMonitorCount();
    lua_pushinteger(L, result);

    return 1;
}

static int getMonitorHeight(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    int result = GetMonitorHeight(monitor);
    lua_pushinteger(L, result);

    return 1;
}

static int getMonitorName(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    const char* result = GetMonitorName(monitor);
    lua_pushstring(L, result);

    return 1;
}

static int getMonitorPhysicalHeight(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    int result = GetMonitorPhysicalHeight(monitor);
    lua_pushinteger(L, result);

    return 1;
}

static int getMonitorPhysicalWidth(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    int result = GetMonitorPhysicalWidth(monitor);
    lua_pushinteger(L, result);

    return 1;
}

static int getMonitorPosition(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    Vector2 result = GetMonitorPosition(monitor);
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int getMonitorRefreshRate(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    int result = GetMonitorRefreshRate(monitor);
    lua_pushinteger(L, result);

    return 1;
}

static int getMonitorWidth(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    int result = GetMonitorWidth(monitor);
    lua_pushinteger(L, result);

    return 1;
}

static int getPosition(lua_State* L)
{
    Vector2 result = GetWindowPosition();
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int getResizable(lua_State* L)
{
    bool result = IsWindowState(FLAG_WINDOW_RESIZABLE);
    lua_pushboolean(L, result);

    return 1;
}

static int getVSync(lua_State* L)
{
    bool result = IsWindowState(FLAG_VSYNC_HINT);
    lua_pushboolean(L, result);

    return 1;
}

static int getWidth(lua_State* L)
{
    int result = GetRenderWidth();
    lua_pushinteger(L, result);

    return 1;
}

static int init(lua_State* L)
{
    if (IsWindowReady()) {
        return 0;
    }

    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    const char* title = luaL_checkstring(L, 3);

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(width, height, title);

    SetExitKey(KEY_NULL);

    currentFont = LoadFont_Noto();

    Image icon;
    icon.data = ICON_DATA;
    icon.width = ICON_WIDTH;
    icon.height = ICON_HEIGHT;
    icon.format = ICON_FORMAT;
    icon.mipmaps = 1;

    SetWindowIcon(icon);

    return 0;
}

static int isFocused(lua_State* L)
{
    bool result = IsWindowFocused();
    lua_pushboolean(L, result);

    return 1;
}

static int isFullscreen(lua_State* L)
{
    bool result = IsWindowFullscreen();
    lua_pushboolean(L, result);

    return 1;
}

static int isHidden(lua_State* L)
{
    bool result = IsWindowHidden();
    lua_pushboolean(L, result);

    return 1;
}

static int isMaximized(lua_State* L)
{
    bool result = IsWindowMaximized();
    lua_pushboolean(L, result);

    return 1;
}

static int isMinimized(lua_State* L)
{
    bool result = IsWindowMinimized();
    lua_pushboolean(L, result);

    return 1;
}

static int isReady(lua_State* L)
{
    bool result = IsWindowReady();
    lua_pushboolean(L, result);

    return 1;
}

static int isResized(lua_State* L)
{
    bool result = IsWindowResized();
    lua_pushboolean(L, result);

    return 1;
}

static int maximize(lua_State* L)
{
    MaximizeWindow();

    return 0;
}

static int minimize(lua_State* L)
{
    MinimizeWindow();

    return 0;
}

static int restore(lua_State* L)
{
    RestoreWindow();

    return 0;
}

static int setFocused(lua_State* L)
{
    SetWindowFocused();

    return 0;
}

static int setIcon(lua_State* L)
{
    Texture icon = *(Texture*)luaL_checkudata(L, 1, "Texture");
    Image image = LoadImageFromTexture(icon);
    SetWindowIcon(image);

    return 0;
}

static int setMaxSize(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    SetWindowMaxSize(width, height);

    return 0;
}

static int setMinSize(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    SetWindowMinSize(width, height);

    return 0;
}

static int setMonitor(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    SetWindowMonitor(monitor);

    return 0;
}

static int setOpacity(lua_State* L)
{
    float opacity = (float)luaL_checknumber(L, 1);

    if (opacity < 0.0f || opacity > 1.0f) {
        return luaL_error(L, "Opacity must be between 0 and 1");
    }

    SetWindowOpacity(opacity);

    return 0;
}

static int setPosition(lua_State* L)
{
    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    SetWindowPosition(x, y);

    return 0;
}

static int setResizable(lua_State* L)
{
    bool resizable = check_boolean(L, 1);

    if (resizable) {
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    } else {
        ClearWindowState(FLAG_WINDOW_RESIZABLE);
    }

    return 0;
}

static int setSize(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    SetWindowSize(width, height);

    return 0;
}

static int setTitle(lua_State* L)
{
    const char* title = luaL_checkstring(L, 1);
    SetWindowTitle(title);

    return 0;
}

static int setTargetFPS(lua_State* L)
{
    int fps = (int)luaL_checkinteger(L, 1);
    SetTargetFPS(fps);

    return 0;
}

static int setVSync(lua_State* L)
{
    bool resizable = check_boolean(L, 1);

    if (resizable) {
        SetWindowState(FLAG_VSYNC_HINT);
    } else {
        ClearWindowState(FLAG_VSYNC_HINT);
    }

    return 0;
}

static int shouldClose(lua_State* L)
{
    bool result = WindowShouldClose() || shouldQuit;
    lua_pushboolean(L, result);

    return 1;
}

static int toggleBorderless(lua_State* L)
{
    ToggleBorderlessWindowed();

    return 0;
}

static int toggleFullscreen(lua_State* L)
{
    ToggleFullscreen();

    return 0;
}

static const luaL_Reg functions[] = {
    { "close", close },
    { "getCurrentMonitor", getCurrentMonitor },
    { "getDPIScale", getDPIScale },
    { "getHeight", getHeight },
    { "getMonitorCount", getMonitorCount },
    { "getMonitorHeight", getMonitorHeight },
    { "getMonitorName", getMonitorName },
    { "getMonitorPhysicalHeight", getMonitorPhysicalHeight },
    { "getMonitorPhysicalWidth", getMonitorPhysicalWidth },
    { "getMonitorPosition", getMonitorPosition },
    { "getMonitorRefreshRate", getMonitorRefreshRate },
    { "getMonitorWidth", getMonitorWidth },
    { "getPosition", getPosition },
    { "getResizable", getResizable },
    { "getVSync", getVSync },
    { "getWidth", getWidth },
    { "init", init },
    { "isFocused", isFocused },
    { "isFullscreen", isFullscreen },
    { "isHidden", isHidden },
    { "isMaximized", isMaximized },
    { "isMinimized", isMinimized },
    { "isReady", isReady },
    { "isResized", isResized },
    { "maximize", maximize },
    { "minimize", minimize },
    { "restore", restore },
    { "setFocused", setFocused },
    { "setIcon", setIcon },
    { "setMaxSize", setMaxSize },
    { "setMinSize", setMinSize },
    { "setMonitor", setMonitor },
    { "setOpacity", setOpacity },
    { "setPosition", setPosition },
    { "setResizable", setResizable },
    { "setSize", setSize },
    { "setTitle", setTitle },
    { "setTargetFPS", setTargetFPS },
    { "setVSync", setVSync },
    { "shouldClose", shouldClose },
    { "toggleBorderless", toggleBorderless },
    { "toggleFullscreen", toggleFullscreen },
    { NULL, NULL }
};

int luaopen_window(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "window");

    lua_pop(L, 1);

    return 1;
}
