#ifndef PLAYER_H
#define PLAYER_H

#include "fighter/Heroes.h"
#include "Enums.h"
#include "fighter/SherlockHolmes.h"
#include "fighter/Dracula.h"
#include "fighter/Sidekick.h"
#include "card/Card.h"
#include <string>

class Player
{
    private:
        Heroes * current_hero = nullptr;
        SherlockHolmes sherlock;
        Dracula dracula;

        std::vector<Card> handcard;
        std::vector<Card> discard;

        std :: string name;
        int age;

        int action = 2;

    public:
        // Player(std :: string , int);
        
        //set and get
        void set_name(std :: string);
        void set_age(int);
        void add_card(Card&& card);
        int remove_card(CardName);
        Card take_hand_card(int index);
        void discard_card(Card&& card);
        std :: vector<Card>& get_hand_cards() ;
        std :: vector<Card>& get_dis_cards() ;
        int get_age()const;
        std :: string get_name() const;
        Heroes * get_hero();
        void assign_Characters(CharacterType) ;
        int get_aciton()const;
        void increase_action(int x);
        void decrease_action(int x);
        void reset_action();
        
};




#endif 
