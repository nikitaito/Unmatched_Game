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
        void intial_space(Space & , std :: vector<int> , std :: vector<int> , std :: vector<Zone>);
        Board();

        std :: vector<Space> get_spaces() const;
        void set_Hero(Hero * , int) ;
        void set_Comrade(Comrades * , int);
        void reset_space(int);
        Space * search_hero(Hero *);
        Space * search_comrades(Comrades *);


        
};



#endif