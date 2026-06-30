
#include "Heroes.h"
using namespace std;

Heroes::Heroes(std::string name, std::string Attacktype, int Health, int Movement)
    : name(name), Attacktype(Attacktype), Health(Health), Movement(Movement) {}

string Heroes::get_name()
{
    return name;
    ;
}
string Heroes::get_Attacktype()
{
    return Attacktype;
}
int Heroes::get_Movement()
{
    return Movement;
}
void Heroes::set_Health(int amount)
{
    if (Health + 2 > 13)
        Health = 13;
    else
        this->Health += amount;
}