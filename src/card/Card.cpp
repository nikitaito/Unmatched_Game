#include "Card.h"
using namespace std;
Card::Card(CardName name, CardTiming timing, CardType cardtype , Usertype usertype, int Attack, int Defense, int Boost , vector<unique_ptr<Effect>> Effects )
    : name(name), timing(timing), cardtype(cardtype) , usertype(usertype) , Attack(Attack) , Defense(Defense), Boost(Boost) , Effects(std :: move(Effects)){}

CardName Card::get_CardName() const
{
    return this->name;
}
CardTiming Card::get_CardTiming() const
{
    return this->timing;
}

CardType Card :: get_CardType() const
{
    return this->cardtype;
}

Usertype Card :: get_usertype() const{
    return this->usertype;
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

vector<unique_ptr<Effect>>& Card :: get_effects() {
    return Effects;
}

bool Card :: operator==(const Card & card){
    if(this->get_CardName() == card.get_CardName())
        return true;
    else
        return false;
}

// Card :: ~Card(){
//     for(auto & it : Effects)
//         delete it;
// }