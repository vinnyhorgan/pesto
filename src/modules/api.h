#ifndef API_H
#define API_H

#include <lua.hpp>
#include <raylib.h>

// Global variables
extern bool shouldQuit;
extern Font defaultFont;
extern Font defaultFontMedium;
extern Font defaultFontBig;
extern Shader sdfShader;
extern Image icon;
extern Image githubLogo;
extern Image loveLogo;
extern Image luaLogo;
extern Image raylibLogo;

int luaopen_pesto(lua_State* L);

// Pesto modules
int luaopen_pesto_audio(lua_State* L);
int luaopen_pesto_filesystem(lua_State* L);
int luaopen_pesto_gamepad(lua_State* L);
int luaopen_pesto_graphics(lua_State* L);
int luaopen_pesto_imgui(lua_State* L);
int luaopen_pesto_keyboard(lua_State* L);
int luaopen_pesto_log(lua_State* L);
int luaopen_pesto_math(lua_State* L);
int luaopen_pesto_mouse(lua_State* L);
int luaopen_pesto_rres(lua_State* L);
int luaopen_pesto_system(lua_State* L);
int luaopen_pesto_window(lua_State* L);

// Lua libraries
int luaopen_astar(lua_State* L);
int luaopen_brinevector(lua_State* L);
int luaopen_bump(lua_State* L);
int luaopen_classic(lua_State* L);
int luaopen_flux(lua_State* L);
int luaopen_inspect(lua_State* L);
int luaopen_json(lua_State* L);
int luaopen_lume(lua_State* L);
int luaopen_signal(lua_State* L);
int luaopen_tick(lua_State* L);
int luaopen_tiny(lua_State* L);

#endif
