#include "board.h"
#include<iostream>

using namespace std;

void Board :: intial_space(Space& space , vector<int> neighbors, vector<int> hidden_way , vector<Zone> zone){
    for (int i : neighbors){
        vector<Space *> ngh;
        ngh.push_back(&spaces[i]);
        space.set_neighbor(ngh);  
    }
    for (int i : hidden_way){
        vector<Space*> hw;
        hw.push_back(&spaces[i]);
        space.set_hidden_way(hw);
    }
    space.set_zone(zone);
    
}

Board :: Board(){
    Space space;
    for (int i = 0; i < 31; i++){
        spaces.push_back(space);
    }

    intial_space(spaces[0] , {1,2} , {14 , 18 , 31} , {LIGHT_BLUE} );
    intial_space(spaces[1] , {0,4} , {} , {LIGHT_BLUE});
    intial_space(spaces[2] , {0,3} , {} , {LIGHT_BLUE});
    intial_space(spaces[3] , {2,4,8} , {} , {LIGHT_BLUE} );
    intial_space(spaces[4] , {1,3,5,8} , {} , {LIGHT_BLUE , BROWN} );
    intial_space(spaces[5] , {4,6,7} , {} , {BROWN} );
    intial_space(spaces[6] , {5,28} , {} , {BROWN} );
    intial_space(spaces[7] , {5,28} , {} , {BROWN} );
    intial_space(spaces[8] , {3,4,9} , {} , {LIGHT_BLUE , DARK_BLUE} );
    intial_space(spaces[9] , {8,10} , {} , {DARK_BLUE} );
    intial_space(spaces[10] , {2,9,11} , {} , {DARK_BLUE} );
    intial_space(spaces[11] , {10,12,18} , {} , {DARK_BLUE  ,GRAY} );
    intial_space(spaces[12] , {11,13} , {} , {DARK_BLUE , GREEN} );
    intial_space(spaces[13] , {12,14,15} , {} , {GREEN} );
    intial_space(spaces[14] , {13,21} , {0 , 18 , 31} , {GREEN} );
    intial_space(spaces[15] , {14,16,19,20} , {} , {GRAY , GREEN} );
    intial_space(spaces[16] , {15,17,19} , {} , {GRAY} );
    intial_space(spaces[17] , {16,18} , {} , {GRAY} );
    intial_space(spaces[18] , {11,17} , {0 , 14 ,31} , {GRAY});
    intial_space(spaces[19] , {15,16,20} , {} , {GRAY} );
    intial_space(spaces[20] , {15,19,21,25} , {} , {GRAY} );
    intial_space(spaces[21] , {14,20,22,24,25,28} , {} , {GREEN , PURPULE} );
    intial_space(spaces[22] , {21,23,24,30} , {} , {PURPULE} );
    intial_space(spaces[23] , {22,24,26} , {} , {PURPULE} );
    intial_space(spaces[24] , {21,22} , {} , {PURPULE} );
    intial_space(spaces[25] , {20,21,24,26,27} , {} , {GRAY} );
    intial_space(spaces[26] , {23,25,27} , {} , {GRAY , PURPULE} );
    intial_space(spaces[27] , {25,26} , {} , {GRAY} );
    intial_space(spaces[28] , {6,7,29,30} , {} , {BROWN , GREEN , YELLOW} );
    intial_space(spaces[29] , {28,30,31} , {} , {YELLOW} );
    intial_space(spaces[30] , {22,28,29} , {} , {YELLOW} );
    intial_space(spaces[31] , {29} , {0 , 14 , 18} , {YELLOW});
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
    spaces[situation].reset_hero();
}

Space * Board :: search_hero(Hero * hero){
    Space * search_hero = nullptr;
    for (auto it : spaces){
        if(hero == it.get_Hero())
            search_hero = &it;
    }
    return search_hero;
}

Space * Board :: search_comrades(Comrades * comrade){
    Space * search_comrade = nullptr;
    for (auto it : spaces){
        if(comrade == it.get_comrade())
            search_comrade = &it;
    }
    return search_comrade;
}

