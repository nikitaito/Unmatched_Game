#include "board.h"
#include "exption_control.h"
#include<iostream>

using namespace std;


Board :: Board(){
    
    spaces.push_back(Space(0 , {1,2} , {14 , 18 , 31} , {LIGHT_BLUE} ));
    spaces.push_back(Space(1 , {0,4} , {} , {LIGHT_BLUE}));
    spaces.push_back(Space(2 , {0,3} , {} , {LIGHT_BLUE}));
    spaces.push_back(Space(3 , {2,8} , {} , {LIGHT_BLUE} ));
    spaces.push_back(Space(4 , {1,5,8} , {} , {LIGHT_BLUE , BROWN} ));
    spaces.push_back(Space(5 , {4,6,7} , {} , {BROWN} ));
    spaces.push_back(Space(6 , {5,7,28} , {} , {BROWN} ));
    spaces.push_back(Space(7 , {5,28} , {} , {BROWN} ));
    spaces.push_back(Space(8 , {3,4,9} , {} , {LIGHT_BLUE , DARK_BLUE} ));
    spaces.push_back(Space(9 , {8,10} , {} , {DARK_BLUE} ));
    spaces.push_back(Space(10 , {2,9,11} , {} , {DARK_BLUE} ));
    spaces.push_back(Space(11 , {10,12,18} , {} , {DARK_BLUE  ,GRAY} ));
    spaces.push_back(Space(12 , {11,13} , {} , {DARK_BLUE , GREEN} ));
    spaces.push_back(Space(13 , {12,14,15} , {} , {GREEN} ));
    spaces.push_back(Space(14 , {13,21} , {0 , 18 , 31} , {GREEN} ));
    spaces.push_back(Space(15 , {14,16,19,20} , {} , {GRAY , GREEN} ));
    spaces.push_back(Space(16 , {15,17,19} , {} , {GRAY} ));
    spaces.push_back(Space(17 , {16,18} , {} , {GRAY} ));
    spaces.push_back(Space(18 , {11,17} , {0 , 14 ,31} , {GRAY}));
    spaces.push_back(Space(19 , {15,16,20} , {} , {GRAY} ));
    spaces.push_back(Space(20 , {15,19,21,25} , {} , {GRAY} ));
    spaces.push_back(Space(21 , {14,20,22,24,25,28} , {} , {GREEN , PURPULE} ));
    spaces.push_back(Space(22 , {21,23,24,30} , {} , {PURPULE} ));
    spaces.push_back(Space(23 , {22,24,26} , {} , {PURPULE} ));
    spaces.push_back(Space(24 , {21,22} , {} , {PURPULE} ));
    spaces.push_back(Space(25 , {20,21,24,26,27} , {} , {GRAY} ));
    spaces.push_back(Space(26 , {23,25,27} , {} , {GRAY , PURPULE} ));
    spaces.push_back(Space(27 , {25,26} , {} , {GRAY} ));
    spaces.push_back(Space(28 , {6,7,21,29,30} , {} , {BROWN , GREEN , YELLOW} ));
    spaces.push_back(Space(29 , {28,30,31} , {} , {YELLOW} ));
    spaces.push_back(Space(30 , {22,28,29} , {} , {YELLOW} ));
    spaces.push_back(Space(31 , {29} , {0 , 14 , 18} , {YELLOW}));
}

const std :: vector<Space> & Board ::  get_spaces() const{
    return spaces;
}

std :: vector<Space> & Board :: get_spaces_mut(){
    return spaces;
}

int Board :: get_space_count() const{
    return SPACE_COUNT;
}

bool Board :: valid_space(int id) const{
    return id >= 0 && id < SPACE_COUNT;
}

void Board :: set_Hero(Heroes * hero , int situation){
    spaces[situation].set_hero(hero);
}

void Board :: set_Comrade(Sidekick* comrade , int situation){
    spaces[situation].set_comrades(comrade);
}

void Board :: reset_space(int situation){
    spaces[situation].reset();
}

Space * Board :: search_hero(Heroes * hero){
    Space * search_hero = nullptr;
    for (auto & it : spaces){
        if(hero == it.get_Hero())
            search_hero = &it;
    }
    return search_hero;
}

Space * Board :: search_comrades(Sidekick * comrade){
    Space * search_comrade = nullptr;
    for (auto & it : spaces){
        if(comrade == it.get_comrade())
            search_comrade = &it;
    }
    return search_comrade;
}

int Board :: find_space_of_hero(Heroes * hero) const{
    for(const auto & it : spaces){
        if(it.get_Hero() == hero)
            return it.get_id();
    }
    return -1;
}

int Board :: find_space_of_comrade(Sidekick * comrade) const{
    for(const auto & it : spaces){
        if(it.get_comrade() == comrade)
            return it.get_id();
    }
    return -1;
}

int Board :: number_of_sisters_in_this_zone(Space * space){
    int i = 0;
    for(const auto & it : spaces){
        if(it.get_zone() == space->get_zone() && it.get_id() != space->get_id() && dynamic_cast<Sister *>(it.get_comrade()) != nullptr){
            i++;
        }
    }
    return i;
}

bool Board :: dfs(int current , int target , std::vector<bool>& visited , CharacterType forbidden , bool allowhiddenway , int cost ) const{
    if (current == target)
        return true;
    
    if(cost <= 0)
        return false;

    visited[current] = true;
    const Space & space = spaces[current];

    for(int next : space.get_neighbor()){
        if(visited[next] == true)
            continue;
        
        if(spaces[next].get_Hero() && spaces[next].get_Hero()->get_name() == forbidden)
            continue;
        else if(spaces[next].get_comrade() && spaces[next].get_comrade()->get_name() == forbidden)
            continue;

        if(dfs(next , target , visited , forbidden , allowhiddenway , cost - 1))
            return true;
    }

    if (allowhiddenway)
    {
        for (int next : space.get_Hidden_way())
        {
            if (visited[next] == true)
                continue;

            if(spaces[next].get_Hero() && spaces[next].get_Hero()->get_name() == forbidden)
                continue;
            else if(spaces[next].get_comrade() && spaces[next].get_comrade()->get_name() == forbidden)
                continue;

            if (dfs(next, target, visited, forbidden, allowhiddenway , cost - 1))
                return true;
        }
    }
    visited[current] = false;
    return false;
}

bool Board :: is_way(int current , int target , CharacterType forbidden , bool allowhiddenway, int cost) const{
    if(!(spaces[target].empty()))
        return false;
    
    std :: vector<bool> visited (SPACE_COUNT , false);
    return dfs(current , target , visited , forbidden , allowhiddenway , cost);

}

void Board :: Move(int current , int target){
    if(current == target)
        return;

    if(spaces[current].get_Hero()){
        Heroes * hero = spaces[current].get_Hero();
        spaces[current].reset();
        spaces[target].set_hero(hero);
    }
    else if(spaces[current].get_comrade()){
        Sidekick * sidekick = spaces[current].get_comrade();
        spaces[current].reset();
        spaces[target].set_comrades(sidekick);
    }
}

void Board :: Teleport(int current , int target){
    if(!spaces[target].empty())
        throw NoSpaceException();

    Move(current , target);
}

bool Board :: AdjacentSpaces(int a , int b) const{
    if(!valid_space(a) || !valid_space(b))
        return false;

    for(int n : spaces[a].get_neighbor()){
        if(n == b)
            return true;
    }
    return false;
}

bool Board :: SameZone(int a , int b) const{
    if(!valid_space(a) || !valid_space(b))
        return false;

    for(auto za : spaces[a].get_zone()){
        for(auto zb : spaces[b].get_zone()){
            if(za == zb)
                return true;
        }
    }
    return false;
}

bool Board :: Adjacency(CharacterType ch1 , CharacterType ch2){
    for(auto & sp : spaces){
        if((sp.get_Hero() && sp.get_Hero()->get_name() == ch1) || (sp.get_comrade() && sp.get_comrade()->get_name() == ch1)){
            for(auto & ng : sp.get_neighbor()){
                if(spaces[ng].get_Hero() && spaces[ng].get_Hero()->get_name() == ch2)
                    return true;
                else if(spaces[ng].get_comrade() && spaces[ng].get_comrade()->get_name() == ch2)
                    return true;
            }
        }
    }
    return false;
}

void Board :: Swap(int a , int b){
    Sidekick * sidekick_A = spaces[a].get_comrade();
    Heroes * hero_A = spaces[a].get_Hero();
    Sidekick * sidekick_B = spaces[b].get_comrade();
    Heroes * hero_B = spaces[b].get_Hero();

    spaces[a].reset();
    spaces[b].reset();

    if(hero_B)
        spaces[a].set_hero(hero_B);
    if(sidekick_B)
        spaces[a].set_comrades(sidekick_B);

    if(hero_A)
        spaces[b].set_hero(hero_A);
    if(sidekick_A)
        spaces[b].set_comrades(sidekick_A);
}

