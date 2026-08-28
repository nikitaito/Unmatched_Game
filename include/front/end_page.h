#ifndef END_PAGE_H
#define END_PAGE_H

#include "Enums.h"
#include "raylib.h"
#include "ui_common.h"
#include <string>

class EndPage
{
    private:
        void DrawMenuButton(MenuButton& , Rectangle , Font , Vector2 , bool);
        bool is_clicked(Rectangle , Vector2);
    public:
        void Make_Page(Page & current_page, Texture2D & background, Font & titleFont,
                        Font & subtitleFont, Font & buttonFont,
                        const std :: string & resultLine, const std :: string & detailLine);
};

#endif
