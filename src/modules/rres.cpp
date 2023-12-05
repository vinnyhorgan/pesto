#include "api.h"

#define RRES_IMPLEMENTATION
#include "../lib/rres/rres.h"

#define RRES_RAYLIB_IMPLEMENTATION
#define RRES_SUPPORT_COMPRESSION_LZ4
#define RRES_SUPPORT_ENCRYPTION_AES
#define RRES_SUPPORT_ENCRYPTION_XCHACHA20
#include "../lib/rres/rres-raylib.h"

static const char* GetCompressionName(int compType)
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

static const char* GetCipherName(int cipherType)
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

static unsigned char* LoadDataBuffer(rresResourceChunkData data, unsigned int rawSize)
{
    unsigned char* buffer = (unsigned char*)RRES_CALLOC((data.propCount + 1) * sizeof(unsigned int) + rawSize, 1);

    memcpy(buffer, &data.propCount, sizeof(unsigned int));
    for (int i = 0; i < data.propCount; i++)
        memcpy(buffer + (i + 1) * sizeof(unsigned int), &data.props[i], sizeof(unsigned int));
    memcpy(buffer + (data.propCount + 1) * sizeof(unsigned int), data.raw, rawSize);

    return buffer;
}

static void UnloadDataBuffer(unsigned char* buffer)
{
    RRES_FREE(buffer);
}

static int info(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    rresCentralDir dir = rresLoadCentralDirectory(filename);

    if (dir.count == 0)
        printf("WARNING: Central Directory not available\n"); // No central directory

    // NOTE: With no CDIR we can still load the contained resources info,
    // but we can't know the original input files that generated the resource chunks

    // Load ALL resource chunks info from .rres file
    unsigned int chunkCount = 0;
    rresResourceChunkInfo* infos = rresLoadResourceChunkInfoAll(filename, &chunkCount);

    unsigned int prevId = 0;

    // Display resource chunks info
    // NOTE: Central Directory relates input files to rres resource chunks,
    // some input files could generate multiple rres resource chunks (Font files)
    for (unsigned int i = 0; i < chunkCount; i++) {
        for (unsigned int j = 0; j < dir.count; j++) {
            if ((infos[i].id == dir.entries[j].id) && (infos[i].id != prevId)) {
                printf("Input File: %s\n", dir.entries[j].fileName);
                printf("Resource(s) Offset: 0x%08x\n", dir.entries[j].offset);
                prevId = dir.entries[j].id;
                break;
            }
        }

        printf("    Resource Chunk: %c%c%c%c\n", infos[i].type[0], infos[i].type[1], infos[i].type[2], infos[i].type[3]);
        printf("       > id:            0x%08x\n", infos[i].id);
        printf("       > compType:      %s (%i)\n", GetCompressionName((int)infos[i].compType), (int)infos[i].compType);
        printf("       > cipherType:    %s (%i)\n", GetCipherName((int)infos[i].cipherType), (int)infos[i].cipherType);
        printf("       > baseSize:      %i\n", infos[i].baseSize);
        printf("       > packedSize:    %i (%i%%)\n", infos[i].packedSize, (int)(((float)infos[i].packedSize / infos[i].baseSize) * 100)); // Get compression ratio
        printf("       > nextOffset:    %i\n", infos[i].nextOffset);
        printf("       > CRC32:         0x%08x\n", infos[i].crc32);
    }

    // Free allocated memory for chunks info
    RRES_FREE(infos);

    return 0;
}

static int saveText(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);
    const char* text = luaL_checkstring(L, 2);

    FILE* rresFile = fopen(filename, "wb");

    // Header

    rresFileHeader header;
    header.id[0] = 'r';
    header.id[1] = 'r';
    header.id[2] = 'e';
    header.id[3] = 's';
    header.version = 100;
    header.chunkCount = 1;
    header.cdOffset = 0;
    header.reserved = 0;

    fwrite(&header, sizeof(rresFileHeader), 1, rresFile);

    // Chunks

    rresResourceChunkInfo chunkInfo = { 0 };
    rresResourceChunkData chunkData = { 0 };

    unsigned char* buffer = NULL;

    // Text

    unsigned int rawSize = (unsigned int)strlen(text);

    chunkInfo.type[0] = 'T';
    chunkInfo.type[1] = 'E';
    chunkInfo.type[2] = 'X';
    chunkInfo.type[3] = 'T';

    chunkInfo.id = rresComputeCRC32((unsigned char*)"file", (int)strlen("file"));

    chunkInfo.compType = RRES_COMP_NONE;
    chunkInfo.cipherType = RRES_CIPHER_NONE;
    chunkInfo.flags = 0;
    chunkInfo.baseSize = 5 * sizeof(unsigned int) + rawSize;
    chunkInfo.packedSize = chunkInfo.baseSize;
    chunkInfo.nextOffset = 0;
    chunkInfo.reserved = 0;

    chunkData.propCount = 4;
    chunkData.props = (unsigned int*)RRES_CALLOC(chunkData.propCount, sizeof(unsigned int));
    chunkData.props[0] = rawSize;
    chunkData.props[1] = RRES_TEXT_ENCODING_UNDEFINED;
    chunkData.props[2] = RRES_CODE_LANG_UNDEFINED;
    chunkData.props[3] = 0x0409;
    chunkData.raw = (void*)text;

    buffer = LoadDataBuffer(chunkData, rawSize);

    chunkInfo.crc32 = rresComputeCRC32(buffer, chunkInfo.packedSize);

    fwrite(&chunkInfo, sizeof(rresResourceChunkInfo), 1, rresFile);
    fwrite(buffer, 1, chunkInfo.packedSize, rresFile);

    memset(&chunkInfo, 0, sizeof(rresResourceChunkInfo));
    RRES_FREE(chunkData.props);
    UnloadDataBuffer(buffer);

    fclose(rresFile);

    return 0;
}

static const luaL_Reg functions[] = {
    { "info", info },
    { "saveText", saveText },
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
