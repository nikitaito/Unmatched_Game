#pragma once

// Small, self-contained text helpers used only by the front-end. The game
// backend never needed human-readable strings for CardName/CardType/Usertype
// (it only compares enum values), but the UI has no card artwork to fall
// back on, so hand cards, deck/discard viewers and the combat screen render
// these names + a short stat line instead of a picture.

#include "Enums.h"
#include <string>

// Printed card name, matching the rulebook text (e.g. "Confound - Extra").
const char * CardDisplayName(CardName name);

// Short label for who may play the card ("Hero", "Sidekick", "Any").
const char * UsertypeLabel(Usertype type);

// Short label for the card type, matching the rulebook's color-coded types.
const char * CardTypeLabel(CardType type);

// One line combining Attack/Defense/Boost as printed on the card, e.g.
// "ATK 3 / BOOST 2" or "ATK-DEF 3 / BOOST 1" for Versatile cards.
std :: string CardStatLine(CardType type, int attack, int defense, int boost);

// Readable name for a fighter, used for hero/sidekick panels and logs.
const char * CharacterDisplayName(CharacterType type);
