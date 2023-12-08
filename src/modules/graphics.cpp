#include "api.h"

#include <string.h>

#include "../util.h"

static bool safe = false;
static Color currentColor = WHITE;

static int beginDrawing(lua_State* L)
{
    BeginDrawing();
    safe = true;

    return 0;
}

static int circle(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    float radius = (float)luaL_checknumber(L, 3);
    DrawCircle(x, y, radius, currentColor);

    return 0;
}

static int circleLines(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    float radius = (float)luaL_checknumber(L, 3);
    DrawCircleLines(x, y, radius, currentColor);

    return 0;
}

static int clear(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    unsigned char r = (unsigned char)luaL_optinteger(L, 1, 0);
    unsigned char g = (unsigned char)luaL_optinteger(L, 2, 0);
    unsigned char b = (unsigned char)luaL_optinteger(L, 3, 0);
    unsigned char a = (unsigned char)luaL_optinteger(L, 4, 255);
    ClearBackground({ r, g, b, a });

    return 0;
}

static int endDrawing(lua_State* L)
{
    EndDrawing();
    safe = false;

    return 0;
}

static int getColor(lua_State* L)
{
    lua_pushinteger(L, currentColor.r);
    lua_pushinteger(L, currentColor.g);
    lua_pushinteger(L, currentColor.b);
    lua_pushinteger(L, currentColor.a);

    return 4;
}

static int getDelta(lua_State* L)
{
    float result = GetFrameTime();
    lua_pushnumber(L, result);

    return 1;
}

static int getFPS(lua_State* L)
{
    int result = GetFPS();
    lua_pushinteger(L, result);

    return 1;
}

static int line(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x1 = (int)luaL_checkinteger(L, 1);
    int y1 = (int)luaL_checkinteger(L, 2);
    int x2 = (int)luaL_checkinteger(L, 3);
    int y2 = (int)luaL_checkinteger(L, 4);
    DrawLine(x1, y1, x2, y2, currentColor);

    return 0;
}

static int loadCanvas(lua_State* L)
{
    int width = (int)luaL_checkinteger(L, 1);
    int height = (int)luaL_checkinteger(L, 2);
    RenderTexture result = LoadRenderTexture(width, height);

    void* ud = lua_newuserdata(L, sizeof(RenderTexture));
    memcpy(ud, &result, sizeof(RenderTexture));
    luaL_setmetatable(L, "Canvas");

    return 1;
}

static int loadFont(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    if (!FileExists(filename)) {
        return luaL_error(L, "File %s does not exist.", filename);
    }

    int size = (int)luaL_checkinteger(L, 2);
    Font result = LoadFontEx(filename, size, NULL, 0);

    void* ud = lua_newuserdata(L, sizeof(Font));
    memcpy(ud, &result, sizeof(Font));
    luaL_setmetatable(L, "Font");

    return 1;
}

static int loadShader(lua_State* L)
{
    const char* vsFilename = luaL_checkstring(L, 1);
    const char* fsFilename = luaL_checkstring(L, 2);

    if (!FileExists(vsFilename)) {
        return luaL_error(L, "File %s does not exist.", vsFilename);
    }

    if (!FileExists(fsFilename)) {
        return luaL_error(L, "File %s does not exist.", fsFilename);
    }

    Shader result = LoadShader(vsFilename, fsFilename);

    void* ud = lua_newuserdata(L, sizeof(Shader));
    memcpy(ud, &result, sizeof(Shader));
    luaL_setmetatable(L, "Shader");

    return 1;
}

static int loadTexture(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    if (!FileExists(filename)) {
        return luaL_error(L, "File %s does not exist.", filename);
    }

    Texture result = LoadTexture(filename);

    void* ud = lua_newuserdata(L, sizeof(Texture));
    memcpy(ud, &result, sizeof(Texture));
    luaL_setmetatable(L, "Texture");

    return 1;
}

static int pixel(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    DrawPixel(x, y, currentColor);

    return 0;
}

static int polygon(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int sides = (int)luaL_checkinteger(L, 3);
    float radius = (float)luaL_checknumber(L, 4);
    float rotation = (float)luaL_checknumber(L, 5);
    DrawPoly({ (float)x, (float)y }, sides, radius, rotation, currentColor);

    return 0;
}

static int polygonLines(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int sides = (int)luaL_checkinteger(L, 3);
    float radius = (float)luaL_checknumber(L, 4);
    float rotation = (float)luaL_checknumber(L, 5);
    DrawPolyLines({ (float)x, (float)y }, sides, radius, rotation, currentColor);

    return 0;
}

static int rectangle(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int width = (int)luaL_checkinteger(L, 3);
    int height = (int)luaL_checkinteger(L, 4);
    DrawRectangle(x, y, width, height, currentColor);

    return 0;
}

static int rectangleLines(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int width = (int)luaL_checkinteger(L, 3);
    int height = (int)luaL_checkinteger(L, 4);
    DrawRectangleLines(x, y, width, height, currentColor);

    return 0;
}

static int setColor(lua_State* L)
{
    unsigned char r = (unsigned char)luaL_optinteger(L, 1, 0);
    unsigned char g = (unsigned char)luaL_optinteger(L, 2, 0);
    unsigned char b = (unsigned char)luaL_optinteger(L, 3, 0);
    unsigned char a = (unsigned char)luaL_optinteger(L, 4, 255);
    currentColor = { r, g, b, a };

    return 0;
}

static int setFont(lua_State* L)
{
    Font font = *(Font*)luaL_checkudata(L, 1, "Font");
    currentFont = font;

    return 0;
}

static int text(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    const char* text = luaL_checkstring(L, 1);
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    DrawTextEx(currentFont, text, { (float)x, (float)y }, (float)currentFont.baseSize, 0, currentColor);

    return 0;
}

static int wrappedText(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    const char* text = luaL_checkstring(L, 1);
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    int w = (int)luaL_checkinteger(L, 4);
    int h = (int)luaL_checkinteger(L, 5);
    DrawTextBoxedSelectable(currentFont, text, { (float)x, (float)y, (float)w, (float)h }, (float)currentFont.baseSize, 0, true, currentColor, 0, 0, WHITE, WHITE);

    return 0;
}

static const luaL_Reg functions[] = {
    { "beginDrawing", beginDrawing },
    { "circle", circle },
    { "circleLines", circleLines },
    { "clear", clear },
    { "endDrawing", endDrawing },
    { "getColor", getColor },
    { "getDelta", getDelta },
    { "getFPS", getFPS },
    { "line", line },
    { "loadCanvas", loadCanvas },
    { "loadFont", loadFont },
    { "loadShader", loadShader },
    { "loadTexture", loadTexture },
    { "pixel", pixel },
    { "polygon", polygon },
    { "polygonLines", polygonLines },
    { "rectangle", rectangle },
    { "rectangleLines", rectangleLines },
    { "setColor", setColor },
    { "setFont", setFont },
    { "text", text },
    { "wrappedText", wrappedText },
    { NULL, NULL }
};

static int gcTexture(lua_State* L)
{
    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    UnloadTexture(texture);

    return 0;
}

static int tostringTexture(lua_State* L)
{
    lua_pushstring(L, "Texture");

    return 1;
}

static int drawTexture(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    DrawTexture(texture, x, y, currentColor);

    return 0;
}

static int drawProTexture(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    float srcX = (float)luaL_checknumber(L, 2);
    float srcY = (float)luaL_checknumber(L, 3);
    float srcW = (float)luaL_checknumber(L, 4);
    float srcH = (float)luaL_checknumber(L, 5);
    float destX = (float)luaL_checknumber(L, 6);
    float destY = (float)luaL_checknumber(L, 7);
    float destW = (float)luaL_checknumber(L, 8);
    float destH = (float)luaL_checknumber(L, 9);
    float originX = (float)luaL_checknumber(L, 10);
    float originY = (float)luaL_checknumber(L, 11);
    float rotation = (float)luaL_checknumber(L, 12);
    DrawTexturePro(texture, { srcX, srcY, srcW, srcH }, { destX, destY, destW, destH }, { originX, originY }, rotation, currentColor);

    return 0;
}

static int getHeightTexture(lua_State* L)
{
    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    lua_pushinteger(L, texture.height);

    return 1;
}

static int getWidthTexture(lua_State* L)
{
    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    lua_pushinteger(L, texture.width);

    return 1;
}

static int isReadyTexture(lua_State* L)
{
    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    bool result = IsTextureReady(texture);
    lua_pushboolean(L, result);

    return 1;
}

static int setFilterTexture(lua_State* L)
{
    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    const char* filter = luaL_checkstring(L, 2);

    if (TextIsEqual(filter, "point")) {
        SetTextureFilter(texture, TEXTURE_FILTER_POINT);
    } else if (TextIsEqual(filter, "bilinear")) {
        SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    } else {
        return luaL_error(L, "Unknown filter: %s", filter);
    }

    return 0;
}

static int setWrapTexture(lua_State* L)
{
    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    const char* wrap = luaL_checkstring(L, 2);

    if (TextIsEqual(wrap, "clamp")) {
        SetTextureWrap(texture, TEXTURE_WRAP_CLAMP);
    } else if (TextIsEqual(wrap, "repeat")) {
        SetTextureWrap(texture, TEXTURE_WRAP_REPEAT);
    } else {
        return luaL_error(L, "Unknown wrap: %s", wrap);
    }

    return 0;
}

static const luaL_Reg textureMethods[] = {
    { "__gc", gcTexture },
    { "__tostring", tostringTexture },
    { "draw", drawTexture },
    { "drawPro", drawProTexture },
    { "isReady", isReadyTexture },
    { "setFilter", setFilterTexture },
    { "setWrap", setWrapTexture },
    { NULL, NULL }
};

static int gcCanvas(lua_State* L)
{
    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    UnloadRenderTexture(canvas);

    return 0;
}

static int tostringCanvas(lua_State* L)
{
    lua_pushstring(L, "Canvas");

    return 1;
}

static int beginDrawingCanvas(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    BeginTextureMode(canvas);

    return 0;
}

static int drawCanvas(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    DrawTexture(canvas.texture, x, y, currentColor);

    return 0;
}

static int drawProCanvas(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    float srcX = (float)luaL_checknumber(L, 2);
    float srcY = (float)luaL_checknumber(L, 3);
    float srcW = (float)luaL_checknumber(L, 4);
    float srcH = (float)luaL_checknumber(L, 5);
    float destX = (float)luaL_checknumber(L, 6);
    float destY = (float)luaL_checknumber(L, 7);
    float destW = (float)luaL_checknumber(L, 8);
    float destH = (float)luaL_checknumber(L, 9);
    float originX = (float)luaL_checknumber(L, 10);
    float originY = (float)luaL_checknumber(L, 11);
    float rotation = (float)luaL_checknumber(L, 12);
    DrawTexturePro(canvas.texture, { srcX, srcY, srcW, srcH }, { destX, destY, destW, destH }, { originX, originY }, rotation, currentColor);

    return 0;
}

static int endDrawingCanvas(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    EndTextureMode();

    return 0;
}

static int getHeightCanvas(lua_State* L)
{
    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    lua_pushinteger(L, canvas.texture.height);

    return 1;
}

static int getWidthCanvas(lua_State* L)
{
    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    lua_pushinteger(L, canvas.texture.width);

    return 1;
}

static int isReadyCanvas(lua_State* L)
{
    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    bool result = IsRenderTextureReady(canvas);
    lua_pushboolean(L, result);

    return 1;
}

static int setFilterCanvas(lua_State* L)
{
    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    const char* filter = luaL_checkstring(L, 2);

    if (TextIsEqual(filter, "point")) {
        SetTextureFilter(canvas.texture, TEXTURE_FILTER_POINT);
    } else if (TextIsEqual(filter, "bilinear")) {
        SetTextureFilter(canvas.texture, TEXTURE_FILTER_BILINEAR);
    } else {
        return luaL_error(L, "Unknown filter: %s", filter);
    }

    return 0;
}

static int setWrapCanvas(lua_State* L)
{
    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    const char* wrap = luaL_checkstring(L, 2);

    if (TextIsEqual(wrap, "clamp")) {
        SetTextureWrap(canvas.texture, TEXTURE_WRAP_CLAMP);
    } else if (TextIsEqual(wrap, "repeat")) {
        SetTextureWrap(canvas.texture, TEXTURE_WRAP_REPEAT);
    } else {
        return luaL_error(L, "Unknown wrap: %s", wrap);
    }

    return 0;
}

static const luaL_Reg canvasMethods[] = {
    { "__gc", gcCanvas },
    { "__tostring", tostringCanvas },
    { "beginDrawing", beginDrawingCanvas },
    { "draw", drawCanvas },
    { "drawPro", drawProCanvas },
    { "endDrawing", endDrawingCanvas },
    { "isReady", isReadyCanvas },
    { "setFilter", setFilterCanvas },
    { "setWrap", setWrapCanvas },
    { NULL, NULL }
};

static int gcFont(lua_State* L)
{
    Font font = *(Font*)luaL_checkudata(L, 1, "Font");
    UnloadFont(font);

    return 0;
}

static int tostringFont(lua_State* L)
{
    lua_pushstring(L, "Font");

    return 1;
}

static int isReadyFont(lua_State* L)
{
    Font font = *(Font*)luaL_checkudata(L, 1, "Font");
    bool result = IsFontReady(font);
    lua_pushboolean(L, result);

    return 1;
}

static int measureFont(lua_State* L)
{
    Font font = *(Font*)luaL_checkudata(L, 1, "Font");
    const char* text = luaL_checkstring(L, 2);
    Vector2 result = MeasureTextEx(font, text, font.baseSize, 0);
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static const luaL_Reg fontMethods[] = {
    { "__gc", gcFont },
    { "__tostring", tostringFont },
    { "isReady", isReadyFont },
    { "measure", measureFont },
    { NULL, NULL }
};

static int gcShader(lua_State* L)
{
    Shader shader = *(Shader*)luaL_checkudata(L, 1, "Shader");
    UnloadShader(shader);

    return 0;
}

static int tostringShader(lua_State* L)
{
    lua_pushstring(L, "Shader");

    return 1;
}

static int beginDrawingShader(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Shader shader = *(Shader*)luaL_checkudata(L, 1, "Shader");
    BeginShaderMode(shader);

    return 0;
}

static int endDrawingShader(lua_State* L)
{
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Shader shader = *(Shader*)luaL_checkudata(L, 1, "Shader");
    EndShaderMode();

    return 0;
}

static int getAttributeShader(lua_State* L)
{
    Shader shader = *(Shader*)luaL_checkudata(L, 1, "Shader");
    const char* attributeName = luaL_checkstring(L, 2);
    int result = GetShaderLocationAttrib(shader, attributeName);
    lua_pushinteger(L, result);

    return 1;
}

static int getUniformShader(lua_State* L)
{
    Shader shader = *(Shader*)luaL_checkudata(L, 1, "Shader");
    const char* uniformName = luaL_checkstring(L, 2);
    int result = GetShaderLocation(shader, uniformName);
    lua_pushinteger(L, result);

    return 1;
}

static int isReadyShader(lua_State* L)
{
    Shader shader = *(Shader*)luaL_checkudata(L, 1, "Shader");
    bool result = IsShaderReady(shader);
    lua_pushboolean(L, result);

    return 1;
}

static const luaL_Reg shaderMethods[] = {
    { "__gc", gcShader },
    { "__tostring", tostringShader },
    { "beginDrawing", beginDrawingShader },
    { "endDrawing", endDrawingShader },
    { "getAttribute", getAttributeShader },
    { "getUniform", getUniformShader },
    { "isReady", isReadyShader },
    { NULL, NULL }
};

int luaopen_graphics(lua_State* L)
{
    luaL_newmetatable(L, "Texture");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, textureMethods, 0);
    lua_pop(L, 1);

    luaL_newmetatable(L, "Canvas");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, canvasMethods, 0);
    lua_pop(L, 1);

    luaL_newmetatable(L, "Font");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, fontMethods, 0);
    lua_pop(L, 1);

    luaL_newmetatable(L, "Shader");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, shaderMethods, 0);
    lua_pop(L, 1);

    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "graphics");

    lua_pop(L, 1);

    return 1;
}
