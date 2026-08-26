#ifndef BOARD_H
#define BOARD_H

#include "space.h"

class Board
{
    private:
        static constexpr int SPACE_COUNT = 32;
        std :: vector<Space> spaces;
        bool dfs(int , int , std::vector<bool>& , CharacterType , bool , int , int origin) const;
        bool dfs_fog(int , int , std::vector<bool>& , const std :: vector<CharacterType> & , bool , int , int origin) const;
    public:
        Board();

        const std :: vector<Space> & get_spaces() const;
        std :: vector<Space> & get_spaces_mut();
        int get_space_count() const;
        void set_Hero(Heroes * , int) ;
        void set_Comrade(Sidekick * , int);
        void set_Token(Sidekick * , int);
        void reset_space(int);
        Space * search_hero(Heroes *);
        Space * search_comrades(Sidekick *);
        Space * search_token(Sidekick *);
        int find_space_of_hero(Heroes *) const;
        int find_space_of_comrade(Sidekick *) const;
        int find_space_of_token(Sidekick *) const;
        int number_of_sisters_in_this_zone(Space *);
        bool is_way(int , int , CharacterType , bool , int) const;
        bool is_way_for_token(int , int , CharacterType , bool , int) const;
        bool is_way_with_fog_jump(int , int , const std :: vector<CharacterType> & , bool , int) const;

        std :: vector<int> reachable_spaces(int current , CharacterType forbidden , bool allowhiddenway , int cost) const;
        std :: vector<int> reachable_spaces_for_token(int current , CharacterType forbidden , bool allowhiddenway , int cost) const;
        std :: vector<int> reachable_spaces_with_fog_jump(int current , const std :: vector<CharacterType> & enemyTypes , bool allowhiddenway , int cost) const;
        void Move(int , int);
        void MoveToken(int , int);
        void Teleport(int , int);
        bool Adjacency(CharacterType , CharacterType);
        bool AdjacentSpaces(int , int) const;
        bool SameZone(int , int) const;
        bool valid_space(int) const;
        void Swap(int , int);



        
};



#endif