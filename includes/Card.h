#pragma once

#include <string>
#include <functional>
#include "Enums.h"

class Card
{

private:
    CardType name;
    CardTiming timing;      // "DURING" , "AFTER" , "BEFORE", "IMMEDIATE"
    std::string typeAttack; // "ATTACK" , "DEFENSE" , "EVENT", "BOTH"
    int Attack;
    int Defense;
    int Boost;

    bool ApplyEffects{true};

public:
    Card() = default;
    Card(CardType, CardTiming, std::string, int, int, int);

    CardType get_CardType() const;
    CardTiming get_CardTiming() const;

    int get_Boost() const;
    void set_Boost(int);

    int get_Attack() const;
    void set_Attack(int);

    int get_Defense() const;
    void set_Defence(int);

    bool get_ApplyEffects();
    void set_ApplyEffects(bool);
};