#include "api.h"

#define RRES_IMPLEMENTATION
#include "../lib/rres/rres.h"

#define RRES_RAYLIB_IMPLEMENTATION
#define RRES_SUPPORT_COMPRESSION_LZ4
#include "../lib/rres/rres-raylib.h"

static const char* getCompressionName(int compType)
{
    if (compType == RRES_COMP_NONE)
        return "none";
    else if (compType == RRES_COMP_DEFLATE)
        return "DEFLATE";
    else if (compType == RRES_COMP_LZ4)
        return "LZ4";
    else if (compType == RRES_COMP_QOI)
        return "QOI";
    else
        return "Undefined";
}

static const char* getCipherName(int cipherType)
{
    if (cipherType == RRES_CIPHER_NONE)
        return "none";
    else if (cipherType == RRES_CIPHER_AES)
        return "AES-256";
    else if (cipherType == RRES_CIPHER_XCHACHA20_POLY1305)
        return "XChaCha20";
    else
        return "Undefined";
}

static int getInfo(lua_State* L)
{
    const char* rresFilename = luaL_checkstring(L, 1);

    if (!FileExists(rresFilename)) {
        return luaL_error(L, "RRES file %s does not exist.", rresFilename);
    }

    rresCentralDir dir = rresLoadCentralDirectory(rresFilename);

    if (dir.count == 0) {
        return luaL_error(L, "RRES file %s does not contain a central directory.", rresFilename);
    }

    lua_newtable(L);

    for (unsigned int i = 0; i < dir.count; i++) {
        rresResourceChunkInfo info = rresLoadResourceChunkInfo(rresFilename, dir.entries[i].id);

        lua_newtable(L);

        lua_pushstring(L, "input");
        lua_pushstring(L, dir.entries[i].fileName);
        lua_settable(L, -3);

        lua_pushstring(L, "offset");
        lua_pushstring(L, TextFormat("0x%08x", dir.entries[i].offset));
        lua_settable(L, -3);

        lua_pushstring(L, "type");
        lua_pushstring(L, TextFormat("%c%c%c%c", info.type[0], info.type[1], info.type[2], info.type[3]));
        lua_settable(L, -3);

        lua_pushstring(L, "id");
        lua_pushstring(L, TextFormat("0x%08x", dir.entries[i].offset));
        lua_settable(L, -3);

        lua_pushstring(L, "compression");
        lua_pushstring(L, getCompressionName((int)info.compType));
        lua_settable(L, -3);

        lua_pushstring(L, "cipher");
        lua_pushstring(L, getCipherName((int)info.cipherType));
        lua_settable(L, -3);

        lua_pushstring(L, "baseSize");
        lua_pushstring(L, TextFormat("%i", info.baseSize));
        lua_settable(L, -3);

        lua_pushstring(L, "packedSize");
        lua_pushstring(L, TextFormat("%i", info.packedSize));
        lua_settable(L, -3);

        lua_pushstring(L, "nextOffset");
        lua_pushstring(L, TextFormat("%i", info.nextOffset));
        lua_settable(L, -3);

        lua_pushstring(L, "crc32");
        lua_pushstring(L, TextFormat("0x%08x", info.crc32));
        lua_settable(L, -3);

        lua_rawseti(L, -2, i + 1);
    }

    return 1;
}

static int loadText(lua_State* L)
{
    const char* rresFilename = luaL_checkstring(L, 1);
    const char* filename = luaL_checkstring(L, 2);

    if (!FileExists(rresFilename)) {
        return luaL_error(L, "RRES file %s does not exist.", rresFilename);
    }

    rresCentralDir dir = rresLoadCentralDirectory(rresFilename);

    if (dir.count == 0) {
        return luaL_error(L, "RRES file %s does not contain a central directory.", rresFilename);
    }

    unsigned int id = rresGetResourceId(dir, filename);
    rresResourceChunk chunk = rresLoadResourceChunk(rresFilename, id);

    int result = UnpackResourceChunk(&chunk);

    if (result != 0) {
        rresUnloadResourceChunk(chunk);
        rresUnloadCentralDirectory(dir);
    }

    if (result == 1) {
        return luaL_error(L, "Resource %s uses an unsupported encryption algorithm.", filename);
    } else if (result == 2) {
        return luaL_error(L, "Resource %s cannot be decrypted with provided password.", filename);
    } else if (result == 3) {
        return luaL_error(L, "Resource %s uses an unsupported compression algorithm.", filename);
    } else if (result == 4) {
        return luaL_error(L, "Resource %s cannot be decompressed.", filename);
    }

    char* text = LoadTextFromResource(chunk);

    rresUnloadResourceChunk(chunk);
    rresUnloadCentralDirectory(dir);

    lua_pushstring(L, text);

    return 1;
}

static int loadTexture(lua_State* L)
{
    const char* rresFilename = luaL_checkstring(L, 1);
    const char* filename = luaL_checkstring(L, 2);

    if (!FileExists(rresFilename)) {
        return luaL_error(L, "RRES file %s does not exist.", rresFilename);
    }

    rresCentralDir dir = rresLoadCentralDirectory(rresFilename);

    if (dir.count == 0) {
        return luaL_error(L, "RRES file %s does not contain a central directory.", rresFilename);
    }

    unsigned int id = rresGetResourceId(dir, filename);
    rresResourceChunk chunk = rresLoadResourceChunk(rresFilename, id);

    int result = UnpackResourceChunk(&chunk);

    if (result != 0) {
        rresUnloadResourceChunk(chunk);
        rresUnloadCentralDirectory(dir);
    }

    if (result == 1) {
        return luaL_error(L, "Resource %s uses an unsupported encryption algorithm.", filename);
    } else if (result == 2) {
        return luaL_error(L, "Resource %s cannot be decrypted with provided password.", filename);
    } else if (result == 3) {
        return luaL_error(L, "Resource %s uses an unsupported compression algorithm.", filename);
    } else if (result == 4) {
        return luaL_error(L, "Resource %s cannot be decompressed.", filename);
    }

    Image image = LoadImageFromResource(chunk);

    if (image.data == NULL) {
        rresUnloadResourceChunk(chunk);
        rresUnloadCentralDirectory(dir);

        return luaL_error(L, "Resource %s could not be loaded.", filename);
    }

    Texture texture = LoadTextureFromImage(image);
    UnloadImage(image);

    rresUnloadResourceChunk(chunk);
    rresUnloadCentralDirectory(dir);

    void* ud = lua_newuserdata(L, sizeof(Texture));
    memcpy(ud, &texture, sizeof(Texture));
    luaL_setmetatable(L, "Texture");

    return 1;
}

static const luaL_Reg functions[] = {
    { "getInfo", getInfo },
    { "loadText", loadText },
    { "loadTexture", loadTexture },
    { NULL, NULL }
};

int luaopen_rres(lua_State* L)
{
    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "rres");

    lua_pop(L, 1);

    return 1;
}
