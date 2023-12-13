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
int luaopen_audio(lua_State* L);
int luaopen_filesystem(lua_State* L);
int luaopen_gamepad(lua_State* L);
int luaopen_graphics(lua_State* L);
int luaopen_imgui(lua_State* L);
int luaopen_keyboard(lua_State* L);
int luaopen_log(lua_State* L);
int luaopen_pmath(lua_State* L); // luaopen_math conflicts with lua internals
int luaopen_mouse(lua_State* L);
int luaopen_rres(lua_State* L);
int luaopen_system(lua_State* L);
int luaopen_window(lua_State* L);

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

// Luasocket
int luaopen_ftp(lua_State* L);
int luaopen_headers(lua_State* L);
int luaopen_http(lua_State* L);
int luaopen_ltn12(lua_State* L);
int luaopen_mbox(lua_State* L);
int luaopen_mime(lua_State* L);
int luaopen_smtp(lua_State* L);
int luaopen_socket(lua_State* L);
int luaopen_tp(lua_State* L);
int luaopen_url(lua_State* L);

#endif
