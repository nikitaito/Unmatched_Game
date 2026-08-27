#ifndef AGE_PAGE
#define AGE_PAGE

#include <string.h>
#include <cstdlib>
#include "Enums.h"
#include "raylib.h"
#include "ui_common.h"

enum ActiveField
{
    FIELD_NONE,
    FIELD_PLAYER1,
    FIELD_PLAYER2
};

class AgePage
{
    private:
        bool DrawMenuButton(MenuButton& , Rectangle , Font ,Vector2 , bool);
        bool DrawNumberInput(Rectangle , char* , int , bool , Font , Vector2 , Color , Color , Color , Color , Color);

        ActiveField activeField = FIELD_NONE;
        char player1Age[4] = "";
        char player2Age[4] = "";

    public:
        void Make_Page(Page & current_page,Texture2D & background, Font & titleFont, Font & labelFont , int & age1, int & age2);
        void Reset(); 
};

#endif
