#ifndef UTIL_H
#define UTIL_H

#define PESTO_VERSION_MAJOR 0
#define PESTO_VERSION_MINOR 1
#define PESTO_VERSION_PATCH 0
#define PESTO_VERSION_CODENAME "Saucy Serenade"

#include <lua.hpp>
#include <raylib.h>

void preload(lua_State* L, lua_CFunction f, const char* name);
void require(lua_State* L, const char* name);
int check_boolean(lua_State* L, int index);
void generateHeaders();
void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);

#endif
