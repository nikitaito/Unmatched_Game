#ifndef BOARD_H
#define BOARD_H

#include "space.h"
class Hero;

enum class WayType
{
    None,
    Normal,
    Hidden
};

class Board
{
    private:
        static constexpr int SPACE_COUNT = 32;
        std :: vector<Space> spaces;
        void initial_space(Space & , std :: vector<int> , std :: vector<int> , std :: vector<Zone>);

    public:
        Board();

        std :: vector<Space> get_spaces() const;
        void set_Hero(Hero * , int) ;
        void set_Comrade(Comrades * , int);
        void reset_space(int);
        Space * search_hero(Hero *);
        Space * search_comrades(Comrades *);
        WayType way(int , int) const;


        
};



#endif