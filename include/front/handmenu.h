#ifndef HAND_H
#define HAND_H
#include "raylib.h"
#include <array>

constexpr float CP_CARD_WIDTH  = 250.0f;
constexpr float CP_CARD_HEIGHT = 349.0f;
constexpr int   CP_MAX_HAND    = 20;


struct CPHandCard {
    int       cardId = -1; /* index/id into your own card database, if you need it */
    Texture2D texture{};   /* the card's face texture, loaded elsewhere (LoadTexture) */
    int hasTexture ;  /* texture.id == 0 means "not loaded" -> placeholder is drawn instead */
};


class CPHandMenu {
    public:
        std::array<CPHandCard, CP_MAX_HAND> cards{};
        int count = 0;

        bool expanded = false; /* false = collapsed stack, true = fanned out */
        Rectangle anchor{};         /* top-left position of the (collapsed) stack */

        int hoveredIndex = -1;     

        Rectangle CardRect(int index, float cardW, float cardH) const;
        void Update(float cardW, float cardH, int &clickedOut);

        void Draw(float cardW, float cardH) const;
};

#endif