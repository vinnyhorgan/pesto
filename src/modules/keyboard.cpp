#include "api.h"

static int stringToKey(const char* key)
{
    if (TextIsEqual(key, "null"))
        return KEY_NULL;
    else if (TextIsEqual(key, "apostrophe"))
        return KEY_APOSTROPHE;
    else if (TextIsEqual(key, "comma"))
        return KEY_COMMA;
    else if (TextIsEqual(key, "minus"))
        return KEY_MINUS;
    else if (TextIsEqual(key, "period"))
        return KEY_PERIOD;
    else if (TextIsEqual(key, "slash"))
        return KEY_SLASH;
    else if (TextIsEqual(key, "zero"))
        return KEY_ZERO;
    else if (TextIsEqual(key, "one"))
        return KEY_ONE;
    else if (TextIsEqual(key, "two"))
        return KEY_TWO;
    else if (TextIsEqual(key, "three"))
        return KEY_THREE;
    else if (TextIsEqual(key, "four"))
        return KEY_FOUR;
    else if (TextIsEqual(key, "five"))
        return KEY_FIVE;
    else if (TextIsEqual(key, "six"))
        return KEY_SIX;
    else if (TextIsEqual(key, "seven"))
        return KEY_SEVEN;
    else if (TextIsEqual(key, "eight"))
        return KEY_EIGHT;
    else if (TextIsEqual(key, "nine"))
        return KEY_NINE;
    else if (TextIsEqual(key, "semicolon"))
        return KEY_SEMICOLON;
    else if (TextIsEqual(key, "equal"))
        return KEY_EQUAL;
    else if (TextIsEqual(key, "a"))
        return KEY_A;
    else if (TextIsEqual(key, "b"))
        return KEY_B;
    else if (TextIsEqual(key, "c"))
        return KEY_C;
    else if (TextIsEqual(key, "d"))
        return KEY_D;
    else if (TextIsEqual(key, "e"))
        return KEY_E;
    else if (TextIsEqual(key, "f"))
        return KEY_F;
    else if (TextIsEqual(key, "g"))
        return KEY_G;
    else if (TextIsEqual(key, "h"))
        return KEY_H;
    else if (TextIsEqual(key, "i"))
        return KEY_I;
    else if (TextIsEqual(key, "j"))
        return KEY_J;
    else if (TextIsEqual(key, "k"))
        return KEY_K;
    else if (TextIsEqual(key, "l"))
        return KEY_L;
    else if (TextIsEqual(key, "m"))
        return KEY_M;
    else if (TextIsEqual(key, "n"))
        return KEY_N;
    else if (TextIsEqual(key, "o"))
        return KEY_O;
    else if (TextIsEqual(key, "p"))
        return KEY_P;
    else if (TextIsEqual(key, "q"))
        return KEY_Q;
    else if (TextIsEqual(key, "r"))
        return KEY_R;
    else if (TextIsEqual(key, "s"))
        return KEY_S;
    else if (TextIsEqual(key, "t"))
        return KEY_T;
    else if (TextIsEqual(key, "u"))
        return KEY_U;
    else if (TextIsEqual(key, "v"))
        return KEY_V;
    else if (TextIsEqual(key, "w"))
        return KEY_W;
    else if (TextIsEqual(key, "x"))
        return KEY_X;
    else if (TextIsEqual(key, "y"))
        return KEY_Y;
    else if (TextIsEqual(key, "z"))
        return KEY_Z;
    else if (TextIsEqual(key, "leftBracket"))
        return KEY_LEFT_BRACKET;
    else if (TextIsEqual(key, "backslash"))
        return KEY_BACKSLASH;
    else if (TextIsEqual(key, "rightBracket"))
        return KEY_RIGHT_BRACKET;
    else if (TextIsEqual(key, "grave"))
        return KEY_GRAVE;
    else if (TextIsEqual(key, "space"))
        return KEY_SPACE;
    else if (TextIsEqual(key, "escape"))
        return KEY_ESCAPE;
    else if (TextIsEqual(key, "enter"))
        return KEY_ENTER;
    else if (TextIsEqual(key, "tab"))
        return KEY_TAB;
    else if (TextIsEqual(key, "backspace"))
        return KEY_BACKSPACE;
    else if (TextIsEqual(key, "insert"))
        return KEY_INSERT;
    else if (TextIsEqual(key, "delete"))
        return KEY_DELETE;
    else if (TextIsEqual(key, "right"))
        return KEY_RIGHT;
    else if (TextIsEqual(key, "left"))
        return KEY_LEFT;
    else if (TextIsEqual(key, "down"))
        return KEY_DOWN;
    else if (TextIsEqual(key, "up"))
        return KEY_UP;
    else if (TextIsEqual(key, "pageUp"))
        return KEY_PAGE_UP;
    else if (TextIsEqual(key, "pageDown"))
        return KEY_PAGE_DOWN;
    else if (TextIsEqual(key, "home"))
        return KEY_HOME;
    else if (TextIsEqual(key, "end"))
        return KEY_END;
    else if (TextIsEqual(key, "capsLock"))
        return KEY_CAPS_LOCK;
    else if (TextIsEqual(key, "scrollLock"))
        return KEY_SCROLL_LOCK;
    else if (TextIsEqual(key, "numLock"))
        return KEY_NUM_LOCK;
    else if (TextIsEqual(key, "printScreen"))
        return KEY_PRINT_SCREEN;
    else if (TextIsEqual(key, "pause"))
        return KEY_PAUSE;
    else if (TextIsEqual(key, "f1"))
        return KEY_F1;
    else if (TextIsEqual(key, "f2"))
        return KEY_F2;
    else if (TextIsEqual(key, "f3"))
        return KEY_F3;
    else if (TextIsEqual(key, "f4"))
        return KEY_F4;
    else if (TextIsEqual(key, "f5"))
        return KEY_F5;
    else if (TextIsEqual(key, "f6"))
        return KEY_F6;
    else if (TextIsEqual(key, "f7"))
        return KEY_F7;
    else if (TextIsEqual(key, "f8"))
        return KEY_F8;
    else if (TextIsEqual(key, "f9"))
        return KEY_F9;
    else if (TextIsEqual(key, "f10"))
        return KEY_F10;
    else if (TextIsEqual(key, "f11"))
        return KEY_F11;
    else if (TextIsEqual(key, "f12"))
        return KEY_F12;
    else if (TextIsEqual(key, "leftShift"))
        return KEY_LEFT_SHIFT;
    else if (TextIsEqual(key, "leftControl"))
        return KEY_LEFT_CONTROL;
    else if (TextIsEqual(key, "leftAlt"))
        return KEY_LEFT_ALT;
    else if (TextIsEqual(key, "leftSuper"))
        return KEY_LEFT_SUPER;
    else if (TextIsEqual(key, "rightShift"))
        return KEY_RIGHT_SHIFT;
    else if (TextIsEqual(key, "rightControl"))
        return KEY_RIGHT_CONTROL;
    else if (TextIsEqual(key, "rightAlt"))
        return KEY_RIGHT_ALT;
    else if (TextIsEqual(key, "rightSuper"))
        return KEY_RIGHT_SUPER;
    else if (TextIsEqual(key, "menu"))
        return KEY_MENU;
    else if (TextIsEqual(key, "kp0"))
        return KEY_KP_0;
    else if (TextIsEqual(key, "kp1"))
        return KEY_KP_1;
    else if (TextIsEqual(key, "kp2"))
        return KEY_KP_2;
    else if (TextIsEqual(key, "kp3"))
        return KEY_KP_3;
    else if (TextIsEqual(key, "kp4"))
        return KEY_KP_4;
    else if (TextIsEqual(key, "kp5"))
        return KEY_KP_5;
    else if (TextIsEqual(key, "kp6"))
        return KEY_KP_6;
    else if (TextIsEqual(key, "kp7"))
        return KEY_KP_7;
    else if (TextIsEqual(key, "kp8"))
        return KEY_KP_8;
    else if (TextIsEqual(key, "kp9"))
        return KEY_KP_9;
    else if (TextIsEqual(key, "kpDecimal"))
        return KEY_KP_DECIMAL;
    else if (TextIsEqual(key, "kpDivide"))
        return KEY_KP_DIVIDE;
    else if (TextIsEqual(key, "kpMultiply"))
        return KEY_KP_MULTIPLY;
    else if (TextIsEqual(key, "kpSubtract"))
        return KEY_KP_SUBTRACT;
    else if (TextIsEqual(key, "kpAdd"))
        return KEY_KP_ADD;
    else if (TextIsEqual(key, "kpEnter"))
        return KEY_KP_ENTER;
    else if (TextIsEqual(key, "kpEqual"))
        return KEY_KP_EQUAL;
    else
        return KEY_NULL;
}

static int isPressed(lua_State* L)
{
    const char* key = luaL_checkstring(L, 1);
    bool result = IsKeyPressed(stringToKey(key));
    lua_pushboolean(L, result);

    return 1;
}

static int isPressedRepeat(lua_State* L)
{
    const char* key = luaL_checkstring(L, 1);
    bool result = IsKeyPressedRepeat(stringToKey(key));
    lua_pushboolean(L, result);

    return 1;
}

static int isDown(lua_State* L)
{
    const char* key = luaL_checkstring(L, 1);
    bool result = IsKeyDown(stringToKey(key));
    lua_pushboolean(L, result);

    return 1;
}

static int isReleased(lua_State* L)
{
    const char* key = luaL_checkstring(L, 1);
    bool result = IsKeyReleased(stringToKey(key));
    lua_pushboolean(L, result);

    return 1;
}

static int isUp(lua_State* L)
{
    const char* key = luaL_checkstring(L, 1);
    bool result = IsKeyUp(stringToKey(key));
    lua_pushboolean(L, result);

    return 1;
}

static int getPressed(lua_State* L)
{
    int result = GetKeyPressed();
    lua_pushinteger(L, result);

    return 1;
}

static int getCharPressed(lua_State* L)
{
    int result = GetCharPressed();
    lua_pushinteger(L, result);

    return 1;
}

static const luaL_Reg functions[] = {
    { "isPressed", isPressed },
    { "isPressedRepeat", isPressedRepeat },
    { "isDown", isDown },
    { "isReleased", isReleased },
    { "isUp", isUp },
    { "getPressed", getPressed },
    { "getCharPressed", getCharPressed },
    { NULL, NULL }
};

int luaopen_keyboard(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "keyboard");

    return 1;
}
