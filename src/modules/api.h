#ifndef API_H
#define API_H

#include <lua.h>

// Pesto modules
int luaopen_pesto(lua_State* L);
int luaopen_filesystem(lua_State* L);
int luaopen_window(lua_State* L);

// Lua libraries
int luaopen_classic(lua_State* L);

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
