#include "game_page.h"
#include <cstdio>
#include <cmath>

// gold-on-navy theme, kept in one place so re-theming only touches this block
namespace
{
    Color NavyBackground()  { return Color{ 10, 14, 26, 255 }; }
    Color NavyOverlay()     { return Color{ 8, 12, 22, 150 }; }
    Color NavyPanelBg()     { return Color{ 20, 26, 45, 225 }; }
    Color NavyPanelBgLight(){ return Color{ 28, 35, 58, 225 }; }
    Color NavyPanelBorder() { return Color{ 70, 82, 115, 255 }; }
    Color NavyShadow()      { return Color{ 0, 0, 0, 120 }; }

    Color Gold()            { return Color{ 212, 175, 90, 255 }; }
    Color GoldBright()      { return Color{ 235, 200, 130, 255 }; }
    Color GoldDim()         { return Color{ 120, 102, 66, 255 }; }
    Color GoldGlow()        { return Color{ 212, 175, 90, 60 }; }

    Color TextWhite()       { return RAYWHITE; }
    Color TextMuted()       { return Color{ 190, 190, 198, 255 }; }
    Color TextOnGold()      { return Color{ 24, 20, 14, 255 }; }

    Color LifeRed()         { return Color{ 195, 45, 45, 255 }; }

    Color PhosphorGreen()     { return Color{ 90, 255, 140, 255 }; }
    Color PhosphorGreenGlow() { return Color{ 90, 255, 140, 70 }; }

    // panel with drop shadow + double gold border, shared by every framed region
    void DrawFramedPanel(Rectangle rect, Color fill, bool cornerAccents = false){
        DrawRectangleRec({ rect.x + 3, rect.y + 4, rect.width, rect.height }, NavyShadow());
        DrawRectangleRec(rect, fill);
        DrawRectangleLinesEx(rect, 2.0f, GoldDim());
        DrawRectangleLinesEx({ rect.x + 3, rect.y + 3, rect.width - 6, rect.height - 6 }, 1.0f, NavyPanelBorder());

        if(cornerAccents){
            float len = fmin(rect.width, rect.height) * 0.06f;
            if(len > 22.0f) len = 22.0f;
            Color c = Gold();
            DrawLineEx({ rect.x, rect.y + len }, { rect.x, rect.y }, 2.0f, c);
            DrawLineEx({ rect.x, rect.y }, { rect.x + len, rect.y }, 2.0f, c);
            DrawLineEx({ rect.x + rect.width - len, rect.y }, { rect.x + rect.width, rect.y }, 2.0f, c);
            DrawLineEx({ rect.x + rect.width, rect.y }, { rect.x + rect.width, rect.y + len }, 2.0f, c);
            DrawLineEx({ rect.x, rect.y + rect.height - len }, { rect.x, rect.y + rect.height }, 2.0f, c);
            DrawLineEx({ rect.x, rect.y + rect.height }, { rect.x + len, rect.y + rect.height }, 2.0f, c);
            DrawLineEx({ rect.x + rect.width - len, rect.y + rect.height }, { rect.x + rect.width, rect.y + rect.height }, 2.0f, c);
            DrawLineEx({ rect.x + rect.width, rect.y + rect.height - len }, { rect.x + rect.width, rect.y + rect.height }, 2.0f, c);
        }
    }

    // filled when 'primary' (e.g. End Turn), outline-only otherwise (Maneuver/Attack/Scheme)
    void DrawThemedButton(Rectangle rect, const char *label, Font font, float fontSize, bool primary){
        DrawRectangleRounded({ rect.x + 2, rect.y + 3, rect.width, rect.height }, 0.16f, 8, NavyShadow());

        Color fill = primary ? Gold() : NavyPanelBgLight();
        DrawRectangleRounded(rect, 0.16f, 8, fill);
        DrawRectangleRoundedLines(rect, 0.16f, 8, primary ? GoldBright() : Gold());

        Rectangle inner = { rect.x + 3, rect.y + 3, rect.width - 6, rect.height - 6 };
        DrawRectangleRoundedLines(inner, 0.16f, 8, primary ? Color{ 255, 230, 180, 140 } : Color{ 212, 175, 90, 90 });

        Color textColor = primary ? TextOnGold() : GoldBright();
        Vector2 textSize = MeasureTextEx(font, label, fontSize, 1.0f);
        Vector2 textPos = { rect.x + rect.width / 2 - textSize.x / 2, rect.y + rect.height / 2 - textSize.y / 2 };
        DrawTextEx(font, label, textPos, fontSize, 1.0f, textColor);
    }

    // small gold diamond, used beside the turn banner
    void DrawDiamondAccent(Vector2 center, float size, Color color){
        Vector2 top = { center.x, center.y - size };
        Vector2 right = { center.x + size, center.y };
        Vector2 bottom = { center.x, center.y + size };
        Vector2 left = { center.x - size, center.y };
        DrawTriangle(top, left, right, color);
        DrawTriangle(bottom, right, left, color);
    }

    // thin centered divider line, shared between sections
    void DrawCenteredDivider(float centerX, float y, float width, Color color){
        DrawLineEx({ centerX - width / 2, y }, { centerX + width / 2, y }, 1.0f, color);
    }
}

// normalized (0-1) centers of the board's 32 numbered spaces, measured
// against the 1337x866 map art; nudge an entry if its ring looks off-center
namespace
{
    const Vector2 kSpaceCenterNorm[GP_SPACE_COUNT] = {
        /*  0 */ { 0.072f, 0.106f }, /*  1 */ { 0.206f, 0.054f }, /*  2 */ { 0.056f, 0.293f }, /*  3 */ { 0.177f, 0.311f },
        /*  4 */ { 0.280f, 0.237f }, /*  5 */ { 0.384f, 0.097f }, /*  6 */ { 0.582f, 0.102f }, /*  7 */ { 0.511f, 0.240f },
        /*  8 */ { 0.318f, 0.435f }, /*  9 */ { 0.206f, 0.505f }, /* 10 */ { 0.087f, 0.552f }, /* 11 */ { 0.150f, 0.768f },
        /* 12 */ { 0.321f, 0.678f }, /* 13 */ { 0.458f, 0.564f }, /* 14 */ { 0.560f, 0.471f }, /* 15 */ { 0.500f, 0.764f },
        /* 16 */ { 0.427f, 0.901f }, /* 17 */ { 0.317f, 0.870f }, /* 18 */ { 0.208f, 0.912f }, /* 19 */ { 0.548f, 0.917f },
        /* 20 */ { 0.637f, 0.801f }, /* 21 */ { 0.694f, 0.557f }, /* 22 */ { 0.858f, 0.442f }, /* 23 */ { 0.932f, 0.569f },
        /* 24 */ { 0.805f, 0.605f }, /* 25 */ { 0.771f, 0.813f }, /* 26 */ { 0.948f, 0.787f }, /* 27 */ { 0.869f, 0.916f },
        /* 28 */ { 0.694f, 0.236f }, /* 29 */ { 0.803f, 0.111f }, /* 30 */ { 0.867f, 0.244f }, /* 31 */ { 0.939f, 0.117f },
    };
}

// small heart badge showing only current HP (a fraction wouldn't be legible at this size)
void GamePage :: DrawLifeBadge(Vector2 center, int currentHP, float radius){
    float r = radius;
    DrawCircleV({ center.x, center.y + r * 0.12f }, r * 1.18f, Color{ 0, 0, 0, 90 });

    Vector2 leftLobe = { center.x - r * 0.5f, center.y - r * 0.25f };
    Vector2 rightLobe = { center.x + r * 0.5f, center.y - r * 0.25f };
    DrawCircleV(leftLobe, r * 0.55f, LifeRed());
    DrawCircleV(rightLobe, r * 0.55f, LifeRed());

    Vector2 t1 = { center.x - r, center.y - r * 0.1f };
    Vector2 t2 = { center.x + r, center.y - r * 0.1f };
    Vector2 t3 = { center.x, center.y + r };
    DrawTriangle(t1, t3, t2, LifeRed());

    char hpText[8];
    snprintf(hpText, sizeof(hpText), "%d", currentHP);
    float fontSize = r * 0.9f;
    int textW = MeasureText(hpText, (int)fontSize);
    DrawText(hpText, (int)(center.x - textW / 2.0f), (int)(center.y - fontSize / 2.0f + r * 0.1f), (int)fontSize, TextWhite());
}

// fixed 1337x866 source map, scaled to fit 'area' keeping aspect ratio, centered
Rectangle GamePage :: DrawMap(Rectangle area, Texture2D mapTexture){
    const float srcW = 1337.0f, srcH = 866.0f;
    float srcRatio = srcH / srcW;

    float destW = area.width;
    float destH = destW * srcRatio;
    if(destH > area.height){
        destH = area.height;
        destW = destH / srcRatio;
    }

    Rectangle destRect = { area.x + area.width / 2 - destW / 2, area.y + area.height / 2 - destH / 2, destW, destH };

    DrawRectangleRec({ destRect.x + 3, destRect.y + 4, destRect.width, destRect.height }, NavyShadow());

    if(mapTexture.id != 0){
        Rectangle srcRect = { 0, 0, (float)mapTexture.width, (float)mapTexture.height };
        DrawTexturePro(mapTexture, srcRect, destRect, { 0, 0 }, 0.0f, WHITE);
    } else {
        DrawRectangleRec(destRect, Color{ 30, 36, 58, 255 });
    }

    DrawRectangleLinesEx({ destRect.x - 4, destRect.y - 4, destRect.width + 8, destRect.height + 8 }, 2.0f, GoldDim());
    DrawRectangleLinesEx(destRect, 1.0f, NavyPanelBorder());

    float len = fmin(destRect.width, destRect.height) * 0.03f;
    if(len > 30.0f) len = 30.0f;
    Rectangle frame = { destRect.x - 4, destRect.y - 4, destRect.width + 8, destRect.height + 8 };
    Color c = Gold();
    DrawLineEx({ frame.x, frame.y + len }, { frame.x, frame.y }, 2.5f, c);
    DrawLineEx({ frame.x, frame.y }, { frame.x + len, frame.y }, 2.5f, c);
    DrawLineEx({ frame.x + frame.width - len, frame.y }, { frame.x + frame.width, frame.y }, 2.5f, c);
    DrawLineEx({ frame.x + frame.width, frame.y }, { frame.x + frame.width, frame.y + len }, 2.5f, c);
    DrawLineEx({ frame.x, frame.y + frame.height - len }, { frame.x, frame.y + frame.height }, 2.5f, c);
    DrawLineEx({ frame.x, frame.y + frame.height }, { frame.x + len, frame.y + frame.height }, 2.5f, c);
    DrawLineEx({ frame.x + frame.width - len, frame.y + frame.height }, { frame.x + frame.width, frame.y + frame.height }, 2.5f, c);
    DrawLineEx({ frame.x + frame.width, frame.y + frame.height - len }, { frame.x + frame.width, frame.y + frame.height }, 2.5f, c);

    return destRect;
}

// Deck/Discard buttons + portrait + name + life badge + sidekick row. 'mirrored' flips
// which side things sit on for the right-hand hero so both panels mirror each other.
Rectangle GamePage :: DrawHeroPanel(Rectangle area, const HeroPanelData &data, Font nameFont, Font labelFont, bool mirrored, Rectangle &outDeckBtn, Rectangle &outDiscardBtn){
    Rectangle inset = { area.x + 6, area.y + 6, area.width - 12, area.height - 12 };
    DrawFramedPanel(inset, NavyPanelBg(), true);

    float padding = area.width * 0.09f;

    float btnW = (area.width - padding * 2 - 10.0f) / 2.0f;
    float btnH = area.height * 0.062f;
    float topY = area.y + padding * 0.7f;

    Rectangle deckBtn = { area.x + padding, topY, btnW, btnH };
    Rectangle discardBtn = { deckBtn.x + btnW + 10.0f, topY, btnW, btnH };

    DrawThemedButton(deckBtn, "DECK", labelFont, btnH * 0.42f, false);
    DrawThemedButton(discardBtn, "DISCARD", labelFont, btnH * 0.36f, false);

    outDeckBtn = deckBtn;
    outDiscardBtn = discardBtn;

    float portraitAreaH = area.height * 0.44f;
    float portraitTop = deckBtn.y + btnH + padding * 0.6f;

    const float srcW = 1061.0f, srcH = 1483.0f;
    float srcRatio = srcH / srcW;

    float availW = area.width - padding * 1.6f;
    float destW = availW;
    float destH = destW * srcRatio;
    if(destH > portraitAreaH){
        destH = portraitAreaH;
        destW = destH / srcRatio;
    }

    Rectangle portraitRect = { area.x + area.width / 2 - destW / 2, portraitTop, destW, destH };

    if(data.portrait.id != 0){
        Rectangle srcRect = { 0, 0, (float)data.portrait.width, (float)data.portrait.height };
        DrawTexturePro(data.portrait, srcRect, portraitRect, { 0, 0 }, 0.0f, WHITE);
    } else {
        DrawRectangleRec(portraitRect, Color{ 35, 40, 60, 255 });
    }
    DrawRectangleLinesEx(portraitRect, 1.5f, GoldDim());

    // life badge overlaps the portrait's outer-bottom corner, always in bounds
    float badgeRadius = fmin(area.width * 0.062f, destW * 0.22f);
    float badgeX = mirrored ? (portraitRect.x + portraitRect.width) : portraitRect.x;
    Vector2 badgeCenter = { badgeX, portraitRect.y + portraitRect.height - badgeRadius * 0.3f };
    DrawLifeBadge(badgeCenter, data.currentHP, badgeRadius);

    float nameFontSize = area.height * 0.03f;
    Vector2 nameSize = MeasureTextEx(nameFont, data.name, nameFontSize, 2.0f);
    Vector2 namePos = { area.x + area.width / 2 - nameSize.x / 2, portraitRect.y + portraitRect.height + padding * 0.5f };
    DrawTextEx(nameFont, data.name, namePos, nameFontSize, 2.0f, GoldBright());

    float dividerY = namePos.y + nameSize.y + padding * 0.35f;
    DrawCenteredDivider(area.x + area.width / 2, dividerY, area.width * 0.5f, GoldDim());

    Rectangle sidekickArea = {
        area.x + padding * 0.4f, dividerY + padding * 0.5f,
        area.width - padding * 0.8f, (area.y + area.height) - (dividerY + padding * 0.5f) - padding * 0.4f
    };
    DrawSidekickRow(sidekickArea, data.sidekicks, labelFont);

    return area;
}

// row of 638x400 circular token art, sized to fit both the panel width and the
// vertical room the divider leaves it
Rectangle GamePage :: DrawSidekickRow(Rectangle area, const std::vector<SidekickVisual> &sidekicks, Font labelFont){
    if(sidekicks.empty()) return area;

    float slotH = fmin(area.width * 0.46f, area.height * 0.9f);
    float slotW = slotH * (GP_TOKEN_SRC_W / GP_TOKEN_SRC_H);

    float gap = slotW * 0.15f;
    float totalWidth = slotW * sidekicks.size() + gap * (sidekicks.size() - 1);
    if(totalWidth > area.width){
        float scale = area.width / totalWidth;
        slotW *= scale; slotH *= scale; gap *= scale;
        totalWidth = area.width;
    }

    float startX = area.x + area.width / 2 - totalWidth / 2;
    float slotY = area.y + (area.height - slotH) / 2;

    for(size_t i = 0; i < sidekicks.size(); ++i){
        Rectangle slotRect = { startX + (float)i * (slotW + gap), slotY, slotW, slotH };
        const SidekickVisual &sk = sidekicks[i];

        if(sk.texture.id != 0){
            Rectangle srcRect = { 0, 0, (float)sk.texture.width, (float)sk.texture.height };
            DrawTexturePro(sk.texture, srcRect, slotRect, { 0, 0 }, 0.0f, WHITE);
        } else {
            DrawRectangleRec(slotRect, Color{ 26, 32, 52, 220 });
            DrawRectangleLinesEx(slotRect, 1.0f, NavyPanelBorder());
        }

        if(sk.showLife){
            float badgeRadius = slotH * 0.28f;
            Vector2 badgeCenter = { slotRect.x + slotRect.width - badgeRadius * 0.6f, slotRect.y + badgeRadius * 0.6f };
            DrawLifeBadge(badgeCenter, sk.currentHP, badgeRadius);
        }
    }

    return area;
}

// End Turn button + "ACTION" label + one dot per action point, centered as a block
Rectangle GamePage :: DrawActionBar(Rectangle area, Font labelFont, int actionsRemaining, Rectangle &outEndTurnBtn){
    Rectangle inset = { area.x + 4, area.y + 4, area.width - 8, area.height - 8 };
    DrawFramedPanel(inset, NavyPanelBg());

    float btnW = area.width * 0.8f;
    float btnH = area.height * 0.17f;

    const char *label = "ACTION";
    float labelFontSize = area.width * 0.15f;
    Vector2 labelSize = MeasureTextEx(labelFont, label, labelFontSize, 1.0f);

    float dotRadius = area.width * 0.095f;
    float gapAfterBtn = area.height * 0.09f;
    float gapAfterLabel = 14.0f;

    float blockH = btnH + gapAfterBtn + labelSize.y + gapAfterLabel + dotRadius * 2.0f;
    float startY = area.y + (area.height - blockH) / 2.0f;
    if(startY < area.y + area.height * 0.05f) startY = area.y + area.height * 0.05f;

    Rectangle endTurnBtn = { area.x + area.width / 2 - btnW / 2, startY, btnW, btnH };
    DrawThemedButton(endTurnBtn, "END TURN", labelFont, btnH * 0.45f, true);
    outEndTurnBtn = endTurnBtn;

    float labelY = endTurnBtn.y + endTurnBtn.height + gapAfterBtn;
    DrawTextEx(labelFont, label, { area.x + area.width / 2 - labelSize.x / 2, labelY }, labelFontSize, 1.0f, TextMuted());

    // exactly 'actionsRemaining' dots are drawn - no separate max, no empty/unfilled dots
    float gap = dotRadius * 2.8f;
    float totalWidth = gap * (actionsRemaining > 0 ? actionsRemaining - 1 : 0);
    float startX = area.x + area.width / 2 - totalWidth / 2;
    float dotY = labelY + labelSize.y + gapAfterLabel + dotRadius;

    for(int i = 0; i < actionsRemaining; ++i){
        Vector2 center = { startX + i * gap, dotY };
        DrawCircleV(center, dotRadius * 1.6f, GoldGlow());
        DrawCircleV(center, dotRadius, Gold());
        DrawCircleLines((int)center.x, (int)center.y, dotRadius, GoldBright());
    }

    return area;
}

// Maneuver / Attack / Scheme buttons, centered with divider lines above/below
void GamePage :: DrawManeuverAttackScheme(Rectangle area, Font labelFont, Rectangle &outManeuver, Rectangle &outAttack, Rectangle &outScheme){
    Rectangle inset = { area.x + 4, area.y + 4, area.width - 8, area.height - 8 };
    DrawFramedPanel(inset, NavyPanelBg());

    const char *labels[3] = { "MANEUVER", "ATTACK", "SCHEME" };
    Rectangle *outs[3] = { &outManeuver, &outAttack, &outScheme };

    float sidePad = area.width * 0.07f;
    float gap = area.width * 0.05f;
    float btnW = (area.width - sidePad * 2 - gap * 2) / 3.0f;
    float btnH = area.height * 0.5f;
    float btnY = area.y + area.height / 2 - btnH / 2;

    for(int i = 0; i < 3; ++i){
        Rectangle btnRect = { area.x + sidePad + i * (btnW + gap), btnY, btnW, btnH };
        DrawThemedButton(btnRect, labels[i], labelFont, btnH * 0.14f, false);
        *outs[i] = btnRect;
    }

    float lineW = area.width * 0.55f;
    DrawCenteredDivider(area.x + area.width / 2, btnY - area.height * 0.14f, lineW, GoldDim());
    DrawCenteredDivider(area.x + area.width / 2, btnY + btnH + area.height * 0.14f, lineW, GoldDim());
}

void GamePage :: Init(const std::string &fontPath){
    cardViewWindow = std::make_unique<CardViewWindow>(fontPath, 32);
    deckWindow = std::make_unique<DeckCardWindow>(fontPath, 32);
}

// handles hand-card clicks (opens CardViewWindow) and deck/discard button
// clicks (opens DeckCardWindow); skipped while either window is already open
void GamePage :: Update(int &handCardClicked){
    handCardClicked = -1;

    if(cardViewWindow->IsOpen() || deckWindow->IsOpen()){
        cardViewWindow->Update();
        deckWindow->Update();
        return;
    }

    Vector2 mouse = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if(CheckCollisionPointRec(mouse, leftDeckBtn))          deckWindow->Open(leftDeckCards);
        else if(CheckCollisionPointRec(mouse, leftDiscardBtn))  deckWindow->Open(leftDiscardCards);
        else if(CheckCollisionPointRec(mouse, rightDeckBtn))    deckWindow->Open(rightDeckCards);
        else if(CheckCollisionPointRec(mouse, rightDiscardBtn)) deckWindow->Open(rightDiscardCards);
    }

    handMenu.Update(CP_CARD_WIDTH * 0.6f, CP_CARD_HEIGHT * 0.6f, handCardClicked);
    if(handCardClicked != -1)
        cardViewWindow->Open(handMenu.cards[handCardClicked].texture);
}

// top-level composition: lays out every region for one frame
void GamePage :: Draw(Texture2D background, Font titleFont, Font labelFont, Texture2D mapTexture, HeroPanelData &leftHero, HeroPanelData &rightHero, const char *turnLabel, int actionsRemaining){
    int sw = GetScreenWidth();
    int sh = GetScreenHeight();

    ClearBackground(NavyBackground());

    if(background.id != 0){
        DrawTexturePro(background, { 0, 0, (float)background.width, (float)background.height }, { 0, 0, (float)sw, (float)sh }, { 0, 0 }, 0.0f, WHITE);
        DrawRectangle(0, 0, sw, sh, NavyOverlay());
    }

    // top region: hero panels either side, map fills the rest
    float topHeight = sh * 0.68f;
    float heroPanelWidth = sw * 0.14f;

    Rectangle leftPanelArea = { 0, 0, heroPanelWidth, topHeight };
    Rectangle rightPanelArea = { sw - heroPanelWidth, 0, heroPanelWidth, topHeight };
    Rectangle mapArea = { heroPanelWidth, 0, sw - heroPanelWidth * 2, topHeight };

    // turn banner: framed ribbon with diamond accents
    float turnFontSize = topHeight * 0.04f;
    Vector2 turnSize = MeasureTextEx(titleFont, turnLabel, turnFontSize, 2.0f);

    float bannerPadX = turnSize.x * 0.35f;
    float bannerH = turnSize.y * 1.9f;
    Rectangle banner = { mapArea.x + mapArea.width / 2 - (turnSize.x + bannerPadX * 2) / 2, topHeight * 0.015f, turnSize.x + bannerPadX * 2, bannerH };

    DrawRectangleRec({ banner.x + 2, banner.y + 3, banner.width, banner.height }, NavyShadow());
    DrawRectangleRec(banner, NavyPanelBg());
    DrawRectangleLinesEx(banner, 2.0f, GoldDim());
    DrawRectangleLinesEx({ banner.x + 3, banner.y + 3, banner.width - 6, banner.height - 6 }, 1.0f, Gold());

    float diamondSize = bannerH * 0.2f;
    DrawDiamondAccent({ banner.x - diamondSize * 1.4f, banner.y + banner.height / 2 }, diamondSize, Gold());
    DrawDiamondAccent({ banner.x + banner.width + diamondSize * 1.4f, banner.y + banner.height / 2 }, diamondSize, Gold());
    DrawTextEx(titleFont, turnLabel, { banner.x + banner.width / 2 - turnSize.x / 2, banner.y + banner.height / 2 - turnSize.y / 2 }, turnFontSize, 2.0f, GoldBright());

    Rectangle mapDrawArea = { mapArea.x, banner.y + banner.height + 8.0f, mapArea.width, mapArea.height - (banner.y + banner.height + 8.0f) };

    DrawHeroPanel(leftPanelArea, leftHero, titleFont, labelFont, false, leftDeckBtn, leftDiscardBtn);
    lastMapRect = DrawMap(mapDrawArea, mapTexture);
    DrawHeroPanel(rightPanelArea, rightHero, titleFont, labelFont, true, rightDeckBtn, rightDiscardBtn);

    // bottom region: buttons | action | hand
    float bottomY = topHeight;
    float bottomHeight = sh - topHeight;

    float actionBarWidth = sw * 0.12f;
    float buttonsWidth = sw * 0.24f;
    float handWidth = sw - actionBarWidth - buttonsWidth;

    Rectangle buttonsArea = { 0, bottomY, buttonsWidth, bottomHeight };
    Rectangle actionArea = { buttonsWidth, bottomY, actionBarWidth, bottomHeight };
    Rectangle handArea = { buttonsWidth + actionBarWidth, bottomY, handWidth, bottomHeight };

    DrawManeuverAttackScheme(buttonsArea, labelFont, maneuverBtn, attackBtn, schemeBtn);
    DrawActionBar(actionArea, labelFont, actionsRemaining, endTurnBtn);

    // hand panel: cards auto-scale down if they'd overflow the panel
    Rectangle handPanel = { handArea.x + 4, handArea.y + 4, handArea.width - 8, handArea.height - 8 };
    DrawFramedPanel(handPanel, NavyPanelBg());

    const char *handLabel = "HAND";
    float handLabelFontSize = handPanel.height * 0.06f;
    Vector2 handLabelSize = MeasureTextEx(labelFont, handLabel, handLabelFontSize, 2.0f);
    DrawTextEx(labelFont, handLabel, { handPanel.x + handPanel.width / 2 - handLabelSize.x / 2, handPanel.y + handPanel.height * 0.035f }, handLabelFontSize, 2.0f, TextMuted());

    float innerPadX = handPanel.width * 0.03f;
    Rectangle handContent = {
        handPanel.x + innerPadX, handPanel.y + handLabelSize.y + handPanel.height * 0.06f,
        handPanel.width - innerPadX * 2, handPanel.height - (handLabelSize.y + handPanel.height * 0.09f)
    };

    float handCardW = CP_CARD_WIDTH * 0.6f;
    float handCardH = CP_CARD_HEIGHT * 0.6f;
    int cardCount = handMenu.count;

    if(handCardH > handContent.height){
        float s = handContent.height / handCardH;
        handCardW *= s; handCardH *= s;
    }

    float overlap = handCardW * 0.4f;
    float totalWidth = handCardW + overlap * (cardCount > 0 ? cardCount - 1 : 0);
    if(totalWidth > handContent.width && cardCount > 1){
        float s = handContent.width / totalWidth;
        handCardW *= s; handCardH *= s;
    }

    if(!handMenu.expanded){
        handMenu.anchor = {
            handContent.x + handContent.width / 2 - handCardW / 2 - (cardCount > 0 ? (cardCount - 1) * 2.0f : 0.0f),
            handContent.y + handContent.height / 2 - handCardH / 2 + (cardCount > 0 ? (cardCount - 1) * 2.0f : 0.0f),
            handCardW, handCardH
        };
    } else {
        float overlapFinal = handCardW * 0.4f;
        float totalWidthFinal = handCardW + overlapFinal * (cardCount > 0 ? cardCount - 1 : 0);
        handMenu.anchor = {
            handContent.x + handContent.width / 2 - totalWidthFinal / 2,
            handContent.y + handContent.height / 2 - handCardH / 2,
            handCardW, handCardH
        };
    }

    handMenu.Draw(handCardW, handCardH);
}

// thin phosphor-green ring around one board space, positioned off lastMapRect;
// call after Draw() so the map rect for this frame is already known
void GamePage :: HighlightSpace(int spaceIndex){
    if(spaceIndex < 0 || spaceIndex >= GP_SPACE_COUNT) return;
    if(lastMapRect.width <= 0.0f || lastMapRect.height <= 0.0f) return;

    Vector2 norm = kSpaceCenterNorm[spaceIndex];
    Vector2 center = { lastMapRect.x + norm.x * lastMapRect.width, lastMapRect.y + norm.y * lastMapRect.height };

    float radius = GP_SPACE_RADIUS_NORM * lastMapRect.width;
    float thickness = fmax(1.0f, radius * 0.045f);

    DrawRing(center, radius - thickness * 2.80f, radius + thickness * 2.0f, 0.0f, 360.0f, 48, PhosphorGreenGlow());
    DrawRing(center, radius - thickness * 2.80f, radius + thickness * 1.3f, 0.0f, 360.0f, 48, PhosphorGreen());
}

// same ring, applied to every index in 'spaceIndices' (e.g. all reachable spaces)
void GamePage :: HighlightSpaces(const std::vector<int> &spaceIndices){
    for(int index : spaceIndices) HighlightSpace(index);
}