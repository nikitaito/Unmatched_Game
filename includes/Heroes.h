#pragma once

#include <string>
#include <vector>
#include "Card.h"
#include "Enums.h"
#include "Sidekick.h"

struct Cards
{
    std::vector<Card> deck;
    std::vector<Card> hand;
    std::vector<Card> discard;
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
        std :: vector<Sidekick> sidekick;

    public:
        Heroes(std::string, Attacktype, Style , int, int);

        //set and get
        std::string get_name() const;
        Attacktype get_Attacktype() const;
        Style get_style() const;
        int get_Movement() const;

        void Damage(int);
        void set_Health(int);

        //virtual
        virtual void initial_deck() = 0;
        virtual void initial_sidekicks() = 0;

};