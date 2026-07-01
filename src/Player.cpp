#include "Player.h"
using namespace std;

Player :: Player(string name , int age) : age(age) , name(name) {}

int Player :: get_age() const{
    return age;
}

string Player :: get_name() const{
    return name;
}

void Player :: assign_Characters(int x){
    if(x == 1)
        current_hero = &sherlock;
    else
        current_hero = &dracula;
}

