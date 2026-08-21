#include "front/age_page.h"

bool AgePage :: DrawMenuButton(MenuButton& btn, Rectangle rect, Font font,Vector2 mousePos, bool mouseDown){
    bool hover = CheckCollisionPointRec(mousePos, rect);
    bool clicked = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

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

    return clicked;
}

bool AgePage :: DrawNumberInput(Rectangle rect, char* buffer, int maxLen, bool isActive, Font font, Vector2 mousePos, Color bgColor, Color activeBorder, Color idleBorder, Color textColor, Color placeholderColor){
    bool hover = CheckCollisionPointRec(mousePos, rect);
    bool clicked = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    DrawRectangleRounded(rect, 0.1f, 6, bgColor);
    DrawRectangleRoundedLines(rect, 0.1f, 6, isActive ? activeBorder : idleBorder);

    int len = (int)strlen(buffer);
    float fontSize = rect.height * 0.4f;

    if (len == 0 && !isActive)
    {
        const char* placeholder = "Enter age";
        Vector2 size = MeasureTextEx(font, placeholder, fontSize, 1.0f);
        Vector2 pos = { rect.x + rect.width / 2 - size.x / 2, rect.y + rect.height / 2 - size.y / 2 };
        DrawTextEx(font, placeholder, pos, fontSize, 1.0f, placeholderColor);
    }
    else
    {
        Vector2 size = MeasureTextEx(font, buffer, fontSize, 1.0f);
        Vector2 pos = { rect.x + rect.width / 2 - size.x / 2, rect.y + rect.height / 2 - size.y / 2 };
        DrawTextEx(font, buffer, pos, fontSize, 1.0f, textColor);

        if (isActive && (int)(GetTime() * 2) % 2 == 0)
        {
            float cursorX = pos.x + size.x + 4;
            DrawLine((int)cursorX, (int)(rect.y + rect.height * 0.25f),
                     (int)cursorX, (int)(rect.y + rect.height * 0.75f), textColor);
        }
    }

    return clicked;
}

void AgePage :: Make_Page(Page & current_page ,Texture2D & background, Font & titleFont, Font & labelFont, int & age1 , int & age2){

    Color overlayColor = { 0, 0, 0, 190 };
    Color goldColor    = { 212, 175, 90, 255 };

    Color dialogBg          = { 18, 20, 27, 235 };
    Color dialogBorder      = { 170, 140, 80, 255 };
    Color creamColor        = { 230, 222, 205, 255 };
    Color labelGold         = { 195, 165, 90, 255 };
    Color inputBg           = { 10, 12, 16, 255 };
    Color inputIdleBorder   = { 60, 62, 70, 255 };
    Color inputActiveBorder = { 200, 165, 80, 255 };
    Color placeholderGray   = { 130, 132, 138, 255 };
    Color textWhite         = RAYWHITE;
    Color textGray          = { 200, 200, 205, 255 };

    Color panelBg          = { 20, 22, 28, 200 };
    Color panelHoverBg     = { 38, 40, 48, 220 };
    Color panelPressBg     = { 10, 12, 16, 220 };
    Color panelBorder      = { 70, 70, 80, 255 };
    Color panelHoverBorder = { 160, 160, 170, 255 };

    Color okBg          = { 200, 165, 80, 255 };
    Color okHoverBg     = { 215, 180, 95, 255 };
    Color okPressBg     = { 175, 140, 60, 255 };
    Color okBorder      = { 200, 165, 80, 255 };
    Color okHoverBorder = { 230, 200, 120, 255 };
    Color okTextColor   = { 25, 20, 10, 255 };

    MenuButton okBtn      = { "OK", 26, okBg, okHoverBg, okPressBg,
                              okBorder, okHoverBorder, okTextColor, okTextColor };
    MenuButton retreatBtn = { "RETREAT", 26, panelBg, panelHoverBg, panelPressBg,
                              panelBorder, panelHoverBorder, textGray, textWhite };

    ActiveField activeField = FIELD_NONE;
    char player1Age[4] = "";
    char player2Age[4] = "";

    while (!WindowShouldClose())
    {
        int sw = GetScreenWidth();
        int sh = GetScreenHeight();
        int centerX = sw / 2;

        Vector2 mousePos = GetMousePosition();
        bool mouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(background,
            { 0, 0, (float)background.width, (float)background.height },
            { 0, 0, (float)sw, (float)sh },
            { 0, 0 }, 0.0f, WHITE);
        DrawRectangle(0, 0, sw, sh, overlayColor);

        float panelWidth  = sw * 0.34f;
        float panelHeight = sh * 0.62f;
        Rectangle panelRect = { centerX - panelWidth / 2, sh * 0.18f, panelWidth, panelHeight };

        DrawRectangleRounded(panelRect, 0.06f, 10, dialogBg);
        DrawRectangleRoundedLines(panelRect, 0.06f, 10, dialogBorder);

        float contentX = panelRect.x + panelWidth * 0.08f;
        float contentWidth = panelWidth * 0.84f;

        const char* titleLine1 = "ASSESSMENT OF";
        const char* titleLine2 = "MORTALITY";
        float dialogTitleSize = sh * 0.045f;

        Vector2 t1Size = MeasureTextEx(titleFont, titleLine1, dialogTitleSize, 2.0f);
        Vector2 t2Size = MeasureTextEx(titleFont, titleLine2, dialogTitleSize, 2.0f);

        float titleY = panelRect.y + panelHeight * 0.10f;
        DrawTextEx(titleFont, titleLine1, { centerX - t1Size.x / 2, titleY }, dialogTitleSize, 2.0f, creamColor);
        DrawTextEx(titleFont, titleLine2, { centerX - t2Size.x / 2, titleY + dialogTitleSize * 1.05f }, dialogTitleSize, 2.0f, goldColor);

        float dividerY = titleY + dialogTitleSize * 2.3f;
        DrawLine((int)(centerX - panelWidth * 0.08f), (int)dividerY,
                 (int)(centerX + panelWidth * 0.08f), (int)dividerY, goldColor);

        float labelSize = sh * 0.018f;
        float fieldHeight = sh * 0.07f;
        float sectionY = dividerY + sh * 0.05f;

        DrawTextEx(labelFont, "LIFE CYCLE OF PLAYER 1:", { contentX, sectionY }, labelSize, 2.0f, labelGold);
        Rectangle player1Rect = { contentX, sectionY + labelSize * 1.6f, contentWidth, fieldHeight };
        bool p1Clicked = DrawNumberInput(player1Rect, player1Age, 3, activeField == FIELD_PLAYER1,
                                         labelFont, mousePos, inputBg, inputActiveBorder, inputIdleBorder,
                                         textWhite, placeholderGray);

        float section2Y = player1Rect.y + fieldHeight + sh * 0.045f;
        DrawTextEx(labelFont, "LIFE CYCLE OF PLAYER 2:", { contentX, section2Y }, labelSize, 2.0f, labelGold);
        Rectangle player2Rect = { contentX, section2Y + labelSize * 1.6f, contentWidth, fieldHeight };
        bool p2Clicked = DrawNumberInput(player2Rect, player2Age, 3, activeField == FIELD_PLAYER2,
                                         labelFont, mousePos, inputBg, inputActiveBorder, inputIdleBorder,
                                         textWhite, placeholderGray);

        float buttonsY = player2Rect.y + fieldHeight + sh * 0.06f;
        float okWidth = contentWidth * 0.62f;
        float retreatWidth = contentWidth * 0.32f;
        float buttonsGap = contentWidth * 0.06f;

        Rectangle okRect = { contentX, buttonsY, okWidth, fieldHeight };
        Rectangle retreatRect = { contentX + okWidth + buttonsGap, buttonsY, retreatWidth, fieldHeight };

        bool anyHover =
            CheckCollisionPointRec(mousePos, player1Rect) ||
            CheckCollisionPointRec(mousePos, player2Rect) ||
            CheckCollisionPointRec(mousePos, okRect) ||
            CheckCollisionPointRec(mousePos, retreatRect);
        SetMouseCursor(anyHover ? MOUSE_CURSOR_POINTING_HAND : MOUSE_CURSOR_DEFAULT);

        bool okClicked = DrawMenuButton(okBtn, okRect, labelFont, mousePos, mouseDown);
        bool retreatClicked = DrawMenuButton(retreatBtn, retreatRect, labelFont, mousePos, mouseDown);

        if (p1Clicked) activeField = FIELD_PLAYER1;
        else if (p2Clicked) activeField = FIELD_PLAYER2;
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                 !CheckCollisionPointRec(mousePos, okRect) &&
                 !CheckCollisionPointRec(mousePos, retreatRect))
        {
            activeField = FIELD_NONE;
        }

        if (activeField != FIELD_NONE)
        {
            char* activeBuffer = (activeField == FIELD_PLAYER1) ? player1Age : player2Age;
            int len = (int)strlen(activeBuffer);

            int key = GetCharPressed();
            while (key > 0)
            {
                if (key >= '0' && key <= '9' && len < 3)
                {
                    activeBuffer[len] = (char)key;
                    activeBuffer[len + 1] = '\0';
                    len++;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && len > 0)
            {
                activeBuffer[len - 1] = '\0';
            }
        }

        if (okClicked){
            current_page = Page :: Choose;
            age1 = atoi(player1Age);
            age2 = atoi(player2Age);
        }
        if (retreatClicked) {current_page = Page :: Menu;}

        EndDrawing();

        if (okClicked || retreatClicked) break;
    }

    if (WindowShouldClose())
    {
        current_page = Page::Exit;
    }

}
