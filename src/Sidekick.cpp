#include "Sidekick.h"

using namespace std;

Sidekick::Sidekick(string name, Attacktype attacktype, int Health, int Movement)
    : name(name), attacktype(attacktype), Health(Health), Movement(Movement) {}

bool Sidekick::get_islive() const
{
    if(Health == 0)
        return 0;
    
    else if(Health > 0)
        return 1;
    
}

Attacktype Sidekick :: get_Attacktype() const
{
    return attacktype;
}

int Sidekick::get_Health() const
{
    return Health;
}

int Sidekick::get_Movement() const
{
    return Movement;
}

void Sidekick :: Damage(int x)
{
    if(Health <= x)
        Health = 0;
    else
        Health -= x; 
}
