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
    public:
        Board();

        std :: vector<Space> get_spaces() const;
        void set_Hero(Heroes * , int) ;
        void set_Comrade(Sidekick * , int);
        void reset_space(int);
        Space * search_hero(Heroes *);
        Space * search_comrades(Sidekick *);
        WayType way(int , int) const;




        
};



#endif