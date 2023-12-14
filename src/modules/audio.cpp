#include "api.h"

#include <string.h>

static int close(lua_State* L)
{
    CloseAudioDevice();

    return 0;
}

static int getVolume(lua_State* L)
{
    float result = GetMasterVolume();
    lua_pushnumber(L, result);

    return 1;
}

static int init(lua_State* L)
{
    if (IsAudioDeviceReady()) {
        return 0;
    }

    InitAudioDevice();

    return 0;
}

static int isReady(lua_State* L)
{
    bool result = IsAudioDeviceReady();
    lua_pushboolean(L, result);

    return 1;
}

static int loadSound(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    if (!FileExists(filename)) {
        return luaL_error(L, "File %s does not exist.", filename);
    }

    Sound result = LoadSound(filename);

    void* ud = lua_newuserdata(L, sizeof(Sound));
    memcpy(ud, &result, sizeof(Sound));
    luaL_setmetatable(L, "Sound");

    return 1;
}

static int loadStream(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    if (!FileExists(filename)) {
        return luaL_error(L, "File %s does not exist.", filename);
    }

    Music result = LoadMusicStream(filename);

    void* ud = lua_newuserdata(L, sizeof(Music));
    memcpy(ud, &result, sizeof(Music));
    luaL_setmetatable(L, "Stream");

    return 1;
}

static int setVolume(lua_State* L)
{
    float volume = (float)luaL_checknumber(L, 1);
    SetMasterVolume(volume);

    return 0;
}

static const luaL_Reg functions[] = {
    { "close", close },
    { "getVolume", getVolume },
    { "init", init },
    { "isReady", isReady },
    { "loadSound", loadSound },
    { "loadStream", loadStream },
    { "setVolume", setVolume },
    { NULL, NULL }
};

static int gcSound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    UnloadSound(sound);

    return 0;
}

static int tostringSound(lua_State* L)
{
    lua_pushstring(L, "Sound");

    return 1;
}

static int isPlayingSound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    bool result = IsSoundPlaying(sound);
    lua_pushboolean(L, result);

    return 1;
}

static int isReadySound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    bool result = IsSoundReady(sound);
    lua_pushboolean(L, result);

    return 1;
}

static int pauseSound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    PauseSound(sound);

    return 0;
}

static int playSound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    PlaySound(sound);

    return 0;
}

static int resumeSound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    ResumeSound(sound);

    return 0;
}

static int setPanSound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    float pan = (float)luaL_checknumber(L, 2);
    SetSoundPan(sound, pan);

    return 0;
}

static int setPitchSound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    float pitch = (float)luaL_checknumber(L, 2);
    SetSoundPitch(sound, pitch);

    return 0;
}

static int setVolumeSound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    float volume = (float)luaL_checknumber(L, 2);
    SetSoundVolume(sound, volume);

    return 0;
}

static int stopSound(lua_State* L)
{
    Sound sound = *(Sound*)luaL_checkudata(L, 1, "Sound");
    StopSound(sound);

    return 0;
}

static const luaL_Reg soundMethods[] = {
    { "__gc", gcSound },
    { "__tostring", tostringSound },
    { "isPlaying", isPlayingSound },
    { "isReady", isReadySound },
    { "pause", pauseSound },
    { "play", playSound },
    { "resume", resumeSound },
    { "setPan", setPanSound },
    { "setPitch", setPitchSound },
    { "setVolume", setVolumeSound },
    { "stop", stopSound },
    { NULL, NULL }
};

static int gcStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    UnloadMusicStream(stream);

    return 0;
}

static int tostringStream(lua_State* L)
{
    lua_pushstring(L, "Stream");

    return 1;
}

static int getLengthStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    float result = GetMusicTimeLength(stream);
    lua_pushnumber(L, result);

    return 1;
}

static int getPositionStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    float result = GetMusicTimePlayed(stream);
    lua_pushnumber(L, result);

    return 1;
}

static int isPlayingStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    bool result = IsMusicStreamPlaying(stream);
    lua_pushboolean(L, result);

    return 1;
}

static int isReadyStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    bool result = IsMusicReady(stream);
    lua_pushboolean(L, result);

    return 1;
}

static int pauseStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    PauseMusicStream(stream);

    return 0;
}

static int playStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    PlayMusicStream(stream);

    return 0;
}

static int resumeStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    ResumeMusicStream(stream);

    return 0;
}

static int seekStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    float position = (float)luaL_checknumber(L, 2);
    SeekMusicStream(stream, position);

    return 0;
}

static int setPanStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    float pan = (float)luaL_checknumber(L, 2);
    SetMusicPan(stream, pan);

    return 0;
}

static int setPitchStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    float pitch = (float)luaL_checknumber(L, 2);
    SetMusicPitch(stream, pitch);

    return 0;
}

static int setVolumeStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    float volume = (float)luaL_checknumber(L, 2);
    SetMusicVolume(stream, volume);

    return 0;
}

static int stopStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    StopMusicStream(stream);

    return 0;
}

static int updateStream(lua_State* L)
{
    Music stream = *(Music*)luaL_checkudata(L, 1, "Stream");
    UpdateMusicStream(stream);

    return 0;
}

static const luaL_Reg streamMethods[] = {
    { "__gc", gcStream },
    { "__tostring", tostringStream },
    { "getLength", getLengthStream },
    { "getPosition", getPositionStream },
    { "isPlaying", isPlayingStream },
    { "isReady", isReadyStream },
    { "pause", pauseStream },
    { "play", playStream },
    { "resume", resumeStream },
    { "seek", seekStream },
    { "setPan", setPanStream },
    { "setPitch", setPitchStream },
    { "setVolume", setVolumeStream },
    { "stop", stopStream },
    { "update", updateStream },
    { NULL, NULL }
};

int luaopen_pesto_audio(lua_State* L)
{
    luaL_newmetatable(L, "Sound");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, soundMethods, 0);
    lua_pop(L, 1);

    luaL_newmetatable(L, "Stream");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, streamMethods, 0);
    lua_pop(L, 1);

    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "audio");

    lua_pop(L, 1);

    return 1;
}
