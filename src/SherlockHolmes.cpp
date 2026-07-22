
#include "SherlockHolmes.h"
#include <random>
using namespace std;

SherlockHolmes::SherlockHolmes()
    : Heroes(CharacterType :: SherlockHolmes, Attacktype :: MELEE , Style :: INTEL , 16, 2)
{
    initial_deck();
}


void SherlockHolmes :: initial_deck(){
    cards.deck.push_back(Card(CardName::Administer_Aid, CardTiming::Immediate, CardType :: EVENT , Usertype :: DR_WATSON , 0, 0, 2 , Make_Effect({new ReplaceEffect(4) , new HealEffect(1) , new DrawCardEffect(1)})));
    cards.deck.push_back(Card(CardName::Administer_Aid, CardTiming::Immediate, CardType :: EVENT , Usertype :: DR_WATSON , 0, 0, 2 , Make_Effect({new ReplaceEffect(4) , new HealEffect(1) , new DrawCardEffect(1)})));

    cards.deck.push_back(Card(CardName::Confirm_Suspicion, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 1 , Make_Effect({new ConfirmSuspicionEffect()})));
    cards.deck.push_back(Card(CardName::Confirm_Suspicion, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 1 , Make_Effect({new ConfirmSuspicionEffect()})));
    cards.deck.push_back(Card(CardName::Confirm_Suspicion, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 1 , Make_Effect({new ConfirmSuspicionEffect()})));

    cards.deck.push_back(Card(CardName::Counterpunch, CardTiming::After, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1 , Make_Effect({new DamageIfAdjacent(2 , CharacterType :: SherlockHolmes)})));
    cards.deck.push_back(Card(CardName::Counterpunch, CardTiming::After, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1 , Make_Effect({new DamageIfAdjacent(2 , CharacterType :: SherlockHolmes)})));
    cards.deck.push_back(Card(CardName::Counterpunch, CardTiming::After, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1 , Make_Effect({new DamageIfAdjacent(2 , CharacterType :: SherlockHolmes)})));

    cards.deck.push_back(Card(CardName::Deduce_Strategy, CardTiming::During, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1 , Make_Effect({new DeduceStrategyEffect()})));
    cards.deck.push_back(Card(CardName::Deduce_Strategy, CardTiming::During, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1 , Make_Effect({new DeduceStrategyEffect()})));
    cards.deck.push_back(Card(CardName::Deduce_Strategy, CardTiming::During, CardType :: BOTH , Usertype :: HOLMES , 3, 3, 1 , Make_Effect({new DeduceStrategyEffect()})));

    cards.deck.push_back(Card(CardName::Education_Never_Ends, CardTiming::After, CardType :: BOTH, Usertype :: ANY , 3, 3, 1 , Make_Effect({new DrawDependingOnResult(1 , 2)})));
    cards.deck.push_back(Card(CardName::Education_Never_Ends, CardTiming::After, CardType :: BOTH, Usertype :: ANY , 3, 3, 1 , Make_Effect({new DrawDependingOnResult(1 , 2)})));

    cards.deck.push_back(Card(CardName::Elementary, CardTiming::During, CardType :: DEFENSE, Usertype :: HOLMES , 0, 3, 3 , Make_Effect({new ElementaryEffect()})));
    cards.deck.push_back(Card(CardName::Elementary, CardTiming::During, CardType :: DEFENSE, Usertype :: HOLMES , 0, 3, 3 , Make_Effect({new ElementaryEffect()})));

    cards.deck.push_back(Card(CardName::Eliminate_The_Impossible, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0 , 0, 2 , Make_Effect({new Discard(true)})));
    cards.deck.push_back(Card(CardName::Eliminate_The_Impossible, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0 , 0, 2 , Make_Effect({new Discard(true)})));

    cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH, Usertype :: ANY , 2, 2, 1 , Make_Effect({new Disable_effects()})));
    cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH, Usertype :: ANY , 2, 2, 1 , Make_Effect({new Disable_effects()})));
    cards.deck.push_back(Card(CardName::Feint, CardTiming::Before, CardType :: BOTH, Usertype :: ANY , 2, 2, 1 , Make_Effect({new Disable_effects()})));

    cards.deck.push_back(Card(CardName::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType :: BOTH , Usertype :: DR_WATSON , 3, 3, 1 , Make_Effect({new HealIfAdjency(CharacterType :: SherlockHolmes)})));
    cards.deck.push_back(Card(CardName::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType :: BOTH , Usertype :: DR_WATSON , 3, 3, 1 , Make_Effect({new HealIfAdjency(CharacterType :: SherlockHolmes)})));

    cards.deck.push_back(Card(CardName::Master_of_Disguise, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 2 , Make_Effect({new ReplaceEffect(1) , new DamageEffect(1)})));
    cards.deck.push_back(Card(CardName::Master_of_Disguise, CardTiming::Immediate, CardType :: EVENT , Usertype :: HOLMES , 0, 0, 2 , Make_Effect({new ReplaceEffect(1) , new DamageEffect(1)})));

    cards.deck.push_back(Card(CardName::The_Game_Is_Afoot, CardTiming::After, CardType :: ATTACK, Usertype :: HOLMES , 5, 0, 2 , Make_Effect({new Move(3)})));
    cards.deck.push_back(Card(CardName::The_Game_Is_Afoot, CardTiming::After, CardType :: ATTACK, Usertype :: HOLMES , 5, 0, 2 , Make_Effect({new Move(3)})));

    cards.deck.push_back(Card(CardName::Service_Revolver, CardTiming::During, CardType :: ATTACK, Usertype :: DR_WATSON , 5 , 0, 3 , Make_Effect({})));
    cards.deck.push_back(Card(CardName::Service_Revolver, CardTiming::During, CardType :: ATTACK, Usertype :: DR_WATSON , 5 , 0, 3 , Make_Effect({})));

    cards.deck.push_back(Card(CardName::Study_Methods, CardTiming::After, CardType :: BOTH, Usertype :: ANY , 3, 3, 2 , Make_Effect({new See_the_deck()})));
    cards.deck.push_back(Card(CardName::Study_Methods, CardTiming::After, CardType :: BOTH, Usertype :: ANY , 3, 3, 2 , Make_Effect({new See_the_deck()})));
}

void SherlockHolmes :: assign_sidekicks(){
    sidekick.push_back(&dr_watson);
}

vector<Sidekick*> SherlockHolmes :: get_sidekick(){
    vector<Sidekick *> sidekicks;
    sidekicks.push_back(&dr_watson);
    return sidekicks;
}

