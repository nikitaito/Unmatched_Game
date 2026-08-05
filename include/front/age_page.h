
#ifndef AGE_PAGE
#define AGE_PAGE

#include <string.h>
#include <cstdlib>
#include "Enums.h"
#include "raylib.h"

enum ActiveField
{
    FIELD_NONE,
    FIELD_PLAYER1,
    FIELD_PLAYER2
};

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
        bool DrawNumberInput(Rectangle , char* , int , bool , Font , Vector2 , Color , Color , Color , Color , Color);
    public:
        void Make_Page(Page & , int & , int &);
        
};





#endif
