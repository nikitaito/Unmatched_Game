#include "board/space.h"
#include "exption_control.h"
using namespace std;

Space :: Space(int id , std :: vector<int> neighbor, std :: vector<int> hidden_way , std :: vector<Zone> zone ) : zone(zone) , neighbor(neighbor) , Hidden_way(hidden_way) , id(id){}

int Space :: get_id() const{
    return id;
}

vector <int> Space :: get_neighbor() const{
    return neighbor;
}

vector <int> Space :: get_Hidden_way() const{
    return Hidden_way;
}

Heroes* Space :: get_Hero() const {
    return hero;
}

vector<Zone> Space :: get_zone() const{
    return zone;
}

void Space :: set_neighbor(vector<int> & n){
    neighbor = n;
}

void Space :: set_hidden_way(vector<int> & h){
    Hidden_way = h;
}

void Space::set_hero(Heroes* hero){
    if (this->hero == nullptr && this->comrade == nullptr)
        this->hero = hero;
    else
        throw NoSpaceException();
}

void Space::set_comrades(Sidekick* comrade){
    if (this->hero == nullptr && this->comrade == nullptr)
        this->comrade = comrade;
    else
        throw NoSpaceException();
}

void Space::set_token(Sidekick* token){
    if (this->token == nullptr)
        this->token = token;
    else
        throw NoSpaceException();
}

void Space :: set_zone(vector<Zone> & zone){
    this->zone = zone;
}

Sidekick* Space :: get_comrade() const{
    return comrade;
}

Sidekick* Space :: get_token() const{
    return token;
}

void Space :: clear_token(){
    token = nullptr;
}

void Space :: clear_comrade(){
    comrade = nullptr;
}

void Space :: clear_hero(){
    hero = nullptr;
}

void Space :: reset(){
    hero = nullptr;
    comrade = nullptr;
    token = nullptr;
}

bool Space :: operator == (const Space & s) const{
    if(s.get_zone() != zone)
        return false;
    if(s.get_comrade() != comrade)
        return false;
    if(s.get_Hero() != hero)
        return false;
    if(s.get_token() != token)
        return false;
    if(s.get_Hidden_way() != Hidden_way)
        return false;
    if(s.get_neighbor() != neighbor)
        return false;


    return true;
}

bool Space :: empty() const{
    return hero == nullptr && comrade == nullptr;
}




