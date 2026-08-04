
#ifndef MAIN_MENU
#define MAIN_MENU

#include "Enums.h"
#include "raylib.h"

struct MenuButton
{
    const char* text;
    int fontSize;
    Color idleBg;
    Color hoverBg;
    Color pressBg;
    Color idleBorder;
    Color hoverBorder;
    Color idleText;
    Color hoverText;
};

class Menu
{
    private:
        Texture2D background = LoadTexture("../../assets/background.png");
        Font titleFont    = LoadFontEx("../../assets/Cinzel-Bold.ttf", 128, 0, 0);
        Font subtitleFont = LoadFontEx("../../assets/Cinzel-Bold.ttf", 64, 0, 0);
        Font buttonFont   = LoadFontEx("../../assets/Cinzel-SemiBold.ttf", 64, 0, 0);

        void DrawMenuButton(MenuButton&, Rectangle, Font,Vector2, bool);
        bool is_clicked(Rectangle  , Vector2 );
    public:
        void make_Page(Page &);


};



#endif 
