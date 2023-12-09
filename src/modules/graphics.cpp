#include "api.h"

#include <string.h>

#include "../util.h"

static bool safe = false;
static Color currentColor = WHITE;

static int beginBlendMode(lua_State* L)
{
    if (!safe) {
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
    if (!safe) {
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

static int ellipse(lua_State* L)
{
    if (!safe) {
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
    if (!safe) {
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
    if (!safe) {
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
    if (!safe) {
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

static int loadCamera(lua_State* L)
{
    int x = (int)luaL_checkinteger(L, 1);
    int y = (int)luaL_checkinteger(L, 2);
    float rotation = (float)luaL_optnumber(L, 3, 0);
    float zoom = (float)luaL_optnumber(L, 4, 1);

    Camera2D result;
    result.target = { (float)x, (float)y };
    result.offset = { GetRenderWidth() / 2.0f, GetRenderHeight() / 2.0f };
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

static int ring(lua_State* L)
{
    if (!safe) {
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
    if (!safe) {
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
    if (!safe) {
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
    if (!safe) {
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

static int triangle(lua_State* L)
{
    if (!safe) {
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
    if (!safe) {
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
    { "line", line },
    { "loadCamera", loadCamera },
    { "loadCanvas", loadCanvas },
    { "loadFont", loadFont },
    { "loadShader", loadShader },
    { "loadSvg", loadSvg },
    { "loadTexture", loadTexture },
    { "pixel", pixel },
    { "polygon", polygon },
    { "polygonLines", polygonLines },
    { "rectangle", rectangle },
    { "rectangleLines", rectangleLines },
    { "ring", ring },
    { "ringLines", ringLines },
    { "sector", sector },
    { "sectorLines", sectorLines },
    { "setColor", setColor },
    { "setFont", setFont },
    { "text", text },
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
    Vector2 result = MeasureTextEx(font, text, (float)font.baseSize, 0);
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
    if (!safe) {
        return luaL_error(L, "Some pesto.graphics calls can only be made in the pesto.draw callback.");
    }

    Camera2D camera = *(Camera2D*)luaL_checkudata(L, 1, "Camera");
    BeginMode2D(camera);

    return 0;
}

static int endDrawingCamera(lua_State* L)
{
    if (!safe) {
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
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);
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
