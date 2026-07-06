#ifndef PLAYER_H
#define PLAYER_H

#include "Heroes.h"
#include "Enums.h"
#include "SherlockHolmes.h"
#include "Dracula.h"
#include "Sidekick.h"
#include "Card.h"
#include <string>

class Player
{
    private:
        Heroes * current_hero;
        SherlockHolmes sherlock;
        Dracula dracula;

        std :: string name;
        int age;

    public:
        // Player(std :: string , int);
        
        //set and get
        void set_name(std :: string);
        void set_age(int);
        int get_age()const;
        std :: string get_name() const;
        void assign_Characters(int x) ;
        
};




#endif 
