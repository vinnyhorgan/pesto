#include "util.h"

#include <raylib.h>

void preload(lua_State* L, lua_CFunction f, const char* name)
{
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    lua_pushcfunction(L, f);
    lua_setfield(L, -2, name);
    lua_pop(L, 2);
}

void require(lua_State* L, const char* name)
{
    lua_getglobal(L, "require");
    lua_pushstring(L, name);
    lua_call(L, 1, 1);
}

void generateHeader(const char* filename)
{
    unsigned int size;
    unsigned char* data = LoadFileData(TextFormat("%s%s", PROJECT_PATH, filename), &size);
    ExportDataAsCode(data, size, TextFormat("%s%s.h", PROJECT_PATH, filename));
}

void generateHeaders()
{
    generateHeader("src/scripts/boot.lua");
    generateHeader("src/lib/lua/bump.lua");
    generateHeader("src/lib/lua/classic.lua");
    generateHeader("src/lib/lua/flux.lua");
    generateHeader("src/lib/lua/inspect.lua");
    generateHeader("src/lib/lua/json.lua");
    generateHeader("src/lib/lua/lume.lua");
    generateHeader("src/lib/lua/tick.lua");
    generateHeader("src/lib/lua/tiny.lua");

    generateHeader("src/lib/luasocket/ftp.lua");
    generateHeader("src/lib/luasocket/headers.lua");
    generateHeader("src/lib/luasocket/http.lua");
    generateHeader("src/lib/luasocket/ltn12.lua");
    generateHeader("src/lib/luasocket/mbox.lua");
    generateHeader("src/lib/luasocket/mime.lua");
    generateHeader("src/lib/luasocket/smtp.lua");
    generateHeader("src/lib/luasocket/socket.lua");
    generateHeader("src/lib/luasocket/tp.lua");
    generateHeader("src/lib/luasocket/url.lua");
}
