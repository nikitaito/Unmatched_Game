#include "handmenu.h"
#include "cp_colors.h"

Rectangle CPHandMenu ::CardRect(int index, float cardW, float cardH) const{
    if (!expanded) {
        float offset = index * 4.0f;
        return Rectangle{ anchor.x + offset, anchor.y - offset, cardW, cardH };
    }

    /* expanded: fan out horizontally, overlapping */
    float spacing = cardW * 0.4f;
    return Rectangle{ anchor.x + index * spacing, anchor.y, cardW, cardH };
}

void CPHandMenu :: Update(float cardW, float cardH, int &clickedOut){
    clickedOut = -1;
    hoveredIndex = -1;
    if (count <= 0) return;

    Vector2 mouse = GetMousePosition();
    bool leftClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (!expanded) {
        /* collapsed: the whole stack acts as one clickable area -> expands it */
        Rectangle stackRect = CardRect(count - 1, cardW, cardH);
        if (CheckCollisionPointRec(mouse, stackRect)) {
            hoveredIndex = count - 1;
            if (leftClicked) expanded = true;
        }
        return;
    }

    /* expanded: check top-most drawn card first so overlaps resolve correctly */
    for (int i = count - 1; i >= 0; i--) {
        Rectangle r = CardRect(i, cardW, cardH);
        if (CheckCollisionPointRec(mouse, r)) {
            hoveredIndex = i;
            if (leftClicked) {
                clickedOut = i;
                expanded = false; /* picking a card also collapses the fan */
            }
            break;
        }
    }

    /* clicking anywhere else while expanded collapses it back */
    if (leftClicked && hoveredIndex == -1) expanded = false;
}

void CPHandMenu :: Draw(float cardW, float cardH) const{
    for (int i = 0; i < count; i++) {
        Rectangle r = CardRect(i, cardW, cardH);
        const CPHandCard &card = cards[i];

        /* soft drop shadow for a bit of depth against the background art */
        Rectangle shadow{ r.x + 4, r.y + 5, r.width, r.height };
        DrawRectangleRounded(shadow, 0.08f, 6, Fade(BLACK, 0.35f));

        if (card.texture.id > 0) {
            /* draw the real card face, stretched/fit into r */
            Rectangle src{ 0, 0, (float)card.texture.width, (float)card.texture.height };
            DrawTexturePro(card.texture, src, r, Vector2{ 0, 0 }, 0.0f, WHITE);

            /* hover highlight as an outline on top of the texture */
            Color outline = (i == hoveredIndex) ? CPColors::CardHover : CPColors::CardBorder;
            DrawRectangleLinesEx(r, (i == hoveredIndex) ? 3.0f : 1.0f, outline);
        } else {
            /* fallback placeholder while no texture is assigned yet */
            Color col = (i == hoveredIndex) ? CPColors::CardHover : CPColors::CardFill;
            DrawRectangleRounded(r, 0.08f, 6, col);
            DrawRectangleRoundedLinesEx(r, 0.08f, 6, 2, CPColors::CardBorder);
        }
    }
}