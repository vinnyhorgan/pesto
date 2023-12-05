#include "api.h"

#include "../../assets/icon.png.h"
#include "../../assets/noto.ttf.h"

bool shouldQuit = false;
Font currentFont;

static int init(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    const char* title = luaL_checkstring(L, 3);

    SetTraceLogLevel(LOG_WARNING);

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(width, height, title);

    Image icon;
    icon.data = ICON_DATA;
    icon.width = ICON_WIDTH;
    icon.height = ICON_HEIGHT;
    icon.format = ICON_FORMAT;
    icon.mipmaps = 1;

    SetWindowIcon(icon);

    // Generating the font header requires opengl context

    // Font font = LoadFontEx(PROJECT_PATH "assets/noto.ttf", 18, NULL, 0);
    // ExportFontAsCode(font, PROJECT_PATH "assets/noto.ttf.h");
    // UnloadFont(font);

    currentFont = LoadFont_Noto();

    SetExitKey(KEY_NULL);

    return 0;
}

static int close(lua_State* L)
{
    CloseWindow();

    return 0;
}

static int shouldClose(lua_State* L)
{
    bool result = WindowShouldClose() || shouldQuit;
    lua_pushboolean(L, result);

    return 1;
}

static int isReady(lua_State* L)
{
    bool result = IsWindowReady();
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

static int isMinimized(lua_State* L)
{
    bool result = IsWindowMinimized();
    lua_pushboolean(L, result);

    return 1;
}

static int isMaximized(lua_State* L)
{
    bool result = IsWindowMaximized();
    lua_pushboolean(L, result);

    return 1;
}

static int isFocused(lua_State* L)
{
    bool result = IsWindowFocused();
    lua_pushboolean(L, result);

    return 1;
}

static int isResized(lua_State* L)
{
    bool result = IsWindowResized();
    lua_pushboolean(L, result);

    return 1;
}

static int getResizable(lua_State* L)
{
    bool result = IsWindowState(FLAG_WINDOW_RESIZABLE);
    lua_pushboolean(L, result);

    return 1;
}

static int setResizable(lua_State* L)
{
    bool resizable = lua_toboolean(L, 1);

    if (resizable) {
        SetWindowState(FLAG_WINDOW_RESIZABLE);
    } else {
        ClearWindowState(FLAG_WINDOW_RESIZABLE);
    }

    return 0;
}

static int toggleFullscreen(lua_State* L)
{
    ToggleFullscreen();

    return 0;
}

static int toggleBorderless(lua_State* L)
{
    ToggleBorderlessWindowed();

    return 0;
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

static int setTitle(lua_State* L)
{
    const char* title = luaL_checkstring(L, 1);
    SetWindowTitle(title);

    return 0;
}

static int setPosition(lua_State* L)
{
    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    SetWindowPosition(x, y);

    return 0;
}

static int setMonitor(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    SetWindowMonitor(monitor);

    return 0;
}

static int setMinSize(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    SetWindowMinSize(width, height);

    return 0;
}

static int setMaxSize(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    SetWindowMaxSize(width, height);

    return 0;
}

static int setSize(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    SetWindowSize(width, height);

    return 0;
}

static int setOpacity(lua_State* L)
{
    float opacity = (float)luaL_checknumber(L, 1);
    SetWindowOpacity(opacity);

    return 0;
}

static int setFocused(lua_State* L)
{
    SetWindowFocused();

    return 0;
}

static int getWidth(lua_State* L)
{
    int result = GetScreenWidth();
    lua_pushinteger(L, result);

    return 1;
}

static int getHeight(lua_State* L)
{
    int result = GetScreenHeight();
    lua_pushinteger(L, result);

    return 1;
}

static int getRenderWidth(lua_State* L)
{
    int result = GetRenderWidth();
    lua_pushinteger(L, result);

    return 1;
}

static int getRenderHeight(lua_State* L)
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

static int getCurrentMonitor(lua_State* L)
{
    int result = GetCurrentMonitor();
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

static int getMonitorWidth(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    int result = GetMonitorWidth(monitor);
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

static int getMonitorPhysicalWidth(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    int result = GetMonitorPhysicalWidth(monitor);
    lua_pushinteger(L, result);

    return 1;
}

static int getMonitorPhysicalHeight(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    int result = GetMonitorPhysicalHeight(monitor);
    lua_pushinteger(L, result);

    return 1;
}

static int getMonitorRefreshRate(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    int result = GetMonitorRefreshRate(monitor);
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

static int getScaleDPI(lua_State* L)
{
    Vector2 result = GetWindowScaleDPI();
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int getMonitorName(lua_State* L)
{
    int monitor = (int)luaL_checkinteger(L, 1);
    const char* result = GetMonitorName(monitor);
    lua_pushstring(L, result);

    return 1;
}

static int beginDrawing(lua_State* L)
{
    BeginDrawing();

    return 0;
}

static int endDrawing(lua_State* L)
{
    EndDrawing();

    return 0;
}

static int setTargetFPS(lua_State* L)
{
    int fps = (int)luaL_checkinteger(L, 1);
    SetTargetFPS(fps);

    return 0;
}

static int getDelta(lua_State* L)
{
    float result = GetFrameTime();
    lua_pushnumber(L, result);

    return 1;
}

static int getTime(lua_State* L)
{
    double result = GetTime();
    lua_pushnumber(L, result);

    return 1;
}

static int getFPS(lua_State* L)
{
    int result = GetFPS();
    lua_pushinteger(L, result);

    return 1;
}

static int wait(lua_State* L)
{
    float seconds = (float)luaL_checknumber(L, 1);
    WaitTime(seconds);

    return 0;
}

static const luaL_Reg functions[] = {
    { "init", init },
    { "close", close },
    { "shouldClose", shouldClose },
    { "isReady", isReady },
    { "isFullscreen", isFullscreen },
    { "isHidden", isHidden },
    { "isMinimized", isMinimized },
    { "isMaximized", isMaximized },
    { "isFocused", isFocused },
    { "isResized", isResized },
    { "getResizable", getResizable },
    { "setResizable", setResizable },
    { "toggleFullscreen", toggleFullscreen },
    { "toggleBorderless", toggleBorderless },
    { "maximize", maximize },
    { "minimize", minimize },
    { "restore", restore },
    { "setTitle", setTitle },
    { "setPosition", setPosition },
    { "setMonitor", setMonitor },
    { "setMinSize", setMinSize },
    { "setMaxSize", setMaxSize },
    { "setSize", setSize },
    { "setOpacity", setOpacity },
    { "setFocused", setFocused },
    { "getWidth", getWidth },
    { "getHeight", getHeight },
    { "getRenderWidth", getRenderWidth },
    { "getRenderHeight", getRenderHeight },
    { "getMonitorCount", getMonitorCount },
    { "getCurrentMonitor", getCurrentMonitor },
    { "getMonitorPosition", getMonitorPosition },
    { "getMonitorWidth", getMonitorWidth },
    { "getMonitorHeight", getMonitorHeight },
    { "getMonitorPhysicalWidth", getMonitorPhysicalWidth },
    { "getMonitorPhysicalHeight", getMonitorPhysicalHeight },
    { "getMonitorRefreshRate", getMonitorRefreshRate },
    { "getPosition", getPosition },
    { "getScaleDPI", getScaleDPI },
    { "getMonitorName", getMonitorName },
    { "beginDrawing", beginDrawing },
    { "endDrawing", endDrawing },
    { "setTargetFPS", setTargetFPS },
    { "getDelta", getDelta },
    { "getTime", getTime },
    { "getFPS", getFPS },
    { "wait", wait },
    { NULL, NULL }
};

int luaopen_window(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "window");

    return 1;
}
