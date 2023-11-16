#ifndef API_H
#define API_H

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include <raylib.h>

int luaopen_pesto(lua_State* L);

// Pesto modules
int luaopen_filesystem(lua_State* L);
int luaopen_graphics(lua_State* L);
int luaopen_log(lua_State* L);
int luaopen_window(lua_State* L);

// Lua libraries
int luaopen_bump(lua_State* L);
int luaopen_classic(lua_State* L);
int luaopen_flux(lua_State* L);
int luaopen_inspect(lua_State* L);
int luaopen_json(lua_State* L);
int luaopen_lume(lua_State* L);
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
