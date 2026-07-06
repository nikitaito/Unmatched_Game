#pragma once

#include <string>
#include <functional>
#include "Enums.h"

class Card
{

    private:
        CardName name;
        CardTiming timing;      // "DURING" , "AFTER" , "BEFORE", "IMMEDIATE"
        CardType cardtype; // "ATTACK" , "DEFENSE" , "EVENT", "BOTH"
        Usertype usertype;
        int Attack;
        int Defense;
        int Boost;

        bool ApplyEffects{true};

    public:
        Card() = default;
        Card(CardName, CardTiming, CardType, Usertype , int, int, int);

        CardName get_CardName() const;
        CardTiming get_CardTiming() const;
        CardType get_CardType() const;
        Usertype get_usertype() const;

        int get_Boost() const;
        void set_Boost(int);

        int get_Attack() const;
        void set_Attack(int);

        int get_Defense() const;
        void set_Defence(int);

        bool get_ApplyEffects();
        void set_ApplyEffects(bool);
};