#include "api.h"

#include <filesystem>

static int changeDirectory(lua_State* L)
{
    const char* dir = luaL_checkstring(L, 1);
    bool result = ChangeDirectory(dir);
    lua_pushboolean(L, result);

    return 1;
}

static int copy(lua_State* L)
{
    const char* src = luaL_checkstring(L, 1);
    const char* dest = luaL_checkstring(L, 2);

    try {
        std::filesystem::copy(src, dest, std::filesystem::copy_options::recursive);
    } catch (const std::exception& e) {
        return luaL_error(L, "Failed to copy file: %s", e.what());
    }

    return 0;
}

static int createDirectory(lua_State* L)
{
    const char* dirpath = luaL_checkstring(L, 1);

    try {
        bool result = std::filesystem::create_directory(dirpath);
        lua_pushboolean(L, result);
    } catch (const std::exception& e) {
        return luaL_error(L, "Failed to create directory: %s", e.what());
    }

    return 1;
}

static int exists(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    if (FileExists(filename) || DirectoryExists(filename)) {
        lua_pushboolean(L, true);
    } else {
        lua_pushboolean(L, false);
    }

    return 1;
}

static int getApplicationDirectory(lua_State* L)
{
    const char* result = GetApplicationDirectory();
    lua_pushstring(L, result);

    return 1;
}

static int getDirectoryItems(lua_State* L)
{
    const char* basepath = luaL_checkstring(L, 1);
    const char* filter = NULL;

    if (lua_gettop(L) >= 2) {
        filter = luaL_checkstring(L, 2);
    }

    bool scanSubdirs = lua_toboolean(L, 3);

    FilePathList result = LoadDirectoryFilesEx(basepath, filter, scanSubdirs);

    lua_newtable(L);

    if (result.count > 0) {
        for (int i = 0; i < (int)result.count; i++) {
            lua_pushstring(L, result.paths[i]);
            lua_rawseti(L, -2, i + 1);
        }

        UnloadDirectoryFiles(result);
    }

    return 1;
}

static int getDirectoryPath(lua_State* L)
{
    const char* filepath = luaL_checkstring(L, 1);
    const char* result = GetDirectoryPath(filepath);
    lua_pushstring(L, result);

    return 1;
}

static int getDroppedItems(lua_State* L)
{
    FilePathList result = LoadDroppedFiles();

    lua_newtable(L);

    if (result.count > 0) {
        for (int i = 0; i < (int)result.count; i++) {
            lua_pushstring(L, result.paths[i]);
            lua_rawseti(L, -2, i + 1);
        }

        UnloadDroppedFiles(result);
    }

    return 1;
}

static int getFilename(lua_State* L)
{
    const char* filepath = luaL_checkstring(L, 1);
    const char* result = GetFileName(filepath);
    lua_pushstring(L, result);

    return 1;
}

static int getLastModified(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    long result = GetFileModTime(filename);
    lua_pushinteger(L, result);

    return 1;
}

static int getSize(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    int result = GetFileLength(filename);
    lua_pushinteger(L, result);

    return 1;
}

static int getWorkingDirectory(lua_State* L)
{
    const char* result = GetWorkingDirectory();
    lua_pushstring(L, result);

    return 1;
}

static int isDirectory(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    bool result = IsPathFile(path);

    if (result) {
        lua_pushboolean(L, false);
    } else {
        bool directoryExists = DirectoryExists(path);
        lua_pushboolean(L, directoryExists);
    }

    return 1;
}

static int isFile(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    bool result = IsPathFile(path);
    lua_pushboolean(L, result);

    return 1;
}

static int isFileDropped(lua_State* L)
{
    bool result = IsFileDropped();
    lua_pushboolean(L, result);

    return 1;
}

static int read(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    char* result = LoadFileText(filename);

    if (result != NULL) {
        lua_pushstring(L, result);
        UnloadFileText(result);
    } else {
        lua_pushnil(L);
    }

    return 1;
}

static int remove(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    try {
        bool result = std::filesystem::remove(filename);
        lua_pushboolean(L, result);
    } catch (const std::exception& e) {
        return luaL_error(L, "Failed to remove file: %s", e.what());
    }

    return 1;
}

static int rename(lua_State* L)
{
    const char* src = luaL_checkstring(L, 1);
    const char* dest = luaL_checkstring(L, 2);

    try {
        std::filesystem::rename(src, dest);
    } catch (const std::exception& e) {
        return luaL_error(L, "Failed to rename file: %s", e.what());
    }

    return 0;
}

static int write(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    const char* text = luaL_checkstring(L, 2);
    bool result = SaveFileText(filename, (char*)text);
    lua_pushboolean(L, result);

    return 1;
}

static const luaL_Reg functions[] = {
    { "changeDirectory", changeDirectory },
    { "copy", copy },
    { "createDirectory", createDirectory },
    { "exists", exists },
    { "getApplicationDirectory", getApplicationDirectory },
    { "getDirectoryItems", getDirectoryItems },
    { "getDirectoryPath", getDirectoryPath },
    { "getDroppedItems", getDroppedItems },
    { "getFilename", getFilename },
    { "getLastModified", getLastModified },
    { "getSize", getSize },
    { "getWorkingDirectory", getWorkingDirectory },
    { "isDirectory", isDirectory },
    { "isFile", isFile },
    { "isFileDropped", isFileDropped },
    { "read", read },
    { "remove", remove },
    { "rename", rename },
    { "write", write },
    { NULL, NULL }
};

int luaopen_pesto_filesystem(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "filesystem");

    lua_pop(L, 1);

    return 1;
}
