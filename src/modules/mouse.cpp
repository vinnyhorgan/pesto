#include "api.h"

static int disable(lua_State* L)
{
    DisableCursor();

    return 0;
}

static int enable(lua_State* L)
{
    EnableCursor();

    return 0;
}

static int getDelta(lua_State* L)
{
    Vector2 result = GetMouseDelta();
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int getX(lua_State* L)
{
    int x = GetMouseX();
    lua_pushinteger(L, x);

    return 1;
}

static int getY(lua_State* L)
{
    int y = GetMouseY();
    lua_pushinteger(L, y);

    return 1;
}

static int getWheelMove(lua_State* L)
{
    Vector2 result = GetMouseWheelMoveV();
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int getPosition(lua_State* L)
{
    Vector2 result = GetMousePosition();
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int hide(lua_State* L)
{
    HideCursor();

    return 0;
}

static int isDown(lua_State* L)
{
    int button = (int)luaL_checkinteger(L, 1);
    bool result = IsMouseButtonDown(button);
    lua_pushboolean(L, result);

    return 1;
}

static int isHidden(lua_State* L)
{
    bool result = IsCursorHidden();
    lua_pushboolean(L, result);

    return 1;
}

static int isOnScreen(lua_State* L)
{
    bool result = IsCursorOnScreen();
    lua_pushboolean(L, result);

    return 1;
}

static int isPressed(lua_State* L)
{
    int button = (int)luaL_checkinteger(L, 1);
    bool result = IsMouseButtonPressed(button);
    lua_pushboolean(L, result);

    return 1;
}

static int isReleased(lua_State* L)
{
    int button = (int)luaL_checkinteger(L, 1);
    bool result = IsMouseButtonReleased(button);
    lua_pushboolean(L, result);

    return 1;
}

static int isUp(lua_State* L)
{
    int button = (int)luaL_checkinteger(L, 1);
    bool result = IsMouseButtonUp(button);
    lua_pushboolean(L, result);

    return 1;
}

static int setCursor(lua_State* L)
{
    const char* cursor = luaL_checkstring(L, 1);

    if (TextIsEqual(cursor, "default")) {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    } else if (TextIsEqual(cursor, "arrow")) {
        SetMouseCursor(MOUSE_CURSOR_ARROW);
    } else if (TextIsEqual(cursor, "ibeam")) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
    } else if (TextIsEqual(cursor, "crosshair")) {
        SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);
    } else if (TextIsEqual(cursor, "pointingHand")) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else if (TextIsEqual(cursor, "resizeEW")) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
    } else if (TextIsEqual(cursor, "resizeNS")) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
    } else if (TextIsEqual(cursor, "resizeNWSE")) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
    } else if (TextIsEqual(cursor, "resizeNESW")) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_NESW);
    } else if (TextIsEqual(cursor, "resizeAll")) {
        SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
    } else if (TextIsEqual(cursor, "notAllowed")) {
        SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);
    } else {
        return luaL_error(L, "Invalid cursor type: %s", cursor);
    }

    return 0;
}

static int setScale(lua_State* L)
{
    float x = (float)luaL_checknumber(L, 1);
    float y = (float)luaL_checknumber(L, 2);
    SetMouseScale(x, y);

    return 0;
}

static int setOffset(lua_State* L)
{
    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    SetMouseOffset(x, y);

    return 0;
}

static int setPosition(lua_State* L)
{
    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    SetMousePosition(x, y);

    return 0;
}

static int show(lua_State* L)
{
    ShowCursor();

    return 0;
}

static const luaL_Reg functions[] = {
    { "disable", disable },
    { "enable", enable },
    { "getDelta", getDelta },
    { "getX", getX },
    { "getY", getY },
    { "getWheelMove", getWheelMove },
    { "getPosition", getPosition },
    { "hide", hide },
    { "isDown", isDown },
    { "isHidden", isHidden },
    { "isOnScreen", isOnScreen },
    { "isPressed", isPressed },
    { "isReleased", isReleased },
    { "isUp", isUp },
    { "setCursor", setCursor },
    { "setScale", setScale },
    { "setOffset", setOffset },
    { "setPosition", setPosition },
    { "show", show },
    { NULL, NULL }
};

int luaopen_pesto_mouse(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "mouse");

    lua_pop(L, 1);

    return 1;
}
