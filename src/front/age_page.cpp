#include "front/age_page.h"

bool AgePage :: DrawMenuButton(MenuButton& btn, Rectangle rect, Font font,Vector2 mousePos, bool mouseDown)
{
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