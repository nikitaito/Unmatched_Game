#include "front/end_page.h"

void EndPage :: DrawMenuButton(MenuButton& btn, Rectangle rect, Font font, Vector2 mousePos, bool mouseDown){
    bool hover = CheckCollisionPointRec(mousePos, rect);

    Color bg = btn.idleBg;
    Color border = btn.idleBorder;
    Color textColor = btn.idleText;

    if (hover)
    {
        bg = mouseDown ? btn.pressBg : btn.hoverBg;
        border = btn.hoverBorder;
        textColor = btn.hoverText;
    }

    DrawRectangleRounded(rect, 0.15f, 8, bg);
    DrawRectangleRoundedLines(rect, 0.15f, 8, border);

    Vector2 textSize = MeasureTextEx(font, btn.text, (float)btn.fontSize, 2.0f);
    Vector2 textPos = {
        rect.x + rect.width / 2 - textSize.x / 2,
        rect.y + rect.height / 2 - textSize.y / 2
    };
    DrawTextEx(font, btn.text, textPos, (float)btn.fontSize, 2.0f, textColor);
}

bool EndPage :: is_clicked(Rectangle rect , Vector2 mousePos){
    bool hover = CheckCollisionPointRec(mousePos, rect);
    return hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void EndPage :: Make_Page(Page & current_page, Texture2D & background, Font & titleFont,
                           Font & subtitleFont, Font & buttonFont,
                           const std :: string & resultLine, const std :: string & detailLine){

    Color overlayColor  = { 0, 0, 0, 175 };
    Color goldColor     = { 212, 175, 90, 255 };
    Color subtitleColor = { 225, 210, 180, 255 };
    Color detailColor   = { 170, 150, 110, 255 };

    Color panelBg          = { 20, 22, 28, 200 };
    Color panelHoverBg     = { 38, 40, 48, 220 };
    Color panelPressBg     = { 10, 12, 16, 220 };
    Color panelBorder      = { 70, 70, 80, 255 };
    Color panelHoverBorder = { 160, 160, 170, 255 };

    Color textGray  = { 200, 200, 205, 255 };

    MenuButton exitBtn = { "EXIT", 26, panelBg, panelHoverBg, panelPressBg,
                           panelBorder, panelHoverBorder, textGray, RAYWHITE };

    int sw = GetScreenWidth();
    int sh = GetScreenHeight();
    int centerX = sw / 2;

    float buttonWidth  = sw * 0.30f;
    float buttonHeight = sh * 0.075f;
    Rectangle exitRect = { centerX - buttonWidth / 2, sh * 0.68f, buttonWidth, buttonHeight };

    Vector2 mousePos = GetMousePosition();
    bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
    bool anyHover = CheckCollisionPointRec(mousePos, exitRect);
    SetMouseCursor(anyHover ? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_DEFAULT);

    ClearBackground(BLACK);

    DrawTexturePro(background,
        { 0, 0, (float)background.width, (float)background.height },
        { 0, 0, (float)sw, (float)sh },
        { 0, 0 }, 0.0f, WHITE);

    DrawRectangle(0, 0, sw, sh, overlayColor);

    const char* title = "GAME OVER";
    float titleFontSize = sh * 0.095f;
    Vector2 titleSize = MeasureTextEx(titleFont, title, titleFontSize, 2.0f);
    DrawTextEx(titleFont, title, { centerX - titleSize.x / 2, sh * 0.28f }, titleFontSize, 2.0f, goldColor);

    float resultFontSize = sh * 0.04f;
    Vector2 resultSize = MeasureTextEx(subtitleFont, resultLine.c_str(), resultFontSize, 3.0f);
    DrawTextEx(subtitleFont, resultLine.c_str(), { centerX - resultSize.x / 2, sh * 0.46f }, resultFontSize, 3.0f, subtitleColor);

    if(!detailLine.empty()){
        float detailFontSize = sh * 0.024f;
        Vector2 detailSize = MeasureTextEx(subtitleFont, detailLine.c_str(), detailFontSize, 2.0f);
        DrawTextEx(subtitleFont, detailLine.c_str(), { centerX - detailSize.x / 2, sh * 0.54f }, detailFontSize, 2.0f, detailColor);
    }

    DrawMenuButton(exitBtn, exitRect, buttonFont, mousePos, mouseDown);

    if(is_clicked(exitRect, mousePos)){
        current_page = Page :: Exit;
    }
}
