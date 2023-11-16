#include "api.h"

static int loadFileText(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    char* text = LoadFileText(filename);

    if (text != NULL) {
        lua_pushstring(L, text);
        UnloadFileText(text);

        return 1;
    } else {
        lua_pushnil(L);

        return 1;
    }
}

static int saveFileText(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    const char* text = luaL_checkstring(L, 2);
    bool result = SaveFileText(filename, text);
    lua_pushboolean(L, result);

    return 1;
}

static int fileExists(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    bool result = FileExists(filename);
    lua_pushboolean(L, result);

    return 1;
}

static int directoryExists(lua_State* L)
{
    const char* dirpath = luaL_checkstring(L, 1);
    bool result = DirectoryExists(dirpath);
    lua_pushboolean(L, result);

    return 1;
}

static int isFileExtension(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    const char* ext = luaL_checkstring(L, 2);
    bool result = IsFileExtension(filename, ext);
    lua_pushboolean(L, result);

    return 1;
}

static int getFileLength(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    int result = GetFileLength(filename);
    lua_pushinteger(L, result);

    return 1;
}

static int getFileExtension(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    const char* result = GetFileExtension(filename);
    lua_pushstring(L, result);

    return 1;
}

static int getFileName(lua_State* L)
{
    const char* filepath = luaL_checkstring(L, 1);
    const char* result = GetFileName(filepath);
    lua_pushstring(L, result);

    return 1;
}

static int getFileNameWithoutExt(lua_State* L)
{
    const char* filepath = luaL_checkstring(L, 1);
    const char* result = GetFileNameWithoutExt(filepath);
    lua_pushstring(L, result);

    return 1;
}

static int getDirectoryPath(lua_State* L)
{
    const char* filepath = luaL_checkstring(L, 1);
    const char* result = GetDirectoryPath(filepath);
    lua_pushstring(L, result);

    return 1;
}

static int getPrevDirectoryPath(lua_State* L)
{
    const char* dirpath = luaL_checkstring(L, 1);
    const char* result = GetPrevDirectoryPath(dirpath);
    lua_pushstring(L, result);

    return 1;
}

static int getWorkingDirectory(lua_State* L)
{
    const char* result = GetWorkingDirectory();
    lua_pushstring(L, result);

    return 1;
}

static int getApplicationDirectory(lua_State* L)
{
    const char* result = GetApplicationDirectory();
    lua_pushstring(L, result);

    return 1;
}

static int changeDirectory(lua_State* L)
{
    const char* dir = luaL_checkstring(L, 1);
    bool result = ChangeDirectory(dir);
    lua_pushboolean(L, result);

    return 1;
}

static int isPathFile(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    bool result = IsPathFile(path);
    lua_pushboolean(L, result);

    return 1;
}

static const luaL_Reg functions[] = {
    { "loadFileText", loadFileText },
    { "saveFileText", saveFileText },
    { "fileExists", fileExists },
    { "directoryExists", directoryExists },
    { "isFileExtension", isFileExtension },
    { "getFileLength", getFileLength },
    { "getFileExtension", getFileExtension },
    { "getFileName", getFileName },
    { "getFileNameWithoutExt", getFileNameWithoutExt },
    { "getDirectoryPath", getDirectoryPath },
    { "getPrevDirectoryPath", getPrevDirectoryPath },
    { "getWorkingDirectory", getWorkingDirectory },
    { "getApplicationDirectory", getApplicationDirectory },
    { "changeDirectory", changeDirectory },
    { "isPathFile", isPathFile },
    { NULL, NULL }
};

int luaopen_filesystem(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "filesystem");

    return 1;
}
