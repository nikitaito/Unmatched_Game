#ifndef BOARD_H
#define BOARD_H

#include "space.h"

class Board
{
    private:
        static constexpr int SPACE_COUNT = 32;
        std :: vector<Space> spaces;
        bool dfs(int , int , std::vector<bool>& , CharacterType , bool , int ) const;
    public:
        Board();

        std :: vector<Space> get_spaces() const;
        void set_Hero(Heroes * , int) ;
        void set_Comrade(Sidekick * , int);
        void reset_space(int);
        Space * search_hero(Heroes *);
        Space * search_comrades(Sidekick *);
        int number_of_sisters_in_this_zone(Space *);
        bool is_way(int , int , CharacterType , bool , int) const;
        void Move(int , int);
        bool Adjacency(CharacterType , CharacterType);
        void Swap(int , int);
        std :: vector<int> get_empty_spaces_in_zone(std :: vector<Zone>) const;



        
};



#endif