
#include "SherlockHolmes.h"
#include <random>
using namespace std;

SherlockHolmes::SherlockHolmes()
    : Heroes("SHERLOCKHOLMES", Attacktype :: MELEE , Style :: INTEL , 16, 2)
{
    initial_deck();
}

int SherlockHolmes::discard_hand()
{
    int Boost;

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 4); // 0 - 4
    int randomIndex = dist(rng);

    Boost = cards.hand[randomIndex].get_Boost();
    
    cards.discard.push_back(cards.hand[randomIndex]);

    cards.hand.erase(cards.hand.begin() + randomIndex);

    return Boost;
}

void SherlockHolmes :: initial_deck(){
    cards.deck.push_back(Card(CardName::Administer_Aid, CardTiming::Immediate, CardType :: EVENT , Usertype :: DR_WATSON , 0, 0, 2));
    cards.deck.push_back(Card(CardName::Administer_Aid, CardTiming::Immediate, CardType :: EVENT , Usertype :: DR_WATSON , 0, 0, 2));

    cards.deck.push_back(Card(CardName::Confirm_Suspicion, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 1));
    cards.deck.push_back(Card(CardName::Confirm_Suspicion, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 1));
    cards.deck.push_back(Card(CardName::Confirm_Suspicion, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 1));

    cards.deck.push_back(Card(CardName::Counterpunch, CardTiming::After, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1));
    cards.deck.push_back(Card(CardName::Counterpunch, CardTiming::After, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1));
    cards.deck.push_back(Card(CardName::Counterpunch, CardTiming::After, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1));

    cards.deck.push_back(Card(CardName::Deduce_Strategy, CardTiming::During, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1));
    cards.deck.push_back(Card(CardName::Deduce_Strategy, CardTiming::During, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1));
    cards.deck.push_back(Card(CardName::Deduce_Strategy, CardTiming::During, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1));

    cards.deck.push_back(Card(CardName::Education_Never_Ends, CardTiming::After, CardType :: BOTH, Usertype :: ANY , 3, 3, 1));
    cards.deck.push_back(Card(CardName::Education_Never_Ends, CardTiming::After, CardType :: BOTH, Usertype :: ANY , 3, 3, 1));

    cards.deck.push_back(Card(CardName::Elementary, CardTiming::During, CardType :: DEFENSE, Usertype :: HOLMES , 3, 0, 3));
    cards.deck.push_back(Card(CardName::Elementary, CardTiming::During, CardType :: DEFENSE, Usertype :: HOLMES , 3, 0, 3));

    cards.deck.push_back(Card(CardName::Eliminate_The_Impossible, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0 , 0, 2));
    cards.deck.push_back(Card(CardName::Eliminate_The_Impossible, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0 , 0, 2));

    cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH, Usertype :: ANY , 2, 2, 1));
    cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH, Usertype :: ANY , 2, 2, 1));
    cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH, Usertype :: ANY , 2, 2, 1));

    cards.deck.push_back(Card(CardName::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType :: BOTH , Usertype :: DR_WATSON , 3, 3, 1));
    cards.deck.push_back(Card(CardName::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType :: BOTH , Usertype :: DR_WATSON , 3, 3, 1));

    cards.deck.push_back(Card(CardName::Master_of_Disguise, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 2));
    cards.deck.push_back(Card(CardName::Master_of_Disguise, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 2));

    cards.deck.push_back(Card(CardName::The_Game_Is_Afoot, CardTiming::After, CardType :: ATTACK, Usertype :: HOLMES , 0, 5, 2));
    cards.deck.push_back(Card(CardName::The_Game_Is_Afoot, CardTiming::After, CardType :: ATTACK, Usertype :: HOLMES , 0, 5, 2));

    cards.deck.push_back(Card(CardName::Service_Revolver, CardTiming::Immediate, CardType :: ATTACK, Usertype :: DR_WATSON , 0 , 5, 2));
    cards.deck.push_back(Card(CardName::Service_Revolver, CardTiming::Immediate, CardType :: ATTACK, Usertype :: DR_WATSON , 0 , 5, 2));

    cards.deck.push_back(Card(CardName::Study_Methods, CardTiming::After, CardType :: BOTH, Usertype :: ANY , 3, 3, 2));
    cards.deck.push_back(Card(CardName::Study_Methods, CardTiming::After, CardType :: BOTH, Usertype :: ANY , 3, 3, 2));
}

void SherlockHolmes :: initial_sidekicks(){
    sidekick.push_back(Sidekick("Dr_Watson", Attacktype :: RANGED , 8, 2));
}

