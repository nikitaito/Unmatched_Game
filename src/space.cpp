#include "space.h"
#include "exption_control.h"
using namespace std;

Space :: Space(std :: vector<int> n, std :: vector<int> h , std :: vector<Zone> z ) {

}

vector <Space *> Space :: get_neighbor() const{
    return neighbor;
}

vector <Space *> Space :: get_Hidden_way() const{
    return Hidden_way;
}

Hero* Space :: get_Hero() const {
    return hero;
}

vector<Zone> Space :: get_zone() const{
    return zone;
}

void Space :: set_neighbor(vector<Space*> & n){
    neighbor = n;
}

void Space :: set_hidden_way(vector<Space*> & h){
    Hidden_way = h;
}

void Space :: set_hero(Hero * hero){
    if(hero == nullptr && comrade == nullptr)
        this->hero = hero;
    else
        throw  NoSpaceException(); 
}

void Space :: set_comrades(Comrades * comrade){
    if(hero == nullptr && comrade == nullptr)
        this->comrade = comrade;
    else
        throw NoSpaceException();
}

void Space :: set_zone(vector<Zone> & zone){
    this->zone = zone;
}

Comrades* Space :: get_comrade() const{
    return comrade;
}

void Space :: reset(){
    hero = nullptr;
    comrade = nullptr;
}

bool Space :: operator == (const Space & s) const{
    if(s.get_zone() != zone)
        return false;
    if(s.get_comrade() != comrade)
        return false;
    if(s.get_Hero() != hero)
        return false;
    if(s.get_Hidden_way() != Hidden_way)
        return false;
    if(s.get_neighbor() != neighbor)
        return false;


    return true;
}




