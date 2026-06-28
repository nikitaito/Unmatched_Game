#include "space.h"
using namespace std;

// Space :: Space(Zone z , vector<Space*> v , vector<Space *> h) : zone(z) , neighbor(v) , Hidden_way(h) {}

vector <Space *> Space :: get_neighbor() const{
    return neighbor;
}

vector <Space *> Space :: get_Hidden_way() const{
    return neighbor;
}

Hero* Space :: get_Hero() const {
    return hero;
}

vector<Zone> Space :: get_zone() const{
    return zone;
}

void Space :: reset_hero(){
    hero = nullptr;
    comrade = nullptr;
}

void Space :: set_neighbor(vector<Space*> n){
    neighbor = n;
}

void Space :: set_hidden_way(vector<Space*> h){
    Hidden_way = h;
}

void Space :: set_hero(Hero * hero){
    this->hero = hero;
}

void Space :: set_comrades(Comrades * comrade){
    this->comrade = comrade;
}

void Space :: set_zone(vector<Zone> zone){
    this->zone = zone;
}

Comrades* Space :: get_comrade() const{
    return comrade;
}




