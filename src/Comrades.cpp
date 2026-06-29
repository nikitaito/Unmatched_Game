#include "Comrades.h"

using namespace std;

Comrades::Comrades(string name, std::string Attacktype, int Health, int Movement)
    : name(name), Attacktype(Attacktype), Health(Health), Movement(Movement) {}

bool Comrades::get_islive() const
{
    return islive;
}

std::string Comrades::get_Attacktype() const
{
    return Attacktype;
}

int Comrades::get_Health() const
{
    return Health;
}

int Comrades::get_Movement() const
{
    return Movement;
}
