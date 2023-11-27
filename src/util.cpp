#include "util.h"

static void generateHeader(const char* filename)
{
    int size;
    unsigned char* data = LoadFileData(TextFormat("%s%s", PROJECT_PATH, filename), &size);
    ExportDataAsCode(data, size, TextFormat("%s%s.h", PROJECT_PATH, filename));
    UnloadFileData(data);
}

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
    SetTraceLogLevel(LOG_NONE);

    Image icon = LoadImage(PROJECT_PATH "assets/icon.png");
    ExportImageAsCode(icon, PROJECT_PATH "assets/icon.png.h");
    UnloadImage(icon);

    int size;
    unsigned char* data = LoadFileData(PROJECT_PATH "assets/luacheck.exe", &size);
    ExportDataAsCode(data, size, PROJECT_PATH "assets/luacheck.exe.h");
    UnloadFileData(data);

    generateHeader("src/scripts/boot.lua");
    generateHeader("src/scripts/state.lua");
    generateHeader("src/scripts/reload.lua");

    generateHeader("src/lib/lua/astar.lua");
    generateHeader("src/lib/lua/brinevector.lua");
    generateHeader("src/lib/lua/bump.lua");
    generateHeader("src/lib/lua/classic.lua");
    generateHeader("src/lib/lua/flux.lua");
    generateHeader("src/lib/lua/inspect.lua");
    generateHeader("src/lib/lua/json.lua");
    generateHeader("src/lib/lua/lume.lua");
    generateHeader("src/lib/lua/signal.lua");
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

    SetTraceLogLevel(LOG_INFO);
}

// From raylib examples
// Draw text using font inside rectangle limits with support for text selection
void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
    int length = TextLength(text); // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0; // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f; // Offset X to next character to draw

    float scaleFactor = fontSize / (float)font.baseSize; // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0,
        DRAW_STATE = 1 };
    int state = wordWrap ? MEASURE_STATE : DRAW_STATE;

    int startLine = -1; // Index where to begin drawing (where a line begins)
    int endLine = -1; // Index where to stop drawing (where a line ends)
    int lastk = -1; // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++) {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f)
            codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n') {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width * scaleFactor : font.glyphs[index].advanceX * scaleFactor;

            if (i + 1 < length)
                glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE) {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n'))
                endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width) {
                endLine = (endLine < 1) ? i : endLine;
                if (i == endLine)
                    endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine)
                    endLine = (i - codepointByteCount);

                state = !state;
            } else if ((i + 1) == length) {
                endLine = i;
                state = !state;
            } else if (codepoint == '\n')
                state = !state;

            if (state == DRAW_STATE) {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        } else {
            if (codepoint == '\n') {
                if (!wordWrap) {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }
            } else {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width)) {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize * scaleFactor) > rec.height)
                    break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength))) {
                    DrawRectangleRec(Rectangle { rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize * scaleFactor }, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t')) {
                    DrawTextCodepoint(font, codepoint, Vector2 { rec.x + textOffsetX, rec.y + textOffsetY }, fontSize, isGlyphSelected ? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine)) {
                textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' '))
            textOffsetX += glyphWidth; // avoid leading spaces
    }
}
