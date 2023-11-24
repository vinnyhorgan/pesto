#include "api.h"

#include <string.h>

static int clear(lua_State* L)
{
    int r = (int)luaL_optinteger(L, 1, 0);
    int g = (int)luaL_optinteger(L, 2, 0);
    int b = (int)luaL_optinteger(L, 3, 0);
    int a = (int)luaL_optinteger(L, 4, 255);

    ClearBackground(Color { (unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a });

    return 0;
}

static int text(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);

    DrawTextEx(font, text, Vector2 { (float)x, (float)y }, (float)font.baseSize, 0, WHITE);

    return 0;
}

static int loadTexture(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    Texture2D result = LoadTexture(filename);

    void* ud = lua_newuserdata(L, sizeof(Texture2D));
    memcpy(ud, &result, sizeof(Texture2D));

    luaL_setmetatable(L, "Texture2D");

    return 1;
}

static int drawTexture(lua_State* L)
{
    Texture2D img = *(Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    int x = (int)luaL_checknumber(L, 2);
    int y = (int)luaL_checknumber(L, 3);

    DrawTexture(img, x, y, WHITE);

    return 0;
}

static const luaL_Reg functions[] = {
    { "clear", clear },
    { "text", text },
    { "loadTexture", loadTexture },
    { "drawTexture", drawTexture },
    { NULL, NULL }
};

// Metatable functions
static int indexTexture2D(lua_State* L)
{
    Texture2D img = *(Texture2D*)luaL_checkudata(L, 1, "Texture2D");
    const char* key = luaL_checkstring(L, 2);

    if (TextIsEqual(key, "width"))
        lua_pushinteger(L, img.width);
    else if (TextIsEqual(key, "height"))
        lua_pushinteger(L, img.height);
    else if (TextIsEqual(key, "mipmaps"))
        lua_pushinteger(L, img.mipmaps);
    else if (TextIsEqual(key, "format"))
        lua_pushinteger(L, img.format);
    else if (TextIsEqual(key, "id"))
        lua_pushinteger(L, img.id);
    else
        return 0;

    return 1;
}

int luaopen_graphics(lua_State* L)
{
    luaL_newmetatable(L, "Texture2D");
    lua_pushcfunction(L, &indexTexture2D);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);

    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "graphics");

    return 1;
}
