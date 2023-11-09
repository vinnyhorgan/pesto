#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <raylib.h>

int main(int argc, char* argv[])
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Pesto");
    SetTargetFPS(60);

    Texture2D wabbit_alpha = LoadTexture(ASSETS_PATH "wabbit_alpha.png");

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_loadfile(L, ASSETS_PATH "test.lua") || lua_pcall(L, 0, 0, 0)) {
        printf("Error: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawTexture(wabbit_alpha, 0, 0, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
