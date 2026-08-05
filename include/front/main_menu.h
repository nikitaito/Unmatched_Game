#ifndef MAIN_MENU
#define MAIN_MENU

#include "Enums.h"
#include "raylib.h"
#include "ui_common.h"

class Main_Menu
{
    private:
        void DrawMenuButton(MenuButton& , Rectangle , Font , Vector2 , bool);
        bool is_clicked(Rectangle , Vector2);
    public:
        void make_Page(Page & current_page, Texture2D & background,Font & titleFont, Font & subtitleFont, Font & buttonFont);
};

#endif
