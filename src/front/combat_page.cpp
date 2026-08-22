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
    chooseButton = Rectangle{ area.x + halfW - 130, area.y + halfH + halfH * 0.15f, 140, 44 };

    skipPressed = false;
    choosePressed = false;
    skipHovered = false;
    chooseHovered = false;
    defenceCardClicked = -1;
    attackCardClicked  = -1;
    stage = CombatStage::None;
    showingResult = false;
}

void CombatPage :: Update(){
    Vector2 mouse = GetMousePosition();
    bool leftClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    defenceCardClicked = -1;
    attackCardClicked  = -1;

    if(showingResult){
        skipHovered = false;
        skipPressed = false;
        chooseHovered = CheckCollisionPointRec(mouse, chooseButton);
        choosePressed = leftClicked && chooseHovered;
        return;
    }

    if(stage == CombatStage::AwaitAttackCard){
        constexpr float handCardW = CP_CARD_WIDTH * 0.5f;
        constexpr float handCardH = CP_CARD_HEIGHT * 0.5f;
        attackHand.Update(handCardW, handCardH, attackCardClicked);
    }
    if(stage == CombatStage::AwaitDefenseCard){
        constexpr float handCardW = CP_CARD_WIDTH * 0.5f;
        constexpr float handCardH = CP_CARD_HEIGHT * 0.5f;
        defenceHand.Update(handCardW, handCardH, defenceCardClicked);
    }

    skipHovered   = (stage == CombatStage::AwaitDefenseCard) && CheckCollisionPointRec(mouse, skipButton);
    chooseHovered = (stage == CombatStage::Ready) && CheckCollisionPointRec(mouse, chooseButton);
    skipPressed   = leftClicked && skipHovered;
    choosePressed = leftClicked && chooseHovered;
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

    const char *title = "Combat";
    float titleFontSize = 34;
    float titleSpacing = 2.0f;
    Vector2 titleSize = MeasureTextEx(font, title, titleFontSize, titleSpacing);
    Vector2 titlePos{ area.x + area.width / 2 - titleSize.x / 2, area.y + 14 };
    DrawTextEx(font, title, Vector2{ titlePos.x + 2, titlePos.y + 2 }, titleFontSize, titleSpacing, Fade(BLACK, 0.5f));
    DrawTextEx(font, title, titlePos, titleFontSize, titleSpacing, CPColors::Gold);
    DrawLineEx(Vector2{ area.x + area.width / 2 - titleSize.x / 2 - 20, titlePos.y + titleSize.y + 8 },
               Vector2{ area.x + area.width / 2 + titleSize.x / 2 + 20, titlePos.y + titleSize.y + 8 },
               1.5f, Fade(CPColors::Gold, 0.7f));

    if(showingResult){
        Rectangle logBox{ area.x + area.width * 0.15f, titlePos.y + titleSize.y + 40, area.width * 0.7f, area.height * 0.55f };
        DrawRectangleRounded(logBox, 0.04f, 8, CPColors::PanelFill);
        DrawRectangleRoundedLinesEx(logBox, 0.04f, 8, 2, CPColors::PanelBorder);
        DrawLabel(resultLog.c_str(), Vector2{ logBox.x + 24, logBox.y + 20 }, 20, CPColors::TextLight);

        Color chooseCol     = chooseHovered ? CPColors::ButtonHoverFill : CPColors::ButtonFill;
        Color chooseTextCol = chooseHovered ? CPColors::TextOnGold : CPColors::TextLight;
        DrawRectangleRounded(chooseButton, 0.2f, 6, chooseCol);
        DrawRectangleRoundedLinesEx(chooseButton, 0.2f, 6, 2, CPColors::ButtonBorder);
        Vector2 continueSize = MeasureTextEx(font, "CONTINUE", 20, 1.0f);
        DrawLabel("CONTINUE", Vector2{ chooseButton.x + chooseButton.width / 2 - continueSize.x / 2, chooseButton.y + 12 }, 20, chooseTextCol);
        return;
    }

    Rectangle defHeader{ area.x + 20, area.y + 20, halfW - 40, 40 };
    Rectangle atkHeader{ area.x + halfW + 20, area.y + 20, halfW - 40, 40 };
    DrawRectangleRounded(defHeader, 0.2f, 6, CPColors::ButtonFill);
    DrawRectangleRoundedLinesEx(defHeader, 0.2f, 6, 2, CPColors::PanelBorder);
    DrawLabel(defenderLabel.empty() ? "Defence" : defenderLabel.c_str(), Vector2{ defHeader.x + 14, defHeader.y + 10 }, 20, CPColors::Gold);

    DrawRectangleRounded(atkHeader, 0.2f, 6, CPColors::ButtonFill);
    DrawRectangleRoundedLinesEx(atkHeader, 0.2f, 6, 2, CPColors::PanelBorder);
    DrawLabel(attackerLabel.empty() ? "Attack" : attackerLabel.c_str(), Vector2{ atkHeader.x + 14, atkHeader.y + 10 }, 20, CPColors::Gold);

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

    const char *statusText =
        (stage == CombatStage::AwaitAttackCard) ? "Attacker: choose an Attack or Versatile card" :
        (stage == CombatStage::AwaitDefenseCard) ? "Defender: choose a Defense card, or Skip" :
        (stage == CombatStage::Ready)            ? "Both cards are set - press RESOLVE" : "";
    Vector2 statusSize = MeasureTextEx(font, statusText, 20, 1.0f);
    DrawLabel(statusText, Vector2{ area.x + halfW - statusSize.x / 2, area.y + halfH * 0.5f - statusSize.y - 24 }, 20, CPColors::TextLight);

    bool defenceActive = (stage == CombatStage::AwaitDefenseCard);
    bool attackActive  = (stage == CombatStage::AwaitAttackCard);

    Rectangle defenceHandTextBg{ area.x + 12, area.y + halfH + 12, 190, 32 };
    DrawRectangleRounded(defenceHandTextBg, 0.3f, 6, CPColors::TextBackdrop);
    DrawLabel(defenceActive ? "Your hand" : "Waiting...", Vector2{ area.x + 20, area.y + halfH + 20 }, 20, CPColors::TextLight);

    Rectangle attackHandTextBg{ area.x + halfW + 12, area.y + halfH + 12, 190, 32 };
    DrawRectangleRounded(attackHandTextBg, 0.3f, 6, CPColors::TextBackdrop);
    DrawLabel(attackActive ? "Your hand" : "Waiting...", Vector2{ area.x + halfW + 20, area.y + halfH + 20 }, 20, CPColors::TextLight);

    Color skipCol     = !defenceActive ? Fade(CPColors::ButtonFill, 0.4f) : (skipHovered ? CPColors::ButtonHoverFill : CPColors::ButtonFill);
    Color skipTextCol = !defenceActive ? Fade(CPColors::TextLight, 0.4f) : (skipHovered ? CPColors::TextOnGold : CPColors::TextLight);
    DrawRectangleRounded(skipButton, 0.2f, 6, skipCol);
    DrawRectangleRoundedLinesEx(skipButton, 0.2f, 6, 2, CPColors::ButtonBorder);
    Vector2 skipTextSize = MeasureTextEx(font, "SKIP", 20, 1.0f);
    DrawLabel("SKIP", Vector2{ skipButton.x + skipButton.width / 2 - skipTextSize.x / 2, skipButton.y + 12 }, 20, skipTextCol);

    bool resolveActive = (stage == CombatStage::Ready);
    Color chooseCol     = !resolveActive ? Fade(CPColors::ButtonFill, 0.4f) : (chooseHovered ? CPColors::ButtonHoverFill : CPColors::ButtonFill);
    Color chooseTextCol = !resolveActive ? Fade(CPColors::TextLight, 0.4f) : (chooseHovered ? CPColors::TextOnGold : CPColors::TextLight);
    DrawRectangleRounded(chooseButton, 0.2f, 6, chooseCol);
    DrawRectangleRoundedLinesEx(chooseButton, 0.2f, 6, 2, CPColors::ButtonBorder);
    Vector2 chooseTextSize = MeasureTextEx(font, "RESOLVE", 20, 1.0f);
    DrawLabel("RESOLVE", Vector2{ chooseButton.x + chooseButton.width / 2 - chooseTextSize.x / 2, chooseButton.y + 12 }, 20, chooseTextCol);

    constexpr float handCardW = CP_CARD_WIDTH * 0.5f;
    constexpr float handCardH = CP_CARD_HEIGHT * 0.5f;

    defenceHand.Draw(handCardW, handCardH);
    attackHand.Draw(handCardW, handCardH);
}
