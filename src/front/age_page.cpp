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

