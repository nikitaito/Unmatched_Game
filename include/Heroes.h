#pragma once

#include <string>
#include <vector>
#include "Card.h"
#include "Enums.h"
#include "Sisters.h"
#include "Dr_Watson.h"

struct Cards
{
    std::vector<Card> deck;
};


class Heroes
{
    private:
        std::string name;
        Attacktype attacktype;
        Style style;

        int Health;
        int Movement;

    protected :
        Cards cards;
        std :: vector<Sidekick *> sidekick;

    public:
        Heroes(std::string, Attacktype, Style , int, int);

        //set and get
        std::string get_name() const;
        Attacktype get_Attacktype() const;
        Style get_style() const;
        int get_Movement() const;

        void Damage(int);
        void set_Health(int);
        std :: vector<Card> & get_deck_cards() ;

        //virtual
        virtual void initial_deck() = 0;
        virtual void assign_sidekicks() = 0;

};