#include "handmenu.h"
#include "cp_colors.h"

namespace
{
    Color FillForType(CardType type){
        switch(type){
            case CardType::ATTACK:  return Color{ 92, 24, 24, 255 };
            case CardType::DEFENSE: return Color{ 22, 40, 78, 255 };
            case CardType::BOTH:    return Color{ 58, 30, 82, 255 };
            case CardType::EVENT:   return Color{ 92, 76, 18, 255 };
        }
        return CPColors::CardFill;
    }
    Color BorderForType(CardType type){
        switch(type){
            case CardType::ATTACK:  return Color{ 214, 90, 80, 255 };
            case CardType::DEFENSE: return Color{ 110, 160, 220, 255 };
            case CardType::BOTH:    return Color{ 190, 120, 230, 255 };
            case CardType::EVENT:   return Color{ 226, 196, 90, 255 };
        }
        return CPColors::CardBorder;
    }
}

Rectangle CPHandMenu ::CardRect(int index, float cardW, float cardH) const{
    if (!expanded) {
        float offset = index * 4.0f;
        return Rectangle{ anchor.x + offset, anchor.y - offset, cardW, cardH };
    }

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
        Rectangle stackRect = CardRect(count - 1, cardW, cardH);
        if (CheckCollisionPointRec(mouse, stackRect)) {
            hoveredIndex = count - 1;
            if (leftClicked) expanded = true;
        }
        return;
    }

    for (int i = count - 1; i >= 0; i--) {
        Rectangle r = CardRect(i, cardW, cardH);
        if (CheckCollisionPointRec(mouse, r)) {
            hoveredIndex = i;
            if (leftClicked && !cards[i].disabled) {
                clickedOut = i;
                expanded = false; 
            }
            break;
        }
    }

    if (leftClicked && hoveredIndex == -1) expanded = false;
}

void CPHandMenu :: Draw(float cardW, float cardH) const{
    for (int i = 0; i < count; i++) {
        Rectangle r = CardRect(i, cardW, cardH);
        const CPHandCard &card = cards[i];

        Rectangle shadow{ r.x + 4, r.y + 5, r.width, r.height };
        DrawRectangleRounded(shadow, 0.08f, 6, Fade(BLACK, 0.35f));

        if (card.texture.id > 0) {

            Rectangle src{ 0, 0, (float)card.texture.width, (float)card.texture.height };
            DrawTexturePro(card.texture, src, r, Vector2{ 0, 0 }, 0.0f, WHITE);

            Color outline = (i == hoveredIndex) ? CPColors::CardHover : CPColors::CardBorder;
            DrawRectangleLinesEx(r, (i == hoveredIndex) ? 3.0f : 1.0f, outline);
        } else {

            Color fill = FillForType(card.type);
            Color border = (i == hoveredIndex) ? CPColors::CardHover : BorderForType(card.type);
            DrawRectangleRounded(r, 0.08f, 6, fill);
            DrawRectangleRoundedLinesEx(r, 0.08f, 6, 2, border);

            float pad = r.width * 0.08f;
            float nameFontSize = r.width * 0.11f;
            Font font = GetFontDefault();
            Rectangle textArea{ r.x + pad, r.y + pad, r.width - pad * 2, r.height - pad * 2 };

            std::string remaining = card.name;
            float lineY = textArea.y;
            while(!remaining.empty() && lineY < textArea.y + textArea.height * 0.6f){
                size_t fit = remaining.size();
                while(fit > 0 && MeasureTextEx(font, remaining.substr(0, fit).c_str(), nameFontSize, 1.0f).x > textArea.width)
                    fit--;
                if(fit < remaining.size()){
                    size_t breakAt = remaining.rfind(' ', fit);
                    if(breakAt != std::string::npos && breakAt > 0)
                        fit = breakAt;
                }
                std::string line = remaining.substr(0, fit);
                DrawTextEx(font, line.c_str(), { textArea.x, lineY }, nameFontSize, 1.0f, RAYWHITE);
                lineY += nameFontSize * 1.15f;
                remaining = (fit < remaining.size()) ? remaining.substr(remaining[fit] == ' ' ? fit + 1 : fit) : "";
            }

            float statFontSize = r.width * 0.08f;
            DrawTextEx(font, card.statLine.c_str(), { textArea.x, textArea.y + textArea.height - statFontSize }, statFontSize, 1.0f, Color{ 225, 220, 210, 255 });

            if(card.disabled)
                DrawRectangleRounded(r, 0.08f, 6, Fade(BLACK, 0.55f));
        }
    }
}