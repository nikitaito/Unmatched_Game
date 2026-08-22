#include "front/choose.h"
#include <cstdio>

bool ChoosePage :: DrawCharacterCard(Rectangle rect, Texture2D portrait, const char* name, const char* subtitle,
                                      Color subtitleColor, Font titleFont, Font labelFont,
                                      Vector2 mousePos, bool mouseDown, bool disabled){

    bool hover   = !disabled && CheckCollisionPointRec(mousePos, rect);
    bool clicked = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    Color panelBg          = { 20, 22, 28, 200 };
    Color panelHoverBg     = { 38, 40, 48, 220 };
    Color panelPressBg     = { 10, 12, 16, 220 };
    Color panelBorder      = { 70, 70, 80, 255 };
    Color panelHoverBorder = { 160, 160, 170, 255 };

    Color bg     = panelBg;
    Color border = panelBorder;
    if (hover)
    {
        bg     = mouseDown ? panelPressBg : panelHoverBg;
        border = panelHoverBorder;
    }

    DrawRectangleRounded(rect, 0.05f, 10, bg);
    DrawRectangleRoundedLines(rect, 0.05f, 10, border);

    float padding      = rect.width * 0.08f;
    float portraitArea = rect.height * 0.78f;
    float availW       = rect.width - padding * 2;
    float availH       = portraitArea - padding;

    float srcRatio = 1483.0f / 1061.0f;
    float destW = availW;
    float destH = destW * srcRatio;
    if (destH > availH)
    {
        destH = availH;
        destW = destH / srcRatio;
    }

    Rectangle destRect = {
        rect.x + rect.width / 2 - destW / 2,
        rect.y + padding,
        destW,
        destH
    };

    Color tint = disabled ? Color{ 130, 130, 130, 130 } : WHITE;
    if (portrait.id != 0)
    {
        Rectangle srcRect = { 0, 0, (float)portrait.width, (float)portrait.height };
        DrawTexturePro(portrait, srcRect, destRect, { 0, 0 }, 0.0f, tint);
    }

    if (disabled)
    {
        DrawRectangle((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, Color{ 0, 0, 0, 130 });
    }

    float nameFontSize = rect.height * 0.05f;
    Vector2 nameSize = MeasureTextEx(titleFont, name, nameFontSize, 2.0f);
    Vector2 namePos = {
        rect.x + rect.width / 2 - nameSize.x / 2,
        rect.y + portraitArea + padding * 0.3f
    };
    Color nameColor = disabled ? Color{ 140, 140, 140, 255 } : RAYWHITE;
    DrawTextEx(titleFont, name, namePos, nameFontSize, 2.0f, nameColor);

    float subFontSize = rect.height * 0.03f;
    Vector2 subSize = MeasureTextEx(labelFont, subtitle, subFontSize, 2.0f);
    Vector2 subPos = {
        rect.x + rect.width / 2 - subSize.x / 2,
        namePos.y + nameFontSize * 1.3f
    };
    Color subColor = disabled ? Color{ 110, 110, 110, 255 } : subtitleColor;
    DrawTextEx(labelFont, subtitle, subPos, subFontSize, 2.0f, subColor);

    if (disabled)
    {
        const char* takenLabel = "ALREADY CHOSEN";
        float takenSize = rect.height * 0.026f;
        Vector2 tSize = MeasureTextEx(labelFont, takenLabel, takenSize, 2.0f);
        Vector2 tPos = {
            rect.x + rect.width / 2 - tSize.x / 2,
            rect.y + rect.height / 2 - tSize.y / 2
        };
        DrawTextEx(labelFont, takenLabel, tPos, takenSize, 2.0f, Color{ 200, 60, 40, 255 });
    }

    return clicked;
}

void ChoosePage :: Make_Page(Page & current_page, Texture2D & background,
                              Font & titleFont, Font & labelFont,
                              Texture2D & draculaTex, Texture2D & invManTex, Texture2D & holmesTex,
                              int age1, int age2,
                              CharacterType & character1, CharacterType & character2){

    Color overlayColor  = { 0, 0, 0, 150 };
    Color goldColor     = { 212, 175, 90, 255 };
    Color subtitleColor = { 170, 150, 110, 255 };

    struct CharacterOption
    {
        CharacterType type;
        const char* name;
        const char* subtitle;
        Color subtitleColor;
        Texture2D* portrait;
    };

    CharacterOption options[3] = {
        { CharacterType :: Dracula,        "DRACULA",        "THE LORD OF BLOODS",   Color{ 190, 60, 50, 255 }, &draculaTex },
        { CharacterType :: Invman,         "INVISIBLE MAN",  "THE GHOST",            subtitleColor,             &invManTex  },
        { CharacterType :: SherlockHolmes, "SHERLOCK HOLMES","THE GRAND DETECTIVE",  subtitleColor,             &holmesTex  },
    };

    bool age1PicksFirst = (age1 <= age2);

    {
        int sw = GetScreenWidth();
        int sh = GetScreenHeight();
        int centerX = sw / 2;

        Vector2 mousePos = GetMousePosition();
        bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        bool isFirstPick = (firstPickIndex == -1);
        int displayedPlayerNumber = isFirstPick ? 1 : 2;

        ClearBackground(BLACK);

        DrawTexturePro(background,
            { 0, 0, (float)background.width, (float)background.height },
            { 0, 0, (float)sw, (float)sh },
            { 0, 0 }, 0.0f, WHITE);
        DrawRectangle(0, 0, sw, sh, overlayColor);

        char titleText[64];
        snprintf(titleText, sizeof(titleText), "PLAYER %d, CHOOSE YOUR LEGEND", displayedPlayerNumber);
        float titleFontSize = sh * 0.06f;
        Vector2 titleSize = MeasureTextEx(titleFont, titleText, titleFontSize, 2.0f);
        DrawTextEx(titleFont, titleText, { centerX - titleSize.x / 2, sh * 0.08f }, titleFontSize, 2.0f, goldColor);

        const char* subtitleLine = "SELECT ONE FIGHTER TO STEP INTO THE FOG";
        float subFontSize = sh * 0.02f;
        Vector2 subSize = MeasureTextEx(labelFont, subtitleLine, subFontSize, 2.0f);
        DrawTextEx(labelFont, subtitleLine, { centerX - subSize.x / 2, sh * 0.15f }, subFontSize, 2.0f, RAYWHITE);

        float cardWidth  = sw * 0.16f;
        float cardHeight = sh * 0.6f;
        float gap        = sw * 0.03f;
        float totalWidth = cardWidth * 3 + gap * 2;
        float startX     = centerX - totalWidth / 2;
        float cardY       = sh * 0.28f;

        int clickedIndex = -1;
        for (int i = 0; i < 3; i++)
        {
            Rectangle cardRect = { startX + i * (cardWidth + gap), cardY, cardWidth, cardHeight };
            bool disabled = (i == firstPickIndex);

            bool clicked = DrawCharacterCard(cardRect, *options[i].portrait, options[i].name, options[i].subtitle,
                                              options[i].subtitleColor, titleFont, labelFont,
                                              mousePos, mouseDown, disabled);
            if (clicked) clickedIndex = i;
        }

        const char* caption = isFirstPick ? "The drafting phase has begun."
                                           : "Player 1 has made their choice.";
        float capFontSize = sh * 0.02f;
        Vector2 capSize = MeasureTextEx(labelFont, caption, capFontSize, 2.0f);
        DrawTextEx(labelFont, caption, { centerX - capSize.x / 2, cardY + cardHeight + sh * 0.05f }, capFontSize, 2.0f, Color{ 190, 190, 195, 200 });

        if (clickedIndex != -1)
        {
            if (isFirstPick)
            {
                firstPickIndex = clickedIndex;
            }
            else
            {
                secondPickIndex = clickedIndex;

                CharacterType firstPickType  = options[firstPickIndex].type;
                CharacterType secondPickType = options[secondPickIndex].type;

                if (age1PicksFirst)
                {
                    character1 = firstPickType;
                    character2 = secondPickType;
                }
                else
                {
                    character2 = firstPickType;
                    character1 = secondPickType;
                }

                current_page = Page :: Game;
            }
        }
    }
}

void ChoosePage :: Reset(){
    firstPickIndex  = -1;
    secondPickIndex = -1;
}
