#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#define PESTO_VERSION_MAJOR 0
#define PESTO_VERSION_MINOR 1
#define PESTO_VERSION_PATCH 0
#define PESTO_VERSION_ALIAS "Saucy Serenade"

// Code from raylib-lua <3

#define LuaPush_Texture2D(L, tex) LuaPushOpaqueTypeWithMetatable(L, tex, Texture2D)
#define LuaPushOpaqueTypeWithMetatable(L, str, meta) LuaPushOpaqueWithMetatable(L, &str, sizeof(str), #meta)
#define LuaGetArgument_Texture2D(L, tex) *(Texture2D*)LuaGetArgumentOpaqueTypeWithMetatable(L, tex, "Texture2D")

static void LuaPushOpaqueWithMetatable(lua_State* L, void* ptr, size_t size, const char* metatable_name)
{
    void* ud = lua_newuserdata(L, size);
    memcpy(ud, ptr, size);
    luaL_setmetatable(L, metatable_name);
}

static void* LuaGetArgumentOpaqueTypeWithMetatable(lua_State* L, int index, const char* metatable_name)
{
    return luaL_checkudata(L, index, metatable_name);
}

static int LuaIndexTexture2D(lua_State* L)
{
    Texture2D img = LuaGetArgument_Texture2D(L, 1);
    const char* key = luaL_checkstring(L, 2);

    if (!strcmp(key, "width"))
        lua_pushinteger(L, img.width);
    else if (!strcmp(key, "height"))
        lua_pushinteger(L, img.height);
    else if (!strcmp(key, "mipmaps"))
        lua_pushinteger(L, img.mipmaps);
    else if (!strcmp(key, "format"))
        lua_pushinteger(L, img.format);
    else if (!strcmp(key, "id"))
        lua_pushinteger(L, img.id);
    else
        return 0;

    return 1;
}

int loadTexture(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    Texture2D texture = LoadTexture(TextFormat("%s%s", ASSETS_PATH, path));
    LuaPush_Texture2D(L, texture);
    return 1;
}

int drawTexture(lua_State* L)
{
    Texture2D texture = LuaGetArgument_Texture2D(L, 1);
    int posX = (int)luaL_checkinteger(L, 2);
    int posY = (int)luaL_checkinteger(L, 3);
    DrawTexture(texture, posX, posY, WHITE);
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc > 1 && (TextIsEqual(argv[1], "-v") || TextIsEqual(argv[1], "--version"))) {
        printf("Pesto %d.%d.%d (%s)\n", PESTO_VERSION_MAJOR, PESTO_VERSION_MINOR, PESTO_VERSION_PATCH, PESTO_VERSION_ALIAS);
        return 0;
    }

    if (argc > 1 && (TextIsEqual(argv[1], "-h") || TextIsEqual(argv[1], "--help"))) {
        printf(
            "Usage: pesto [options] [<source>]\n\n"
            "options:\n"
            "  -h, --help\t\tShow help and exit\n"
            "  -v, --version\t\tShow version and exit\n\n"
            "<source> a folder that contains a main.lua file\n");

        return 0;
    }

#ifdef NDEBUG
    SetTraceLogLevel(LOG_WARNING);
#endif

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Pesto");
    SetTargetFPS(60);

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    luaL_newmetatable(L, "Texture2D");
    lua_pushcfunction(L, &LuaIndexTexture2D);
    lua_setfield(L, -2, "__index");
    lua_pop(L, 1);

    lua_register(L, "loadTexture", loadTexture);
    lua_register(L, "drawTexture", drawTexture);

    if (luaL_dofile(L, ASSETS_PATH "test.lua") == LUA_OK) {
        lua_pop(L, lua_gettop(L));
    }

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        lua_getglobal(L, "update");

        if (lua_isfunction(L, -1)) {
            lua_pushnumber(L, GetFrameTime());

            if (lua_pcall(L, 1, 0, 0) == LUA_OK) {
                lua_pop(L, lua_gettop(L));
            } else {
                printf("Error: %s\n", lua_tostring(L, -1));
                exit(1);
            }
        }

        EndDrawing();
    }

    lua_close(L);

    CloseWindow();

    return 0;
}
