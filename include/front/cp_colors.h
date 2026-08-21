#ifndef CP_COLORS_H
#define CP_COLORS_H

#include "raylib.h"

namespace CPColors {
    constexpr Color Background      = Color{ 15,  23,  42,  255 }; 
    constexpr Color PanelFill       = Color{ 24,  33,  58,  255 };
    constexpr Color PanelBorder     = Color{ 198, 161, 91,  255 };
 
    constexpr Color Gold            = Color{ 212, 175, 55,  255 }; 
    constexpr Color GoldLight       = Color{ 235, 205, 130, 255 }; 
 
    constexpr Color TextLight       = Color{ 235, 225, 205, 255 }; 
    constexpr Color TextOnGold      = Color{ 20,  24,  38,  255 }; 
 
    constexpr Color ButtonFill      = Color{ 35,  46,  78,  255 };
    constexpr Color ButtonHoverFill = Color{ 212, 175, 55,  255 };
    constexpr Color ButtonBorder    = Color{ 198, 161, 91,  255 };
 
    constexpr Color CardFill        = Color{ 30,  41,  68,  255 };
    constexpr Color CardHover       = Color{ 212, 175, 55,  255 };
    constexpr Color CardBorder      = Color{ 198, 161, 91,  255 };
 
    constexpr Color TextBackdrop    = Color{ 12,  18,  32,  165 }; 
    constexpr Color SlotFill        = Color{ 12,  18,  32,  90  }; 
}

#endif