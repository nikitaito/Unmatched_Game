#include "Card.h"

Card::Card(CardType name, CardTiming timing, std::string typeAttack, int Attack, int Defense, int Boost)
    : name(name), timing(timing), typeAttack(typeAttack), Attack(Attack), Defense(Defense), Boost(Boost) {}

CardType Card::get_CardTpe() const
{
    return this->name;
}
CardTiming Card::get_CardTiming() const
{
    return this->timing;
}