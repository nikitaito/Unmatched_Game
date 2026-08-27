#pragma once

#include "Enums.h"
#include <string>
const char * CardDisplayName(CardName name);
const char * UsertypeLabel(Usertype type);
const char * CardTypeLabel(CardType type);
std :: string CardStatLine(CardType type, int attack, int defense, int boost);
const char * CharacterDisplayName(CharacterType type);
const char * CardImagePath(CardName name, CharacterType owner);
