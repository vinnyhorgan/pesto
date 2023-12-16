#ifndef DEPS_H
#define DEPS_H

#include <lua.hpp>

extern "C" {
int luaopen_enet(lua_State* L);
int luaopen_http(lua_State* L);
int luaopen_utf8(lua_State* L);
}

#endif
