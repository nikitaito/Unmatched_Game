#include "combat_page.h"
#include "cp_colors.h"

void CombatPage :: Init(Rectangle newArea){
    area = newArea;

    float halfW = area.width  / 2.0f;
    float halfH = area.height / 2.0f;

    defenceSlot = Rectangle{
        area.x + halfW * 0.5f - CP_CARD_WIDTH * 0.35f,
        area.y + halfH * 0.5f - CP_CARD_HEIGHT * 0.35f,
        CP_CARD_WIDTH * 0.7f, CP_CARD_HEIGHT * 0.7f
    };
    attackSlot = Rectangle{
        area.x + halfW * 1.5f - CP_CARD_WIDTH * 0.35f,
        area.y + halfH * 0.5f - CP_CARD_HEIGHT * 0.35f,
        CP_CARD_WIDTH * 0.7f, CP_CARD_HEIGHT * 0.7f
    };

    defenceHand.anchor = Rectangle{ area.x + 40, area.y + halfH + halfH * 0.35f, CP_CARD_WIDTH * 0.5f, CP_CARD_HEIGHT * 0.5f };
    attackHand.anchor  = Rectangle{ area.x + halfW + 40, area.y + halfH + halfH * 0.35f, CP_CARD_WIDTH * 0.5f, CP_CARD_HEIGHT * 0.5f };

    defenceHand.expanded = false;
    attackHand.expanded  = false;
    defenceHand.hoveredIndex = -1;
    attackHand.hoveredIndex  = -1;

    skipButton   = Rectangle{ area.x + halfW - 260, area.y + halfH + halfH * 0.15f, 120, 44 };
    chooseButton = Rectangle{ area.x + halfW - 130, area.y + halfH + halfH * 0.15f, 120, 44 };

    skipPressed = false;
    choosePressed = false;
    skipHovered = false;
    chooseHovered = false;
    defenceCardClicked = -1;
    attackCardClicked  = -1;
}

void CombatPage :: Update(){
    Vector2 mouse = GetMousePosition();
    bool leftClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    skipHovered   = CheckCollisionPointRec(mouse, skipButton);
    chooseHovered = CheckCollisionPointRec(mouse, chooseButton);
    skipPressed   = leftClicked && skipHovered;
    choosePressed = leftClicked && chooseHovered;

    constexpr float handCardW = CP_CARD_WIDTH * 0.5f;
    constexpr float handCardH = CP_CARD_HEIGHT * 0.5f;

    defenceHand.Update(handCardW, handCardH, defenceCardClicked);
}

void CombatPage :: DrawLabel(const char *text, Vector2 pos, float size, Color color) const{
    DrawTextEx(font, text, pos, size, 1.0f, color);
}

void CombatPage :: Draw() const{
    float halfW = area.width / 2.0f;
    float halfH = area.height / 2.0f;

    if (backgroundImage.id > 0) {
        Rectangle src{ 0, 0, (float)backgroundImage.width, (float)backgroundImage.height };
        DrawTexturePro(backgroundImage, src, area, Vector2{ 0, 0 }, 0.0f, WHITE);
        if (backgroundOverlayAlpha > 0.0f) {
            DrawRectangle((int)area.x, (int)area.y, (int)area.width, (int)area.height,
                           Fade(CPColors::PanelFill, backgroundOverlayAlpha));
        }
    } else {
        DrawRectangle((int)area.x, (int)area.y, (int)area.width, (int)area.height, CPColors::PanelFill);
    }

    DrawRectangleRoundedLinesEx(area, 0.02f, 8, 3, CPColors::PanelBorder);
    Rectangle innerFrame{ area.x + 6, area.y + 6, area.width - 12, area.height - 12 };
    DrawRectangleRoundedLinesEx(innerFrame, 0.02f, 8, 1, Fade(CPColors::Gold, 0.5f));

    float studR = 7.0f;
    DrawPoly(Vector2{ area.x, area.y }, 4, studR, 45.0f, CPColors::Gold);
    DrawPoly(Vector2{ area.x + area.width, area.y }, 4, studR, 45.0f, CPColors::Gold);
    DrawPoly(Vector2{ area.x, area.y + area.height }, 4, studR, 45.0f, CPColors::Gold);
    DrawPoly(Vector2{ area.x + area.width, area.y + area.height }, 4, studR, 45.0f, CPColors::Gold);

    DrawLine((int)(area.x + halfW), (int)area.y, (int)(area.x + halfW), (int)(area.y + area.height), CPColors::PanelBorder);
    DrawLine((int)area.x, (int)(area.y + halfH), (int)(area.x + area.width), (int)(area.y + halfH), CPColors::PanelBorder);

    const char *title = "Combat Page";
    float titleFontSize = 34;
    float titleSpacing = 2.0f;
    Vector2 titleSize = MeasureTextEx(font, title, titleFontSize, titleSpacing);
    Vector2 titlePos{ area.x + area.width / 2 - titleSize.x / 2, area.y - 56 };
    DrawTextEx(font, title, Vector2{ titlePos.x + 2, titlePos.y + 2 }, titleFontSize, titleSpacing, Fade(BLACK, 0.5f));
    DrawTextEx(font, title, titlePos, titleFontSize, titleSpacing, CPColors::Gold);
    DrawLineEx(Vector2{ area.x + area.width / 2 - titleSize.x / 2 - 20, titlePos.y + titleSize.y + 8 },
               Vector2{ area.x + area.width / 2 + titleSize.x / 2 + 20, titlePos.y + titleSize.y + 8 },
               1.5f, Fade(CPColors::Gold, 0.7f));

    DrawRectangleRounded(Rectangle{ area.x + 20, area.y + 20, 180, 40 }, 0.2f, 6, CPColors::ButtonFill);
    DrawRectangleRoundedLinesEx(Rectangle{ area.x + 20, area.y + 20, 180, 40 }, 0.2f, 6, 2, CPColors::PanelBorder);
    DrawLabel("Defence", Vector2{ area.x + 45, area.y + 30 }, 22, CPColors::Gold);

    DrawRectangleRounded(Rectangle{ area.x + area.width - 200, area.y + 20, 180, 40 }, 0.2f, 6, CPColors::ButtonFill);
    DrawRectangleRoundedLinesEx(Rectangle{ area.x + area.width - 200, area.y + 20, 180, 40 }, 0.2f, 6, 2, CPColors::PanelBorder);
    DrawLabel("Attack", Vector2{ area.x + area.width - 170, area.y + 30 }, 22, CPColors::Gold);

    DrawRectangleRounded(defenceSlot, 0.05f, 6, CPColors::SlotFill);
    DrawRectangleRoundedLinesEx(defenceSlot, 0.05f, 6, 2, CPColors::PanelBorder);
    DrawRectangleRounded(attackSlot, 0.05f, 6, CPColors::SlotFill);
    DrawRectangleRoundedLinesEx(attackSlot, 0.05f, 6, 2, CPColors::PanelBorder);

    Vector2 c{ area.x + halfW, area.y + halfH * 0.5f };
    if (centerIcon.id > 0) {
        Rectangle src{ 0, 0, (float)centerIcon.width, (float)centerIcon.height };
        Rectangle dst{ c.x - centerIconSize / 2, c.y - centerIconSize / 2, centerIconSize, centerIconSize };
        DrawTexturePro(centerIcon, src, dst, Vector2{ 0, 0 }, 0.0f, WHITE);
    } else {
        DrawPoly(c, 4, 18, 45.0f, CPColors::Gold);
    }

    Rectangle defenceTextBg{ area.x + 12, area.y + halfH + 12, 190, 60 };
    DrawRectangleRounded(defenceTextBg, 0.25f, 6, CPColors::TextBackdrop);
    DrawLabel("Show defence\ncard", Vector2{ area.x + 20, area.y + halfH + 20 }, 20, CPColors::TextLight);

    Rectangle defenceHandTextBg{ area.x + halfW - 168, area.y + halfH + 12, 150, 32 };
    DrawRectangleRounded(defenceHandTextBg, 0.3f, 6, CPColors::TextBackdrop);
    DrawLabel("Handcard", Vector2{ area.x + halfW - 160, area.y + halfH + 20 }, 20, CPColors::TextLight);

    Color skipCol     = skipHovered ? CPColors::ButtonHoverFill : CPColors::ButtonFill;
    Color skipTextCol = skipHovered ? CPColors::TextOnGold : CPColors::TextLight;
    DrawRectangleRounded(skipButton, 0.2f, 6, skipCol);
    DrawRectangleRoundedLinesEx(skipButton, 0.2f, 6, 2, CPColors::ButtonBorder);
    Vector2 skipTextSize = MeasureTextEx(font, "SKIP", 20, 1.0f);
    DrawLabel("SKIP", Vector2{ skipButton.x + skipButton.width / 2 - skipTextSize.x / 2, skipButton.y + 12 }, 20, skipTextCol);

    Color chooseCol     = chooseHovered ? CPColors::ButtonHoverFill : CPColors::ButtonFill;
    Color chooseTextCol = chooseHovered ? CPColors::TextOnGold : CPColors::TextLight;
    DrawRectangleRounded(chooseButton, 0.2f, 6, chooseCol);
    DrawRectangleRoundedLinesEx(chooseButton, 0.2f, 6, 2, CPColors::ButtonBorder);
    Vector2 chooseTextSize = MeasureTextEx(font, "CHOOSE", 20, 1.0f);
    DrawLabel("CHOOSE", Vector2{ chooseButton.x + chooseButton.width / 2 - chooseTextSize.x / 2, chooseButton.y + 12 }, 20, chooseTextCol);

    constexpr float handCardW = CP_CARD_WIDTH * 0.5f;
    constexpr float handCardH = CP_CARD_HEIGHT * 0.5f;

    defenceHand.Draw(handCardW, handCardH);
}