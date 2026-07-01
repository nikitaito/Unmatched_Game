
#include "Dracula.h"
#include <random>
using namespace std;

Dracula::Dracula()
    : Heroes("DRACULA", Attacktype :: MELEE , Style :: ARRGD , 13, 2)
{
    initial_deck();
}

vector<Sidekick> Dracula::get_sisters()
{
  return sidekick;
}

void Dracula::DrawnCard()
{
  cards.hand.push_back(cards.deck.front());
  cards.hand.erase(cards.hand.begin());
}

void Dracula :: initial_deck() {
  cards.deck.push_back(Card(CardName::Feedingfrenzy, CardTiming::During, CardType :: ATTACK, Usertype :: DRACULA , 2, 0, 3));
  cards.deck.push_back(Card(CardName::Feedingfrenzy, CardTiming::During, CardType :: ATTACK, Usertype :: DRACULA , 2, 0, 3));

  cards.deck.push_back(Card(CardName::Mistform, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA , 0, 0, 2));
  cards.deck.push_back(Card(CardName::Mistform, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA , 0, 0, 2));

  cards.deck.push_back(Card(CardName::Ambush, CardTiming::During, CardType :: ATTACK, Usertype :: ANY ,2, 0, 3));
  cards.deck.push_back(Card(CardName::Ambush, CardTiming::During, CardType :: ATTACK, Usertype :: ANY , 2, 0, 3));

  cards.deck.push_back(Card(CardName::Baptism_of_blood, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA , 0, 0, 2));
  cards.deck.push_back(Card(CardName::Baptism_of_blood, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA , 0, 0, 2));

  cards.deck.push_back(Card(CardName::Beastform, CardTiming::During, CardType :: ATTACK, Usertype :: DRACULA , 6, 0, 4));
  cards.deck.push_back(Card(CardName::Beastform, CardTiming::During, CardType :: ATTACK, Usertype :: DRACULA , 6, 0, 4));

  cards.deck.push_back(Card(CardName::Dash, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 3, 3, 1));
  cards.deck.push_back(Card(CardName::Dash, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 3, 3, 1));
  cards.deck.push_back(Card(CardName::Dash, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 3, 3, 1));

  cards.deck.push_back(Card(CardName::Exploit, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 4, 4, 1));
  cards.deck.push_back(Card(CardName::Exploit, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 4, 4, 1));
  cards.deck.push_back(Card(CardName::Exploit, CardTiming::After, CardType :: BOTH , Usertype :: ANY , 4, 4, 1));

  cards.deck.push_back(Card(CardName::Look_into_my_eyes, CardTiming::During, CardType :: DEFENSE, Usertype :: DRACULA ,1, 0, 2));
  cards.deck.push_back(Card(CardName::Look_into_my_eyes, CardTiming::During, CardType :: DEFENSE, Usertype :: DRACULA ,1, 0, 2));
  cards.deck.push_back(Card(CardName::Look_into_my_eyes, CardTiming::During, CardType :: DEFENSE, Usertype :: DRACULA ,1, 0, 2));

  cards.deck.push_back(Card(CardName::Prey_upon, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA ,0, 0, 4));
  cards.deck.push_back(Card(CardName::Prey_upon, CardTiming::Immediate, CardType :: EVENT , Usertype :: DRACULA ,0, 0, 4));

  cards.deck.push_back(Card(CardName::Ravening_Seduction, CardTiming::Immediate, CardType :: EVENT , Usertype :: SISTER ,0, 0, 2));
  cards.deck.push_back(Card(CardName::Ravening_Seduction, CardTiming::Immediate, CardType :: EVENT , Usertype :: SISTER ,0, 0, 2));
  cards.deck.push_back(Card(CardName::Ravening_Seduction, CardTiming::Immediate, CardType :: EVENT , Usertype :: SISTER ,0, 0, 2));

  cards.deck.push_back(Card(CardName::Thirst_for_sustenance, CardTiming::After, CardType :: ATTACK, Usertype :: SISTER ,0, 3, 3));
  cards.deck.push_back(Card(CardName::Thirst_for_sustenance, CardTiming::After, CardType :: ATTACK, Usertype :: SISTER ,0, 3, 3));
  cards.deck.push_back(Card(CardName::Thirst_for_sustenance, CardTiming::After, CardType :: ATTACK, Usertype :: SISTER ,0, 3, 3));

  cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH , Usertype :: ANY ,2, 2, 2));
  cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH , Usertype :: ANY ,2, 2, 2));
  cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH , Usertype :: ANY ,2, 2, 2));
}

void Dracula :: initial_sidekicks() {
    sidekick.push_back(Sidekick("SISTER1", Attacktype :: MELEE, 1, 2));
    sidekick.push_back(Sidekick("SISTER2", Attacktype :: MELEE, 1, 2));
    sidekick.push_back(Sidekick("SISTER3", Attacktype :: MELEE, 1, 2));
}
