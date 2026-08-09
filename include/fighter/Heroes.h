#pragma once

#include <string>
#include <vector>
#include "card/Card.h"
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
        CharacterType name;
        Attacktype attacktype;
        Style style;

        int Health;
        int Health_max;
        int Movement;

    protected :
        Cards cards;
        std :: vector<Sidekick *> sidekick;

    public:
        Heroes(CharacterType, Attacktype, Style , int, int);

        //set and get
        CharacterType get_name() const;
        Attacktype get_Attacktype() const;
        Style get_style() const;
        int get_Movement() const;
        int get_HP() const;
        int get_HP_max()const;

        void Damage(int);
        void Heal(int);
        void set_Health(int);
        std :: vector<Card> & get_deck_cards();

        //virtual
        virtual void initial_deck() = 0;
        virtual void assign_sidekicks() {};
        virtual std :: vector<Sidekick *> get_sidekick() {};

};