#include "Card.h"

Card::Card(CardType name, CardTiming timing, std::string typeAttack, int Attack, int Defense, int Boost)
    : name(name), timing(timing), typeAttack(typeAttack), Attack(Attack), Defense(Defense), Boost(Boost) {}

CardType Card::get_CardType() const
{
    return this->name;
}
CardTiming Card::get_CardTiming() const
{
    return this->timing;
}

int Card::get_Boost() const
{
    return Boost;
}

void Card::set_Boost(int amount)
{
    this->Boost += amount;
}

int Card::get_Attack() const
{
    return Attack;
}

void Card::set_Attack(int amount)
{
    Attack += amount;
}

int Card::get_Defense() const
{
    return Defense;
}
void Card::set_Defence(int amount)
{
    Defense += amount;
}

void Card::set_ApplyEffects(bool b)
{
    ApplyEffects = b;
}

bool Card::get_ApplyEffects()
{
    return ApplyEffects;
}
