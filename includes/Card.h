#pragma once

#include <string>
#include <functional>
#include"Enums.h"

class Card
{

private:
    CardType name;
    CardTiming timing; // "DURING" , "AFTER" , "BEFORE", "IMMEDIATE"
    std::string typeAttack;   // "ATTACK" , "DEFENSE" , "EVENT", "BOTH"
    int Attack;
    int Defense;
    int Boost;

public:
    Card() = default;
    Card(CardType, CardTiming, std::string, int, int, int);

    CardType get_CardTpe() const;
    CardTiming get_CardTiming() const;
};