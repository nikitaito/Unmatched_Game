
#include "SherlockHolmes.h"
using namespace std;

SherlockHolmes::SherlockHolmes()
    : Heroes("SHERLOCKHOLMES", "MELEE", 16, 2)
{
    deck.push_back(Card(CardType::Administer_Aid, CardTiming::Immediate, "Event", 0, 0, 2));
    deck.push_back(Card(CardType::Administer_Aid, CardTiming::Immediate, "Event", 0, 0, 2));

    deck.push_back(Card(CardType::Confirm_Suspicion, CardTiming::Immediate, "Event", 0, 0, 1));
    deck.push_back(Card(CardType::Confirm_Suspicion, CardTiming::Immediate, "Event", 0, 0, 1));
    deck.push_back(Card(CardType::Confirm_Suspicion, CardTiming::Immediate, "Event", 0, 0, 1));

    deck.push_back(Card(CardType::Counterpunch, CardTiming::After, "Both", 3, 3, 1));
    deck.push_back(Card(CardType::Counterpunch, CardTiming::After, "Both", 3, 3, 1));
    deck.push_back(Card(CardType::Counterpunch, CardTiming::After, "Both", 3, 3, 1));

    deck.push_back(Card(CardType::Deduce_Strategy, CardTiming::During, "Both", 3, 3, 1));
    deck.push_back(Card(CardType::Deduce_Strategy, CardTiming::During, "Both", 3, 3, 1));
    deck.push_back(Card(CardType::Deduce_Strategy, CardTiming::During, "Both", 3, 3, 1));

    deck.push_back(Card(CardType::Education_Never_Ends, CardTiming::After, "Both", 3, 3, 1));
    deck.push_back(Card(CardType::Education_Never_Ends, CardTiming::After, "Both", 3, 3, 1));

    deck.push_back(Card(CardType::Elementary, CardTiming::During, "Defense", 3, 0, 3));
    deck.push_back(Card(CardType::Elementary, CardTiming::During, "Defense", 3, 0, 3));

    deck.push_back(Card(CardType::Eliminate_The_Impossible, CardTiming::Immediate, "Event", 0, 0, 2));
    deck.push_back(Card(CardType::Eliminate_The_Impossible, CardTiming::Immediate, "Event", 0, 0, 2));

    deck.push_back(Card(CardType::Feint, CardTiming::Before, "Both", 2, 2, 1));
    deck.push_back(Card(CardType::Feint, CardTiming::Before, "Both", 2, 2, 1));
    deck.push_back(Card(CardType::Feint, CardTiming::Before, "Both", 2, 2, 1));

    deck.push_back(Card(CardType::Fixed_Point_in_a_Changing_Age, CardTiming::After, "Both", 3, 3, 1));
    deck.push_back(Card(CardType::Fixed_Point_in_a_Changing_Age, CardTiming::After, "Both", 3, 3, 1));

    deck.push_back(Card(CardType::Master_of_Disguise, CardTiming::Immediate, "Event", 0, 0, 2));
    deck.push_back(Card(CardType::Master_of_Disguise, CardTiming::Immediate, "Event", 0, 0, 2));

    deck.push_back(Card(CardType::The_Game_Is_Afoot, CardTiming::After, "Attack", 0, 5, 2));
    deck.push_back(Card(CardType::The_Game_Is_Afoot, CardTiming::After, "Attack", 0, 5, 2));

    deck.push_back(Card(CardType::Service_Revolver, CardTiming::Immediate, "Attack", 0, 5, 2));
    deck.push_back(Card(CardType::Service_Revolver, CardTiming::Immediate, "Attack", 0, 5, 2));

    deck.push_back(Card(CardType::Study_Methods, CardTiming::After, "Both", 3, 3, 2));
    deck.push_back(Card(CardType::Study_Methods, CardTiming::After, "Both", 3, 3, 2));
}
