#include "Player.h"
using namespace std;

// Player :: Player(string name , int age) : age(age) , name(name) {}

int Player :: get_age() const{
    return age;
}

string Player :: get_name() const{
    return name;
}

void Player :: assign_Characters(herotype ht){
    if(ht == herotype :: SherlockHolmes)
        current_hero = &sherlock;
    else
        current_hero = &dracula;
}

void Player :: set_age(int x){
    age = x;
}

void Player :: set_name (string name){
    this->name = name;
}

void Player :: add_card(Card card){
    handcard.push_back(card);
}

void Player :: remove_card(Card card){
    CardName name = card.get_CardName();
    auto it = std::find_if(handcard.begin(), handcard.end(),[name](const Card& c) { return c.get_CardName() == name;});

    if (it != handcard.end()) {
        discard.push_back(*it);
        handcard.erase(it);
    }
}

vector<Card> Player :: get_hand_cards() const{
    return handcard;
}

vector<Card> Player :: get_dis_cards() const{
    return discard;
}

Heroes * Player :: get_hero(){
    return current_hero;
}

