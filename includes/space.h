#ifndef SPACE_H
#define SPACE_H

#include<vector>

enum class Zone{
    LIGHT_BLUE,
    DARK_BLUE,
    BROWN,
    YELLOW,
    GREEN,
    PURPULE,
    GRAY
};

class Hero;//will remove

class Space
{
    private:
        std :: vector<Space *> neighbor = {};
        Zone zone ;
        std :: vector<Space *> Hidden_way = {};
        Hero * hero = nullptr;

    public:
        Space(Zone , std :: vector<Space*> , std :: vector<Space *>) ;
        void set_hero(Hero *);

    
};



#endif