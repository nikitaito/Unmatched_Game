#include "fighter/InvisibleManToken.h"

InvisibleManToken::InvisibleManToken()
    : Sidekick(CharacterType :: InvmanToken , Attacktype :: MELEE , 1 , 2) {}

bool InvisibleManToken :: occupies_space() const{
    return false;
}

bool InvisibleManToken :: get_islive() const{
    return true;
}

void InvisibleManToken :: Damage(int){
    // no-op: the token has no life, so damage never removes it from the board
}
