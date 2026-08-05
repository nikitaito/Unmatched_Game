#include "front/main_menu.h"

void Menu :: DrawMenuButton(MenuButton& btn, Rectangle rect, Font font,Vector2 mousePos, bool mouseDown){
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

bool Menu :: is_clicked(Rectangle rect , Vector2 mousePos){
    bool hover = CheckCollisionPointRec(mousePos, rect);
    return hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Menu :: make_Page(Page & current_page, Texture2D & background,Font & titleFont, Font & subtitleFont, Font & buttonFont){

    Color overlayColor  = { 0, 0, 0, 150 };
    Color goldColor     = { 212, 175, 90, 255 };
    Color subtitleColor = { 170, 150, 110, 255 };

    Color startBg          = { 120, 15, 15, 255 };
    Color startHoverBg     = { 150, 25, 20, 255 };
    Color startPressBg     = { 90, 10, 10, 255 };
    Color startBorder      = { 200, 60, 40, 255 };
    Color startHoverBorder = { 255, 120, 90, 255 };

    Color panelBg          = { 20, 22, 28, 200 };
    Color panelHoverBg     = { 38, 40, 48, 220 };
    Color panelPressBg     = { 10, 12, 16, 220 };
    Color panelBorder      = { 70, 70, 80, 255 };
    Color panelHoverBorder = { 160, 160, 170, 255 };

    Color textWhite = RAYWHITE;
    Color textGray  = { 200, 200, 205, 255 };

    MenuButton startBtn = { "START", 30, startBg, startHoverBg, startPressBg,
                            startBorder, startHoverBorder, textWhite, textWhite };
    MenuButton loadBtn  = { "LOAD GAME", 26, panelBg, panelHoverBg, panelPressBg,
                            panelBorder, panelHoverBorder, textGray, textWhite };
    MenuButton exitBtn  = { "EXIT", 26, panelBg, panelHoverBg, panelPressBg,
                            panelBorder, panelHoverBorder, textGray, textWhite };

    while (!WindowShouldClose())
    {
        int sw = GetScreenWidth();
        int sh = GetScreenHeight();
        int centerX = sw / 2;

        float buttonWidth  = sw * 0.32f;
        float buttonHeight = sh * 0.07f;
        float gap          = sh * 0.02f;
        float startY       = sh * 0.50f;

        Rectangle startRect = { centerX - buttonWidth / 2, startY, buttonWidth, buttonHeight };
        Rectangle loadRect  = { centerX - buttonWidth / 2, startY + (buttonHeight + gap), buttonWidth, buttonHeight };
        Rectangle exitRect  = { centerX - buttonWidth / 2, startY + (buttonHeight + gap) * 2, buttonWidth, buttonHeight };

        Vector2 mousePos = GetMousePosition();
        bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        bool anyHover =
            CheckCollisionPointRec(mousePos, startRect) ||
            CheckCollisionPointRec(mousePos, loadRect) ||
            CheckCollisionPointRec(mousePos, exitRect);

        SetMouseCursor(anyHover ? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_DEFAULT);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(background,
            { 0, 0, (float)background.width, (float)background.height },
            { 0, 0, (float)sw, (float)sh },
            { 0, 0 }, 0.0f, WHITE);

        DrawRectangle(0, 0, sw, sh, overlayColor);

        const char* subtitle = "THE ETERNAL BATTLE OF SHADOWS";
        float subFontSize = sh * 0.022f;
        Vector2 subSize = MeasureTextEx(subtitleFont, subtitle, subFontSize, 4.0f);
        DrawTextEx(subtitleFont, subtitle, { centerX - subSize.x / 2, sh * 0.24f }, subFontSize, 4.0f, subtitleColor);

        const char* title = "UNMATCHED";
        float titleFontSize = sh * 0.11f;
        Vector2 titleSize = MeasureTextEx(titleFont, title, titleFontSize, 2.0f);
        DrawTextEx(titleFont, title, { centerX - titleSize.x / 2, sh * 0.28f }, titleFontSize, 2.0f, goldColor);

        DrawMenuButton(startBtn, startRect, buttonFont, mousePos, mouseDown);
        DrawMenuButton(loadBtn, loadRect, buttonFont, mousePos, mouseDown);
        DrawMenuButton(exitBtn, exitRect, buttonFont, mousePos, mouseDown);

        EndDrawing();

        if(is_clicked(startRect , mousePos)){
            current_page = Page :: Age;
            break;
        }
        else if(is_clicked(loadRect , mousePos)){
            current_page = Page :: Help;
            break;
        }
        else if(is_clicked (exitRect , mousePos)){
            current_page = Page :: Exit;
            break;
        }
    }

    if (WindowShouldClose())
    {
        current_page = Page::Exit;
    }

}
