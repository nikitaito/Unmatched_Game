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

        std::vector<Card> handcard;
        std::vector<Card> discard;

        std :: string name;
        int age;

    public:
        // Player(std :: string , int);
        
        //set and get
        void set_name(std :: string);
        void set_age(int);
        void add_card(Card card);
        void remove_card(Card card);
        std :: vector<Card> get_hand_cards() const;
        std :: vector<Card> get_dis_cards() const;
        int get_age()const;
        std :: string get_name() const;
        Heroes * get_hero();
        void assign_Characters(herotype) ;
        
};




#endif 
