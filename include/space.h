#ifndef SPACE_H
#define SPACE_H

#include<vector>

enum Zone{
    LIGHT_BLUE,
    DARK_BLUE,
    BROWN,
    YELLOW,
    GREEN,
    PURPULE,
    GRAY
};

class Hero;//will remove
class Comrades;//will remove

class Space
{
    private:
        std :: vector<Zone> zone ;
        std :: vector<Space *> neighbor ;
        std :: vector<Space *> Hidden_way;
        Hero * hero = nullptr;
        Comrades * comrade = nullptr;

    public:
        Space(std :: vector<int> , std :: vector<int> , std :: vector<Zone> ) ;
        void reset();

        //set and get
        void set_zone(std :: vector<Zone> &);
        void set_hero(Hero *);
        void set_comrades(Comrades *);
        void set_neighbor(std :: vector<Space*> & );
        void set_hidden_way(std :: vector<Space*> & );
        std :: vector<Space*> get_neighbor() const;
        std :: vector<Space*> get_Hidden_way() const;
        std :: vector<Zone> get_zone() const;
        Hero* get_Hero() const;
        Comrades* get_comrade() const;
        bool operator == (const Space &) const;


    
};



#endif