#ifndef UTIL_H
#define UTIL_H

#define PESTO_VERSION_MAJOR 0
#define PESTO_VERSION_MINOR 1
#define PESTO_VERSION_PATCH 0
#define PESTO_VERSION_CODENAME "Saucy Serenade"

#include <lua.h>

void preload(lua_State* L, lua_CFunction f, const char* name);
void require(lua_State* L, const char* name);
void generateHeader(const char* filename);
void generateHeaders();

#endif
