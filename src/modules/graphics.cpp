#include "api.h"

#include <string.h>

#include "../util.h"

static bool safe = false;
static bool canvasSafe = false;
static Color currentColor = WHITE;

static int beginBlendMode(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    const char* mode = luaL_checkstring(L, 1);

    if (TextIsEqual(mode, "alpha")) {
        BeginBlendMode(BLEND_ALPHA);
    } else if (TextIsEqual(mode, "additive")) {
        BeginBlendMode(BLEND_ADDITIVE);
    } else if (TextIsEqual(mode, "multiplied")) {
        BeginBlendMode(BLEND_MULTIPLIED);
    } else if (TextIsEqual(mode, "addColors")) {
        BeginBlendMode(BLEND_ADD_COLORS);
    } else if (TextIsEqual(mode, "subtractColors")) {
        BeginBlendMode(BLEND_SUBTRACT_COLORS);
    } else if (TextIsEqual(mode, "alphaPremultiplied")) {
        BeginBlendMode(BLEND_ALPHA_PREMULTIPLY);
    } else {
        return luaL_error(L, "Unknown blend mode: %s", mode);
    }

    return 0;
}

static int beginDrawing(lua_State* L)
{
    BeginDrawing();
    safe = true;

    return 0;
}

static int beginScissorMode(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int width = (int)luaL_checkinteger(L, 3);
    int height = (int)luaL_checkinteger(L, 4);
    BeginScissorMode(x, y, width, height);

    return 0;
}

static int checkCollisionPointRec(lua_State* L)
{
    int pointX = (int)luaL_checkinteger(L, 1);
    int pointY = (int)luaL_checkinteger(L, 2);
    int recX = (int)luaL_checkinteger(L, 3);
    int recY = (int)luaL_checkinteger(L, 4);
    int recWidth = (int)luaL_checkinteger(L, 5);
    int recHeight = (int)luaL_checkinteger(L, 6);
    bool result = CheckCollisionPointRec({ (float)pointX, (float)pointY }, { (float)recX, (float)recY, (float)recWidth, (float)recHeight });
    lua_pushboolean(L, result);

    return 1;
}

static int checkCollisionRecs(lua_State* L)
{
    int x1 = (int)luaL_checkinteger(L, 1);
    int y1 = (int)luaL_checkinteger(L, 2);
    int w1 = (int)luaL_checkinteger(L, 3);
    int h1 = (int)luaL_checkinteger(L, 4);
    int x2 = (int)luaL_checkinteger(L, 5);
    int y2 = (int)luaL_checkinteger(L, 6);
    int w2 = (int)luaL_checkinteger(L, 7);
    int h2 = (int)luaL_checkinteger(L, 8);
    bool result = CheckCollisionRecs({ (float)x1, (float)y1, (float)w1, (float)h1 }, { (float)x2, (float)y2, (float)w2, (float)h2 });
    lua_pushboolean(L, result);

    return 1;
}

static int circle(lua_State* L)
{
    if (!safe && !canvasSafe) {
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
    if (!safe && !canvasSafe) {
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
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    unsigned char r = (unsigned char)luaL_optinteger(L, 1, 0);
    unsigned char g = (unsigned char)luaL_optinteger(L, 2, 0);
    unsigned char b = (unsigned char)luaL_optinteger(L, 3, 0);
    unsigned char a = (unsigned char)luaL_optinteger(L, 4, 255);
    ClearBackground({ r, g, b, a });

    return 0;
}

static int ellipse(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    float radiusX = (float)luaL_checknumber(L, 3);
    float radiusY = (float)luaL_checknumber(L, 4);
    DrawEllipse(x, y, radiusX, radiusY, currentColor);

    return 0;
}

static int ellipseLines(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    float radiusX = (float)luaL_checknumber(L, 3);
    float radiusY = (float)luaL_checknumber(L, 4);
    DrawEllipseLines(x, y, radiusX, radiusY, currentColor);

    return 0;
}

static int endBlendMode(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    EndBlendMode();

    return 0;
}

static int endDrawing(lua_State* L)
{
    EndDrawing();
    safe = false;

    return 0;
}

static int endScissorMode(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    EndScissorMode();

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

static int hsvToRgb(lua_State* L)
{
    float hue = (float)luaL_checknumber(L, 1);
    float saturation = (float)luaL_checknumber(L, 2);
    float value = (float)luaL_checknumber(L, 3);

    if (hue < 0.0f || hue > 360.0f) {
        return luaL_error(L, "Hue must be between 0 and 360");
    }

    if (saturation < 0.0f || saturation > 1.0f) {
        return luaL_error(L, "Saturation must be between 0 and 1");
    }

    if (value < 0.0f || value > 1.0f) {
        return luaL_error(L, "Value must be between 0 and 1");
    }

    Color result = ColorFromHSV(hue, saturation, value);
    lua_pushinteger(L, result.r);
    lua_pushinteger(L, result.g);
    lua_pushinteger(L, result.b);

    return 3;
}

static int line(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x1 = (int)luaL_checkinteger(L, 1);
    int y1 = (int)luaL_checkinteger(L, 2);
    int x2 = (int)luaL_checkinteger(L, 3);
    int y2 = (int)luaL_checkinteger(L, 4);
    float thickness = (float)luaL_optnumber(L, 5, 1);
    DrawLineEx({ (float)x1, (float)y1 }, { (float)x2, (float)y2 }, thickness, currentColor);

    return 0;
}

static int lineBezier(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x1 = (int)luaL_checkinteger(L, 1);
    int y1 = (int)luaL_checkinteger(L, 2);
    int x2 = (int)luaL_checkinteger(L, 3);
    int y2 = (int)luaL_checkinteger(L, 4);
    float thickness = (float)luaL_optnumber(L, 5, 1);
    DrawLineBezier({ (float)x1, (float)y1 }, { (float)x2, (float)y2 }, thickness, currentColor);

    return 0;
}

static int loadCamera(lua_State* L)
{
    float x = (float)luaL_checknumber(L, 1);
    float y = (float)luaL_checknumber(L, 2);
    float offsetX = (float)luaL_optnumber(L, 3, 0);
    float offsetY = (float)luaL_optnumber(L, 4, 0);
    float rotation = (float)luaL_optnumber(L, 5, 0);
    float zoom = (float)luaL_optnumber(L, 6, 1);

    Camera2D result;
    result.target = { x, y };
    result.offset = { offsetX, offsetY };
    result.rotation = rotation;
    result.zoom = zoom;

    void* ud = lua_newuserdata(L, sizeof(Camera2D));
    memcpy(ud, &result, sizeof(Camera2D));
    luaL_setmetatable(L, "Camera");

    return 1;
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

static int loadFontSDF(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    if (!FileExists(filename)) {
        return luaL_error(L, "File %s does not exist.", filename);
    }

    int fileSize = 0;
    unsigned char* fileData = LoadFileData(filename, &fileSize);

    Font fontSDF = { 0 };
    fontSDF.baseSize = 16;
    fontSDF.glyphCount = 95;
    fontSDF.glyphs = LoadFontData(fileData, fileSize, 16, 0, 0, FONT_SDF);
    Image atlas = GenImageFontAtlas(fontSDF.glyphs, &fontSDF.recs, 95, 16, 0, 1);
    fontSDF.texture = LoadTextureFromImage(atlas);
    SetTextureFilter(fontSDF.texture, TEXTURE_FILTER_BILINEAR);

    UnloadImage(atlas);
    UnloadFileData(fileData);

    void* ud = lua_newuserdata(L, sizeof(Font));
    memcpy(ud, &fontSDF, sizeof(Font));
    luaL_setmetatable(L, "Font");

    return 1;
}

static int loadLogos(lua_State* L)
{
    Texture iconTexture = LoadTextureFromImage(icon);

    void* ud1 = lua_newuserdata(L, sizeof(Texture));
    memcpy(ud1, &iconTexture, sizeof(Texture));
    luaL_setmetatable(L, "Texture");

    Texture githubTexture = LoadTextureFromImage(githubLogo);

    void* ud2 = lua_newuserdata(L, sizeof(Texture));
    memcpy(ud2, &githubTexture, sizeof(Texture));
    luaL_setmetatable(L, "Texture");

    Texture loveTexture = LoadTextureFromImage(loveLogo);

    void* ud3 = lua_newuserdata(L, sizeof(Texture));
    memcpy(ud3, &loveTexture, sizeof(Texture));
    luaL_setmetatable(L, "Texture");

    Texture luaTexture = LoadTextureFromImage(luaLogo);

    void* ud4 = lua_newuserdata(L, sizeof(Texture));
    memcpy(ud4, &luaTexture, sizeof(Texture));
    luaL_setmetatable(L, "Texture");

    Texture raylibTexture = LoadTextureFromImage(raylibLogo);

    void* ud5 = lua_newuserdata(L, sizeof(Texture));
    memcpy(ud5, &raylibTexture, sizeof(Texture));
    luaL_setmetatable(L, "Texture");

    return 5;
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

static int loadSvg(lua_State* L)
{
    const char* filename = luaL_checkstring(L, 1);

    if (!FileExists(filename)) {
        return luaL_error(L, "File %s does not exist.", filename);
    }

    int width = (int)luaL_checkinteger(L, 2);
    int height = (int)luaL_checkinteger(L, 3);
    Image image = LoadImageSvg(filename, width, height);
    Texture result = LoadTextureFromImage(image);
    UnloadImage(image);

    void* ud = lua_newuserdata(L, sizeof(Texture));
    memcpy(ud, &result, sizeof(Texture));
    luaL_setmetatable(L, "Texture");

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

static int measure(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    Vector2 result = MeasureTextEx(defaultFont, text, (float)defaultFont.baseSize, 0);
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int measureBig(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    Vector2 result = MeasureTextEx(defaultFontBig, text, (float)defaultFontBig.baseSize, 0);
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int measureMedium(lua_State* L)
{
    const char* text = luaL_checkstring(L, 1);
    Vector2 result = MeasureTextEx(defaultFontMedium, text, (float)defaultFontMedium.baseSize, 0);
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int pixel(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    DrawPixel(x, y, currentColor);

    return 0;
}

static int polygon(lua_State* L)
{
    if (!safe && !canvasSafe) {
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
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int sides = (int)luaL_checkinteger(L, 3);
    float radius = (float)luaL_checknumber(L, 4);
    float rotation = (float)luaL_checknumber(L, 5);
    float thickness = (float)luaL_optnumber(L, 6, 1);
    DrawPolyLinesEx({ (float)x, (float)y }, sides, radius, rotation, thickness, currentColor);

    return 0;
}

static int rectangle(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int width = (int)luaL_checkinteger(L, 3);
    int height = (int)luaL_checkinteger(L, 4);
    float rotation = (float)luaL_optnumber(L, 5, 0);
    int ox = (int)luaL_optinteger(L, 6, 0);
    int oy = (int)luaL_optinteger(L, 7, 0);
    DrawRectanglePro({ (float)x, (float)y, (float)width, (float)height }, { (float)ox, (float)oy }, rotation, currentColor);

    return 0;
}

static int rectangleLines(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int width = (int)luaL_checkinteger(L, 3);
    int height = (int)luaL_checkinteger(L, 4);
    float thickness = (float)luaL_optnumber(L, 5, 1);
    DrawRectangleLinesEx({ (float)x, (float)y, (float)width, (float)height }, thickness, currentColor);

    return 0;
}

static int rectangleRounded(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int width = (int)luaL_checkinteger(L, 3);
    int height = (int)luaL_checkinteger(L, 4);
    float roundness = (float)luaL_checknumber(L, 5);
    int segments = (int)luaL_checkinteger(L, 6);
    DrawRectangleRounded({ (float)x, (float)y, (float)width, (float)height }, roundness, segments, currentColor);

    return 0;
}

static int rectangleRoundedLines(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    int width = (int)luaL_checkinteger(L, 3);
    int height = (int)luaL_checkinteger(L, 4);
    float roundness = (float)luaL_checknumber(L, 5);
    int segments = (int)luaL_checkinteger(L, 6);
    float thickness = (float)luaL_optnumber(L, 7, 1);
    DrawRectangleRoundedLines({ (float)x, (float)y, (float)width, (float)height }, roundness, segments, thickness, currentColor);

    return 0;
}

static int rgbToHsv(lua_State* L)
{
    unsigned char r = (unsigned char)luaL_checkinteger(L, 1);
    unsigned char g = (unsigned char)luaL_checkinteger(L, 2);
    unsigned char b = (unsigned char)luaL_checkinteger(L, 3);
    Color color = { r, g, b, 255 };
    Vector3 result = ColorToHSV(color);
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);
    lua_pushnumber(L, result.z);

    return 3;
}

static int ring(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    float innerRadius = (float)luaL_checknumber(L, 3);
    float outerRadius = (float)luaL_checknumber(L, 4);
    float startAngle = (float)luaL_checknumber(L, 5);
    float endAngle = (float)luaL_checknumber(L, 6);
    int segments = (int)luaL_checkinteger(L, 7);
    DrawRing({ (float)x, (float)y }, innerRadius, outerRadius, startAngle, endAngle, segments, currentColor);

    return 0;
}

static int ringLines(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    float innerRadius = (float)luaL_checknumber(L, 3);
    float outerRadius = (float)luaL_checknumber(L, 4);
    float startAngle = (float)luaL_checknumber(L, 5);
    float endAngle = (float)luaL_checknumber(L, 6);
    int segments = (int)luaL_checkinteger(L, 7);
    DrawRingLines({ (float)x, (float)y }, innerRadius, outerRadius, startAngle, endAngle, segments, currentColor);

    return 0;
}

static int sector(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    float radius = (float)luaL_checknumber(L, 3);
    float startAngle = (float)luaL_checknumber(L, 4);
    float endAngle = (float)luaL_checknumber(L, 5);
    int segments = (int)luaL_checkinteger(L, 6);
    DrawCircleSector({ (float)x, (float)y }, radius, startAngle, endAngle, segments, currentColor);

    return 0;
}

static int sectorLines(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    float radius = (float)luaL_checknumber(L, 3);
    float startAngle = (float)luaL_checknumber(L, 4);
    float endAngle = (float)luaL_checknumber(L, 5);
    int segments = (int)luaL_checkinteger(L, 6);
    DrawCircleSectorLines({ (float)x, (float)y }, radius, startAngle, endAngle, segments, currentColor);

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

static int setLineSpacing(lua_State* L)
{
    int spacing = (int)luaL_checkinteger(L, 1);
    SetTextLineSpacing(spacing);

    return 0;
}

static int text(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    const char* text = luaL_checkstring(L, 1);
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    DrawTextEx(defaultFont, text, { (float)x, (float)y }, (float)defaultFont.baseSize, 0, currentColor);

    return 0;
}

static int textBig(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    const char* text = luaL_checkstring(L, 1);
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    DrawTextEx(defaultFontBig, text, { (float)x, (float)y }, (float)defaultFontBig.baseSize, 0, currentColor);

    return 0;
}

static int textMedium(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    const char* text = luaL_checkstring(L, 1);
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    DrawTextEx(defaultFontMedium, text, { (float)x, (float)y }, (float)defaultFontMedium.baseSize, 0, currentColor);

    return 0;
}

static int triangle(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x1 = (int)luaL_checkinteger(L, 1);
    int y1 = (int)luaL_checkinteger(L, 2);
    int x2 = (int)luaL_checkinteger(L, 3);
    int y2 = (int)luaL_checkinteger(L, 4);
    int x3 = (int)luaL_checkinteger(L, 5);
    int y3 = (int)luaL_checkinteger(L, 6);
    DrawTriangle({ (float)x1, (float)y1 }, { (float)x2, (float)y2 }, { (float)x3, (float)y3 }, currentColor);

    return 0;
}

static int triangleLines(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    int x1 = (int)luaL_checkinteger(L, 1);
    int y1 = (int)luaL_checkinteger(L, 2);
    int x2 = (int)luaL_checkinteger(L, 3);
    int y2 = (int)luaL_checkinteger(L, 4);
    int x3 = (int)luaL_checkinteger(L, 5);
    int y3 = (int)luaL_checkinteger(L, 6);
    DrawTriangleLines({ (float)x1, (float)y1 }, { (float)x2, (float)y2 }, { (float)x3, (float)y3 }, currentColor);

    return 0;
}

static int wrappedText(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    const char* text = luaL_checkstring(L, 1);
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    int w = (int)luaL_checkinteger(L, 4);
    int h = (int)luaL_checkinteger(L, 5);
    DrawTextBoxedSelectable(defaultFont, text, { (float)x, (float)y, (float)w, (float)h }, (float)defaultFont.baseSize, 0, true, currentColor, 0, 0, WHITE, WHITE);

    return 0;
}

static const luaL_Reg functions[] = {
    { "beginBlendMode", beginBlendMode },
    { "beginDrawing", beginDrawing },
    { "beginScissorMode", beginScissorMode },
    { "checkCollisionPointRec", checkCollisionPointRec },
    { "checkCollisionRecs", checkCollisionRecs },
    { "circle", circle },
    { "circleLines", circleLines },
    { "clear", clear },
    { "ellipse", ellipse },
    { "ellipseLines", ellipseLines },
    { "endBlendMode", endBlendMode },
    { "endDrawing", endDrawing },
    { "endScissorMode", endScissorMode },
    { "getColor", getColor },
    { "getDelta", getDelta },
    { "getFPS", getFPS },
    { "hsvToRgb", hsvToRgb },
    { "line", line },
    { "lineBezier", lineBezier },
    { "loadCamera", loadCamera },
    { "loadCanvas", loadCanvas },
    { "loadFont", loadFont },
    { "loadFontSDF", loadFontSDF },
    { "loadLogos", loadLogos },
    { "loadShader", loadShader },
    { "loadSvg", loadSvg },
    { "loadTexture", loadTexture },
    { "measure", measure },
    { "measureBig", measureBig },
    { "measureMedium", measureMedium },
    { "pixel", pixel },
    { "polygon", polygon },
    { "polygonLines", polygonLines },
    { "rectangle", rectangle },
    { "rectangleLines", rectangleLines },
    { "rectangleRounded", rectangleRounded },
    { "rectangleRoundedLines", rectangleRoundedLines },
    { "rgbToHsv", rgbToHsv },
    { "ring", ring },
    { "ringLines", ringLines },
    { "sector", sector },
    { "sectorLines", sectorLines },
    { "setColor", setColor },
    { "setLineSpacing", setLineSpacing },
    { "text", text },
    { "textBig", textBig },
    { "textMedium", textMedium },
    { "triangle", triangle },
    { "triangleLines", triangleLines },
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
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    float rotation = (float)luaL_optnumber(L, 4, 0);
    float scaleX = (float)luaL_optnumber(L, 5, 1);
    float scaleY = (float)luaL_optnumber(L, 6, 1);
    float originX = (float)luaL_optnumber(L, 7, 0);
    float originY = (float)luaL_optnumber(L, 8, 0);

    Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };

    if (scaleX < 0) {
        source.width = -source.width;
    }

    if (scaleY < 0) {
        source.height = -source.height;
    }

    float absScaleX = scaleX < 0 ? -scaleX : scaleX;
    float absScaleY = scaleY < 0 ? -scaleY : scaleY;

    DrawTexturePro(texture, source, { (float)x, (float)y, (float)texture.width * absScaleX, (float)texture.height * absScaleY }, { originX, originY }, rotation, currentColor);

    return 0;
}

static int drawRecTexture(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Texture texture = *(Texture*)luaL_checkudata(L, 1, "Texture");
    int recX = (int)luaL_checkinteger(L, 2);
    int recY = (int)luaL_checkinteger(L, 3);
    int recWidth = (int)luaL_checkinteger(L, 4);
    int recHeight = (int)luaL_checkinteger(L, 5);
    int x = (int)luaL_checkinteger(L, 6);
    int y = (int)luaL_checkinteger(L, 7);
    float rotation = (float)luaL_optnumber(L, 8, 0);
    float scaleX = (float)luaL_optnumber(L, 9, 1);
    float scaleY = (float)luaL_optnumber(L, 10, 1);
    float originX = (float)luaL_optnumber(L, 11, 0);
    float originY = (float)luaL_optnumber(L, 12, 0);

    Rectangle source = { (float)recX, (float)recY, (float)recWidth, (float)recHeight };

    if (scaleX < 0) {
        source.width = -source.width;
    }

    if (scaleY < 0) {
        source.height = -source.height;
    }

    float absScaleX = scaleX < 0 ? -scaleX : scaleX;
    float absScaleY = scaleY < 0 ? -scaleY : scaleY;

    DrawTexturePro(texture, source, { (float)x, (float)y, (float)recWidth * absScaleX, (float)recHeight * absScaleY }, { originX, originY }, rotation, currentColor);

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
    { "drawRec", drawRecTexture },
    { "getHeight", getHeightTexture },
    { "getWidth", getWidthTexture },
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
    if (canvasSafe) {
        return luaL_error(L, "Can't draw on a canvas while in another canvas.");
    }

    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    BeginTextureMode(canvas);
    canvasSafe = true;

    return 0;
}

static int drawCanvas(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    float rotation = (float)luaL_optnumber(L, 4, 0);
    float scaleX = (float)luaL_optnumber(L, 5, 1);
    float scaleY = (float)luaL_optnumber(L, 6, -1);
    float originX = (float)luaL_optnumber(L, 7, 0);
    float originY = (float)luaL_optnumber(L, 8, 0);

    Rectangle source = { 0, 0, (float)canvas.texture.width, (float)canvas.texture.height };

    if (scaleX < 0) {
        source.width = -source.width;
    }

    if (scaleY < 0) {
        source.height = -source.height;
    }

    float absScaleX = scaleX < 0 ? -scaleX : scaleX;
    float absScaleY = scaleY < 0 ? -scaleY : scaleY;

    DrawTexturePro(canvas.texture, source, { (float)x, (float)y, (float)canvas.texture.width * absScaleX, (float)canvas.texture.height * absScaleY }, { originX, originY }, rotation, currentColor);

    return 0;
}

static int endDrawingCanvas(lua_State* L)
{
    RenderTexture canvas = *(RenderTexture*)luaL_checkudata(L, 1, "Canvas");
    EndTextureMode();
    canvasSafe = false;

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
    { "endDrawing", endDrawingCanvas },
    { "getHeight", getHeightCanvas },
    { "getWidth", getWidthCanvas },
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

static int draw(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Font font = *(Font*)luaL_checkudata(L, 1, "Font");
    const char* text = luaL_checkstring(L, 2);
    int x = (int)luaL_checkinteger(L, 3);
    int y = (int)luaL_checkinteger(L, 4);
    float rotation = (float)luaL_optnumber(L, 5, 0);
    int ox = (int)luaL_optinteger(L, 6, 0);
    int oy = (int)luaL_optinteger(L, 7, 0);
    DrawTextPro(font, text, { (float)x, (float)y }, { (float)ox, (float)oy }, rotation, (float)font.baseSize, 0, currentColor);

    return 0;
}

static int drawSDF(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Font font = *(Font*)luaL_checkudata(L, 1, "Font");
    const char* text = luaL_checkstring(L, 2);
    int x = (int)luaL_checkinteger(L, 3);
    int y = (int)luaL_checkinteger(L, 4);
    float size = (float)luaL_checknumber(L, 5);
    float rotation = (float)luaL_optnumber(L, 6, 0);
    int ox = (int)luaL_optinteger(L, 7, 0);
    int oy = (int)luaL_optinteger(L, 8, 0);

    BeginShaderMode(sdfShader);
    DrawTextPro(font, text, { (float)x, (float)y }, { (float)ox, (float)oy }, rotation, size, 0, currentColor);
    EndShaderMode();

    return 0;
}

static int drawWrapped(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Font font = *(Font*)luaL_checkudata(L, 1, "Font");
    const char* text = luaL_checkstring(L, 2);
    int x = (int)luaL_checkinteger(L, 3);
    int y = (int)luaL_checkinteger(L, 4);
    int w = (int)luaL_checkinteger(L, 5);
    int h = (int)luaL_checkinteger(L, 6);
    DrawTextBoxedSelectable(font, text, { (float)x, (float)y, (float)w, (float)h }, (float)font.baseSize, 0, true, currentColor, 0, 0, WHITE, WHITE);

    return 0;
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
    Vector2 result = MeasureTextEx(font, text, (float)font.baseSize, 0);
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static const luaL_Reg fontMethods[] = {
    { "__gc", gcFont },
    { "__tostring", tostringFont },
    { "draw", draw },
    { "drawSDF", drawSDF },
    { "drawWrapped", drawWrapped },
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
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Shader shader = *(Shader*)luaL_checkudata(L, 1, "Shader");
    BeginShaderMode(shader);

    return 0;
}

static int endDrawingShader(lua_State* L)
{
    if (!safe && !canvasSafe) {
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

static int setValueShader(lua_State* L)
{
    Shader shader = *(Shader*)luaL_checkudata(L, 1, "Shader");
    int locIndex = (int)luaL_checkinteger(L, 2);

    int type = lua_type(L, 3);

    if (type == LUA_TNUMBER) {
        float value = (float)luaL_checknumber(L, 3);
        SetShaderValue(shader, locIndex, &value, SHADER_UNIFORM_FLOAT);
    } else if (type = LUA_TUSERDATA) {
        Texture value = *(Texture*)luaL_checkudata(L, 3, "Texture");
        SetShaderValueTexture(shader, locIndex, value);
    } else if (type == LUA_TTABLE) {
        int tableLength = (int)lua_objlen(L, 3);

        if (tableLength == 2 || tableLength == 3 || tableLength == 4) {
            float values[4];

            for (int i = 0; i < tableLength; ++i) {
                lua_rawgeti(L, 3, i + 1);
                values[i] = (float)luaL_checknumber(L, -1);
                lua_pop(L, 1);
            }

            int uniformType;

            if (tableLength == 2)
                uniformType = SHADER_UNIFORM_VEC2;
            else if (tableLength == 3)
                uniformType = SHADER_UNIFORM_VEC3;
            else
                uniformType = SHADER_UNIFORM_VEC4;

            SetShaderValue(shader, locIndex, &values, uniformType);
        } else {
            return luaL_error(L, "Invalid number of elements in table for shader value.");
        }
    } else {
        return luaL_error(L, "Invalid type for shader value.");
    }

    return 0;
}

static const luaL_Reg shaderMethods[] = {
    { "__gc", gcShader },
    { "__tostring", tostringShader },
    { "beginDrawing", beginDrawingShader },
    { "endDrawing", endDrawingShader },
    { "getAttribute", getAttributeShader },
    { "getUniform", getUniformShader },
    { "isReady", isReadyShader },
    { "setValue", setValueShader },
    { NULL, NULL }
};

static int tostringCamera(lua_State* L)
{
    lua_pushstring(L, "Camera");

    return 1;
}

static int beginDrawingCamera(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Camera2D camera = *(Camera2D*)luaL_checkudata(L, 1, "Camera");
    BeginMode2D(camera);

    return 0;
}

static int endDrawingCamera(lua_State* L)
{
    if (!safe && !canvasSafe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    EndMode2D();

    return 0;
}

static int getPositionCamera(lua_State* L)
{
    Camera2D camera = *(Camera2D*)luaL_checkudata(L, 1, "Camera");
    Vector2 result = camera.target;
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int getRotationCamera(lua_State* L)
{
    Camera2D camera = *(Camera2D*)luaL_checkudata(L, 1, "Camera");
    lua_pushnumber(L, camera.rotation);

    return 1;
}

static int getZoomCamera(lua_State* L)
{
    Camera2D camera = *(Camera2D*)luaL_checkudata(L, 1, "Camera");
    lua_pushnumber(L, camera.zoom);

    return 1;
}

static int moveCamera(lua_State* L)
{
    Camera2D* camera = (Camera2D*)luaL_checkudata(L, 1, "Camera");
    int x = (int)luaL_checkinteger(L, 2);
    int y = (int)luaL_checkinteger(L, 3);
    camera->target = { camera->target.x + x, camera->target.y + y };

    return 0;
}

static int rotateCamera(lua_State* L)
{
    Camera2D* camera = (Camera2D*)luaL_checkudata(L, 1, "Camera");
    float rotation = (float)luaL_checknumber(L, 2);
    camera->rotation += rotation;

    return 0;
}

static int screenToWorldCamera(lua_State* L)
{
    Camera2D camera = *(Camera2D*)luaL_checkudata(L, 1, "Camera");
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);
    Vector2 result = GetScreenToWorld2D({ x, y }, camera);
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int setPositionCamera(lua_State* L)
{
    Camera2D* camera = (Camera2D*)luaL_checkudata(L, 1, "Camera");
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);
    camera->target = { x, y };

    return 0;
}

static int setRotationCamera(lua_State* L)
{
    Camera2D* camera = (Camera2D*)luaL_checkudata(L, 1, "Camera");
    float rotation = (float)luaL_checknumber(L, 2);
    camera->rotation = rotation;

    return 0;
}

static int setZoomCamera(lua_State* L)
{
    Camera2D* camera = (Camera2D*)luaL_checkudata(L, 1, "Camera");
    float zoom = (float)luaL_checknumber(L, 2);
    camera->zoom = zoom;

    return 0;
}

static int worldToScreenCamera(lua_State* L)
{
    Camera2D camera = *(Camera2D*)luaL_checkudata(L, 1, "Camera");
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);
    Vector2 result = GetWorldToScreen2D({ x, y }, camera);
    lua_pushnumber(L, result.x);
    lua_pushnumber(L, result.y);

    return 2;
}

static int zoomCamera(lua_State* L)
{
    Camera2D* camera = (Camera2D*)luaL_checkudata(L, 1, "Camera");
    float zoom = (float)luaL_checknumber(L, 2);
    camera->zoom *= zoom;

    return 0;
}

static const luaL_Reg cameraMethods[] = {
    { "__tostring", tostringCamera },
    { "beginDrawing", beginDrawingCamera },
    { "endDrawing", endDrawingCamera },
    { "getPosition", getPositionCamera },
    { "getRotation", getRotationCamera },
    { "getZoom", getZoomCamera },
    { "move", moveCamera },
    { "rotate", rotateCamera },
    { "screenToWorld", screenToWorldCamera },
    { "setPosition", setPositionCamera },
    { "setRotation", setRotationCamera },
    { "setZoom", setZoomCamera },
    { "worldToScreen", worldToScreenCamera },
    { "zoom", zoomCamera },
    { NULL, NULL }
};

int luaopen_pesto_graphics(lua_State* L)
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

    luaL_newmetatable(L, "Camera");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, cameraMethods, 0);
    lua_pop(L, 1);

    lua_getglobal(L, "pesto");

    lua_newtable(L);
    luaL_setfuncs(L, functions, 0);
    lua_setfield(L, -2, "graphics");

    lua_pop(L, 1);

    return 1;
}
