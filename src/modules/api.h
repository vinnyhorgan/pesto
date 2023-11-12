#ifndef API_H
#define API_H

#include <lua.h>

int luaopen_pesto(lua_State* L);
int luaopen_window(lua_State* L);
int luaopen_filesystem(lua_State* L);

#endif
