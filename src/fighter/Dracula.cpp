
#include "fighter/Dracula.h"
#include <random>
using namespace std;

Dracula::Dracula()
    : Heroes(CharacterType :: Dracula, Attacktype :: MELEE , Style :: ARRGD , 13, 2)
{
    initial_deck();
}

vector<Sidekick *> Dracula::get_sisters()
{
  return sidekick;
}

// void Dracula::DrawnCard()
// {
//   cards.hand.push_back(cards.deck.front());
//   cards.hand.erase(cards.hand.begin());
// }

void Dracula :: initial_deck() {

  cards.deck.push_back(Card(CardName::Feedingfrenzy, CardTiming::During, CardType :: ATTACK, Usertype :: DRACULA , 2, 0, 3 , Make_Effect({new Boost_attack(CharacterType :: Sister  , true)})));
  cards.deck.push_back(Card(CardName::Feedingfrenzy, CardTiming::During, CardType :: ATTACK, Usertype :: DRACULA , 2, 0, 3 , Make_Effect({new Boost_attack(CharacterType :: Sister  , true)})));

  cards.deck.push_back(Card(CardName::Mistform, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA , 0, 0, 2 , Make_Effect({new ReplaceEffect(2)})));
  cards.deck.push_back(Card(CardName::Mistform, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA , 0, 0, 2 , Make_Effect({new ReplaceEffect(2)})));

  cards.deck.push_back(Card(CardName::Ambush, CardTiming::During, CardType :: ATTACK, Usertype :: ANY , 2, 0, 3 , Make_Effect({new Boost_attack(CharacterType :: Dracula , false)})));
  cards.deck.push_back(Card(CardName::Ambush, CardTiming::During, CardType :: ATTACK, Usertype :: ANY , 2, 0, 3 , Make_Effect({new Boost_attack(CharacterType :: Dracula , false)})));

  cards.deck.push_back(Card(CardName::Baptism_of_blood, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA , 0, 0, 2 , Make_Effect({new HealEffect(2) , new ReplaceEffect(1)})));
  cards.deck.push_back(Card(CardName::Baptism_of_blood, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA , 0, 0, 2 , Make_Effect({new HealEffect(2) , new ReplaceEffect(1)})));

  cards.deck.push_back(Card(CardName::Beastform, CardTiming::During, CardType :: ATTACK, Usertype :: DRACULA , 6, 0, 4 , Make_Effect({new Discard(false)})));
  cards.deck.push_back(Card(CardName::Beastform, CardTiming::During, CardType :: ATTACK, Usertype :: DRACULA , 6, 0, 4 , Make_Effect({new Discard(false)})));

  cards.deck.push_back(Card(CardName::Dash, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 3, 3, 1 , Make_Effect({new Move(3)})));
  cards.deck.push_back(Card(CardName::Dash, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 3, 3, 1 , Make_Effect({new Move(3)})));
  cards.deck.push_back(Card(CardName::Dash, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 3, 3, 1 , Make_Effect({new Move(3)})));

  cards.deck.push_back(Card(CardName::Exploit, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 4, 4, 1 , Make_Effect({new DrawCardEffect(1)})));
  cards.deck.push_back(Card(CardName::Exploit, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 4, 4, 1 , Make_Effect({new DrawCardEffect(1)})));
  cards.deck.push_back(Card(CardName::Exploit, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 4, 4, 1 , Make_Effect({new DrawCardEffect(1)})));

  cards.deck.push_back(Card(CardName::Look_into_my_eyes, CardTiming::During, CardType :: DEFENSE, Usertype :: DRACULA ,0, 1, 2 , Make_Effect({new Boost_deffence()})));
  cards.deck.push_back(Card(CardName::Look_into_my_eyes, CardTiming::During, CardType :: DEFENSE, Usertype :: DRACULA ,0, 1, 2 , Make_Effect({new Boost_deffence()})));
  cards.deck.push_back(Card(CardName::Look_into_my_eyes, CardTiming::During, CardType :: DEFENSE, Usertype :: DRACULA ,0, 1, 2 , Make_Effect({new Boost_deffence()})));

  cards.deck.push_back(Card(CardName::Prey_upon, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA ,0, 0, 4 , Make_Effect({new DamageIfAdjacent(1 , CharacterType :: Dracula)})));
  cards.deck.push_back(Card(CardName::Prey_upon, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA ,0, 0, 4 , Make_Effect({new DamageIfAdjacent(1 , CharacterType :: Dracula)})));

  cards.deck.push_back(Card(CardName::Ravening_Seduction, CardTiming::Immediate, CardType :: EVENT , Usertype :: SISTER ,0, 0, 2 , Make_Effect({new Move(2) , new DamageIfAdjacent(1 , CharacterType :: Sister)})));
  cards.deck.push_back(Card(CardName::Ravening_Seduction, CardTiming::Immediate, CardType :: EVENT , Usertype :: SISTER ,0, 0, 2 , Make_Effect({new Move(2) , new DamageIfAdjacent(1 , CharacterType :: Sister)})));
  cards.deck.push_back(Card(CardName::Ravening_Seduction, CardTiming::Immediate, CardType :: EVENT , Usertype :: SISTER ,0, 0, 2 , Make_Effect({new Move(2) , new DamageIfAdjacent(1 , CharacterType :: Sister)})));

  cards.deck.push_back(Card(CardName::Thirst_for_sustenance, CardTiming::After, CardType :: ATTACK, Usertype :: SISTER ,3, 0, 3 , Make_Effect({new ReplaceEffect(3)})));
  cards.deck.push_back(Card(CardName::Thirst_for_sustenance, CardTiming::After, CardType :: ATTACK, Usertype :: SISTER ,3, 0, 3 , Make_Effect({new ReplaceEffect(3)})));
  cards.deck.push_back(Card(CardName::Thirst_for_sustenance, CardTiming::After, CardType :: ATTACK, Usertype :: SISTER ,3, 0, 3 , Make_Effect({new ReplaceEffect(3)})));

  cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH , Usertype :: ANY ,2, 2, 2 , Make_Effect({new Disable_effects()})));
  cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH , Usertype :: ANY ,2, 2, 2 , Make_Effect({new Disable_effects()})));
  cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH , Usertype :: ANY ,2, 2, 2 , Make_Effect({new Disable_effects()})));
}

void Dracula :: assign_sidekicks() {
  sidekick.clear();
  sidekick.push_back(&sister1);
  sidekick.push_back(&sister2);
  sidekick.push_back(&sister3);
}

vector<Sidekick*> Dracula :: get_sidekick(){
  vector<Sidekick*> sidekicks;
  sidekicks.push_back(&sister1);
  sidekicks.push_back(&sister2);
  sidekicks.push_back(&sister3);
  return sidekicks;
}
