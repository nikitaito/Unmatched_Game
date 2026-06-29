#include "space.h"
using namespace std;

Space :: Space(Zone z , vector<Space*> v , vector<Space *> h) : zone(z) , neighbor(v) , Hidden_way(h) {}

void Space :: set_hero(Hero * hero){
    this->hero = hero;
}




