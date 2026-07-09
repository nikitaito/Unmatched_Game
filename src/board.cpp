#include "board.h"
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
    spaces.push_back(Space(28 , {6,7,29,30} , {} , {BROWN , GREEN , YELLOW} ));
    spaces.push_back(Space(29 , {28,30,31} , {} , {YELLOW} ));
    spaces.push_back(Space(30 , {22,28,29} , {} , {YELLOW} ));
    spaces.push_back(Space(31 , {29} , {0 , 14 , 18} , {YELLOW}));
}

std :: vector<Space> Board ::  get_spaces() const{
    return spaces;
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

WayType Board :: way(int a , int b) const{
    if((spaces[a].get_neighbor()).empty() == false)
        for(auto it :spaces[a].get_neighbor()){
            if(it == b)
                return WayType :: Normal; 
        }
    else{
        for(auto it :spaces[a].get_Hidden_way()){
            if(it == a)
                return WayType :: Hidden; 
        }
    }
    return WayType :: None;
}



