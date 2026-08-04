
#ifndef MAIN_MENU
#define MAIN_MENU

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

class menu
{
    private:
        void DrawMenuButton(MenuButton&, Rectangle, Font,Vector2, bool);
    public:
        void make_Page();

};



#endif 
