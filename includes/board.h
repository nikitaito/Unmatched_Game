#ifndef BOARD_H
#define BOARD_H

#include "space.h"
class Hero;

class Board
{
    private:
        std :: vector<Space> spaces;
        Hero * hero;
        

    public:
        Board();

    
};



#endif