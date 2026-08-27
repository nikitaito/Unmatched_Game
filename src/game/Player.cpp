#include "game/Player.h"
#include <algorithm>
using namespace std;

// Player :: Player(string name , int age) : age(age) , name(name) {}

// int Player :: get_age() const{
//     return age;
// }

string Player :: get_name() const{
    return name;
}

void Player :: assign_Characters(CharacterType ht){
    if(ht == CharacterType :: SherlockHolmes)
        current_hero = &sherlock;
    else if(ht == CharacterType :: Invman)
        current_hero = &invman;
    else
        current_hero = &dracula;
}

// void Player :: set_age(int x){
//     age = x;
// }

void Player :: set_name (string name){
    this->name = name;
}

void Player :: add_card(Card&& card){
    handcard.push_back(std :: move(card));
}

int Player :: remove_card(CardName name){
    // CardName name = card.get_CardName();
    int boost = 0;
    auto it = std::find_if(handcard.begin(), handcard.end(),[name](const Card& c) { return c.get_CardName() == name;});

    if (it != handcard.end()) {
        discard.push_back(std :: move(*it));
        boost = it->get_Boost();
        handcard.erase(it);
    }
    return boost;

}

Card Player :: take_hand_card(int index){
    Card c = std :: move(handcard[index]);
    handcard.erase(handcard.begin() + index);
    return c;
}

void Player :: discard_card(Card&& card){
    discard.push_back(std :: move(card));
}

vector<Card>& Player :: get_hand_cards() {
    return handcard;
}

vector<Card>& Player :: get_dis_cards() {
    return discard;
}

Heroes * Player :: get_hero(){
    return current_hero;
}

int Player :: get_aciton() const{
    return action;
}

void Player :: increase_action(int x){
    action += x;
}

void Player :: decrease_action(int x){
    action -= x;
}

void Player :: reset_action(){
    action = 2;
}

bool Player :: get_PendingVanish() const{
    return pendingVanish;
}

void Player :: set_PendingVanish(bool b){
    pendingVanish = b;
}

