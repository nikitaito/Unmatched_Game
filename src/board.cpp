#include "board.h"
#include<iostream>

using namespace std;

void Board :: initial_space(Space& space , vector<int> neighbors, vector<int> hidden_way , vector<Zone> zone){
    vector<Space *> ngh;
    vector<Space*> hw;

    for (int i : neighbors){
        ngh.push_back(&spaces[i]);
    }
    for (int i : hidden_way){
        hw.push_back(&spaces[i]);
    }

    space.set_neighbor(ngh);  
    space.set_hidden_way(hw);
    space.set_zone(zone);
    
}

Board :: Board(){
    spaces.resize(SPACE_COUNT);

    initial_space(spaces[0] , {1,2} , {14 , 18 , 31} , {LIGHT_BLUE} );
    initial_space(spaces[1] , {0,4} , {} , {LIGHT_BLUE});
    initial_space(spaces[2] , {0,3} , {} , {LIGHT_BLUE});
    initial_space(spaces[3] , {2,4,8} , {} , {LIGHT_BLUE} );
    initial_space(spaces[4] , {1,3,5,8} , {} , {LIGHT_BLUE , BROWN} );
    initial_space(spaces[5] , {4,6,7} , {} , {BROWN} );
    initial_space(spaces[6] , {5,28} , {} , {BROWN} );
    initial_space(spaces[7] , {5,28} , {} , {BROWN} );
    initial_space(spaces[8] , {3,4,9} , {} , {LIGHT_BLUE , DARK_BLUE} );
    initial_space(spaces[9] , {8,10} , {} , {DARK_BLUE} );
    initial_space(spaces[10] , {2,9,11} , {} , {DARK_BLUE} );
    initial_space(spaces[11] , {10,12,18} , {} , {DARK_BLUE  ,GRAY} );
    initial_space(spaces[12] , {11,13} , {} , {DARK_BLUE , GREEN} );
    initial_space(spaces[13] , {12,14,15} , {} , {GREEN} );
    initial_space(spaces[14] , {13,21} , {0 , 18 , 31} , {GREEN} );
    initial_space(spaces[15] , {14,16,19,20} , {} , {GRAY , GREEN} );
    initial_space(spaces[16] , {15,17,19} , {} , {GRAY} );
    initial_space(spaces[17] , {16,18} , {} , {GRAY} );
    initial_space(spaces[18] , {11,17} , {0 , 14 ,31} , {GRAY});
    initial_space(spaces[19] , {15,16,20} , {} , {GRAY} );
    initial_space(spaces[20] , {15,19,21,25} , {} , {GRAY} );
    initial_space(spaces[21] , {14,20,22,24,25,28} , {} , {GREEN , PURPULE} );
    initial_space(spaces[22] , {21,23,24,30} , {} , {PURPULE} );
    initial_space(spaces[23] , {22,24,26} , {} , {PURPULE} );
    initial_space(spaces[24] , {21,22} , {} , {PURPULE} );
    initial_space(spaces[25] , {20,21,24,26,27} , {} , {GRAY} );
    initial_space(spaces[26] , {23,25,27} , {} , {GRAY , PURPULE} );
    initial_space(spaces[27] , {25,26} , {} , {GRAY} );
    initial_space(spaces[28] , {6,7,29,30} , {} , {BROWN , GREEN , YELLOW} );
    initial_space(spaces[29] , {28,30,31} , {} , {YELLOW} );
    initial_space(spaces[30] , {22,28,29} , {} , {YELLOW} );
    initial_space(spaces[31] , {29} , {0 , 14 , 18} , {YELLOW});
}

std :: vector<Space> Board ::  get_spaces() const{
    return spaces;
}

void Board :: set_Hero(Hero * hero , int situation){
    spaces[situation].set_hero(hero);
}

void Board :: set_Comrade(Comrades * comrade , int situation){
    spaces[situation].set_comrades(comrade);
}

void Board :: reset_space(int situation){
    spaces[situation].reset();
}

Space * Board :: search_hero(Hero * hero){
    Space * search_hero = nullptr;
    for (auto & it : spaces){
        if(hero == it.get_Hero())
            search_hero = &it;
    }
    return search_hero;
}

Space * Board :: search_comrades(Comrades * comrade){
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
            if(*it == spaces[b])
                return WayType :: Normal; 
        }
    else{
        for(auto it :spaces[a].get_Hidden_way()){
            if(*it == spaces[b])
                return WayType :: Hidden; 
        }
    }
    return WayType :: None;
}



