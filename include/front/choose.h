#ifndef CHOOSE_PAGE
#define CHOOSE_PAGE

#include "Enums.h"
#include "raylib.h"
#include "ui_common.h"

class ChoosePage
{
    private:
        bool DrawCharacterCard(Rectangle rect, Texture2D portrait, const char* name, const char* subtitle,Color subtitleColor, Font titleFont, Font labelFont,Vector2 mousePos, bool mouseDown, bool disabled);

        int firstPickIndex  = -1;
        int secondPickIndex = -1;

    public:
        void Make_Page(Page & current_page, Texture2D & background,
                       Font & titleFont, Font & labelFont,
                       Texture2D & draculaTex, Texture2D & invManTex, Texture2D & holmesTex,
                       int age1, int age2,
                       CharacterType & character1, CharacterType & character2);
        void Reset(); 
};

#endif
