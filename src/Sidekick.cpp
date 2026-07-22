#include "Sidekick.h"

using namespace std;

Sidekick::Sidekick(CharacterType name, Attacktype attacktype, int Health, int Movement)
    : name(name), attacktype(attacktype), Health(Health), Health_max(Health), Movement(Movement) {}

bool Sidekick::get_islive() const
{
    if(Health <= 0)
        return false;
    
    else 
        return true;

    
}

Attacktype Sidekick :: get_Attacktype() const
{
    return attacktype;
}

int Sidekick::get_Health() const
{
    return Health;
}

int Sidekick::get_Health_max() const
{
    return Health_max;
}

int Sidekick::get_Movement() const
{
    return Movement;
}

CharacterType Sidekick :: get_name() const{
    return name;
}

void Sidekick :: Damage(int x)
{
    if(Health <= x)
        Health = 0;
    else
        Health -= x; 
}

void Sidekick :: Heal(int x){
    Health += x;
    if(Health > Health_max)
        Health = Health_max;
}

Sidekick::~Sidekick() = default;
