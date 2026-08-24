#ifndef HAND_H
#define HAND_H
#include "raylib.h"
#include "Enums.h"
#include <array>
#include <string>

constexpr float CP_CARD_WIDTH  = 250.0f;
constexpr float CP_CARD_HEIGHT = 349.0f;
constexpr int   CP_MAX_HAND    = 20;


struct CPHandCard {
    int cardId = -1; 
    Texture2D texture{};  
    int hasTexture ;  

    std::string name;
    std::string statLine;
    CardType    type = CardType::EVENT;
    bool disabled = false; 
};


class CPHandMenu {
    public:
        std::array<CPHandCard, CP_MAX_HAND> cards{};
        int count = 0;

        bool expanded = false; 
        Rectangle anchor{};        

        int hoveredIndex = -1;     

        Rectangle CardRect(int index, float cardW, float cardH) const;
        void Update(float cardW, float cardH, int &clickedOut);

        void Draw(float cardW, float cardH) const;
};

#endif