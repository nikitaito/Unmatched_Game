
#include "Heroes.h"
using namespace std;

Heroes::Heroes(CharacterType name, Attacktype attacktype, Style style , int Health, int Movement)
    : name(name), attacktype(attacktype), style(style) , Health(Health), Movement(Movement) , Health_max(Health) {}

CharacterType Heroes::get_name() const
{
    return name;
    ;
}

Attacktype Heroes::get_Attacktype() const
{
    return attacktype;
}

Style Heroes :: get_style() const{
    return style;
}

int Heroes::get_Movement() const
{
    return Movement;
}

int Heroes :: get_HP() const{
    return Health;
}

int Heroes :: get_HP_max() const{
    return Health_max;
}

void Heroes :: Damage(int x){
    if(Health <= x)
        Health = 0;
    else
        Health -= x; 
}

void Heroes :: Heal(int x){
    Health += x;
}

void Heroes::set_Health(int amount)
{
    if (Health + 2 > 13)
        Health = 13;
    else
        this->Health += amount;
}

vector<Card>& Heroes :: get_deck_cards() {
    return cards.deck;
}