#ifndef DEPS_H
#define DEPS_H

extern "C" {
int luaopen_enet(struct lua_State* L);
int luaopen_http(struct lua_State* L);
int luaopen_utf8(struct lua_State* L);
}

#endif
