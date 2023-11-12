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

void generateHeaders()
{
    int bootSize;
    unsigned char* boot = LoadFileData(PROJECT_PATH "src/scripts/boot.lua", &bootSize);
    ExportDataAsCode(boot, bootSize, PROJECT_PATH "src/scripts/boot.lua.h");

    // Lua libraries

    int bumpSize;
    unsigned char* bump = LoadFileData(PROJECT_PATH "src/lib/lua/bump.lua", &bumpSize);
    ExportDataAsCode(bump, bumpSize, PROJECT_PATH "src/lib/lua/bump.lua.h");

    int classicSize;
    unsigned char* classic = LoadFileData(PROJECT_PATH "src/lib/lua/classic.lua", &classicSize);
    ExportDataAsCode(classic, classicSize, PROJECT_PATH "src/lib/lua/classic.lua.h");

    int fluxSize;
    unsigned char* flux = LoadFileData(PROJECT_PATH "src/lib/lua/flux.lua", &fluxSize);
    ExportDataAsCode(flux, fluxSize, PROJECT_PATH "src/lib/lua/flux.lua.h");

    int inspectSize;
    unsigned char* inspect = LoadFileData(PROJECT_PATH "src/lib/lua/inspect.lua", &inspectSize);
    ExportDataAsCode(inspect, inspectSize, PROJECT_PATH "src/lib/lua/inspect.lua.h");

    int jsonSize;
    unsigned char* json = LoadFileData(PROJECT_PATH "src/lib/lua/json.lua", &jsonSize);
    ExportDataAsCode(json, jsonSize, PROJECT_PATH "src/lib/lua/json.lua.h");

    int lumeSize;
    unsigned char* lume = LoadFileData(PROJECT_PATH "src/lib/lua/lume.lua", &lumeSize);
    ExportDataAsCode(lume, lumeSize, PROJECT_PATH "src/lib/lua/lume.lua.h");

    int tickSize;
    unsigned char* tick = LoadFileData(PROJECT_PATH "src/lib/lua/tick.lua", &tickSize);
    ExportDataAsCode(tick, tickSize, PROJECT_PATH "src/lib/lua/tick.lua.h");

    int tinySize;
    unsigned char* tiny = LoadFileData(PROJECT_PATH "src/lib/lua/tiny.lua", &tinySize);
    ExportDataAsCode(tiny, tinySize, PROJECT_PATH "src/lib/lua/tiny.lua.h");

    // Luasocket

    int ftpSize;
    unsigned char* ftp = LoadFileData(PROJECT_PATH "src/lib/luasocket/ftp.lua", &ftpSize);
    ExportDataAsCode(ftp, ftpSize, PROJECT_PATH "src/lib/luasocket/ftp.lua.h");

    int headersSize;
    unsigned char* headers = LoadFileData(PROJECT_PATH "src/lib/luasocket/headers.lua", &headersSize);
    ExportDataAsCode(headers, headersSize, PROJECT_PATH "src/lib/luasocket/headers.lua.h");

    int httpSize;
    unsigned char* http = LoadFileData(PROJECT_PATH "src/lib/luasocket/http.lua", &httpSize);
    ExportDataAsCode(http, httpSize, PROJECT_PATH "src/lib/luasocket/http.lua.h");

    int ltn12Size;
    unsigned char* ltn12 = LoadFileData(PROJECT_PATH "src/lib/luasocket/ltn12.lua", &ltn12Size);
    ExportDataAsCode(ltn12, ltn12Size, PROJECT_PATH "src/lib/luasocket/ltn12.lua.h");

    int mboxSize;
    unsigned char* mbox = LoadFileData(PROJECT_PATH "src/lib/luasocket/mbox.lua", &mboxSize);
    ExportDataAsCode(mbox, mboxSize, PROJECT_PATH "src/lib/luasocket/mbox.lua.h");

    int mimeSize;
    unsigned char* mime = LoadFileData(PROJECT_PATH "src/lib/luasocket/mime.lua", &mimeSize);
    ExportDataAsCode(mime, mimeSize, PROJECT_PATH "src/lib/luasocket/mime.lua.h");

    int smtpSize;
    unsigned char* smtp = LoadFileData(PROJECT_PATH "src/lib/luasocket/smtp.lua", &smtpSize);
    ExportDataAsCode(smtp, smtpSize, PROJECT_PATH "src/lib/luasocket/smtp.lua.h");

    int socketSize;
    unsigned char* socket = LoadFileData(PROJECT_PATH "src/lib/luasocket/socket.lua", &socketSize);
    ExportDataAsCode(socket, socketSize, PROJECT_PATH "src/lib/luasocket/socket.lua.h");

    int tpSize;
    unsigned char* tp = LoadFileData(PROJECT_PATH "src/lib/luasocket/tp.lua", &tpSize);
    ExportDataAsCode(tp, tpSize, PROJECT_PATH "src/lib/luasocket/tp.lua.h");

    int urlSize;
    unsigned char* url = LoadFileData(PROJECT_PATH "src/lib/luasocket/url.lua", &urlSize);
    ExportDataAsCode(url, urlSize, PROJECT_PATH "src/lib/luasocket/url.lua.h");
}