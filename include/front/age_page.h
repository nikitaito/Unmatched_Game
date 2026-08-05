
#ifndef AGE_PAGE
#define AGE_PAGE

#include <string.h>
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

class AgePage
{
    private:
        bool DrawMenuButton(MenuButton& , Rectangle , Font ,Vector2 , bool);
    public:
        
};





#endif
