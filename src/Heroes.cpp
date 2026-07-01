
#include "Heroes.h"
using namespace std;

Heroes::Heroes(std::string name, Attacktype attacktype, Style style , int Health, int Movement)
    : name(name), attacktype(attacktype), style(style) , Health(Health), Movement(Movement) {}

string Heroes::get_name() const
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

void Heroes :: Damage(int x){
    if(Health <= x)
        Health = 0;
    else
        Health -= x; 
}

void Heroes::set_Health(int amount)
{
    if (Health + 2 > 13)
        Health = 13;
    else
        this->Health += amount;
}