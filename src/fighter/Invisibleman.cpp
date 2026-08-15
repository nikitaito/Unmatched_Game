
#include "fighter/Invisibleman.h"
#include <random>
using namespace std;

Invman::Invman()
    : Heroes(CharacterType :: Invman , Attacktype :: MELEE , Style :: STEALTH , 15 , 2)
{
    initial_deck();
}

void Invman :: initial_deck() {
    cards.deck.push_back(Card(CardName :: Coded_Notes , CardTiming :: After , CardType :: DEFENSE , Usertype :: INVMAN , 0 , 3 , 2 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Coded_Notes , CardTiming :: After , CardType :: DEFENSE , Usertype :: INVMAN , 0 , 3 , 2 , Make_Effect({})));

    cards.deck.push_back(Card(CardName :: ConFound , CardTiming :: After , CardType :: BOTH , Usertype :: INVMAN , 3 , 3 , 2 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: ConFound , CardTiming :: After , CardType :: BOTH , Usertype :: INVMAN , 3 , 3 , 2 , Make_Effect({}))); 


    cards.deck.push_back(Card(CardName :: Covert_PreParation , CardTiming :: After , CardType :: BOTH , Usertype :: INVMAN , 2, 2 , 1 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Covert_PreParation , CardTiming :: After , CardType :: BOTH , Usertype :: INVMAN , 2, 2 , 1 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Covert_PreParation , CardTiming :: After , CardType :: BOTH , Usertype :: INVMAN , 2, 2 , 1 , Make_Effect({})));

    cards.deck.push_back(Card(CardName :: Deaming_of_Revenge , CardTiming :: After , CardType :: BOTH , Usertype :: INVMAN , 3, 3 , 1 , Make_Effect({new DamageIfOnFog(1)})));
    cards.deck.push_back(Card(CardName :: Deaming_of_Revenge , CardTiming :: After , CardType :: BOTH , Usertype :: INVMAN , 3, 3 , 1 , Make_Effect({new DamageIfOnFog(1)})));

    cards.deck.push_back(Card(CardName :: Emerge_from_Mist , CardTiming :: During , CardType :: ATTACK , Usertype :: INVMAN , 3, 0 , 2 , Make_Effect({new EmergeFromMistEffect()})));
    cards.deck.push_back(Card(CardName :: Emerge_from_Mist , CardTiming :: During , CardType :: ATTACK , Usertype :: INVMAN , 3, 0 , 2 , Make_Effect({new EmergeFromMistEffect()})));

    cards.deck.push_back(Card(CardName :: Impossible_to_See , CardTiming :: Before , CardType :: BOTH , Usertype :: INVMAN , 2, 2 , 2 , Make_Effect({new ImpossibleToSeeEffect()})));
    cards.deck.push_back(Card(CardName :: Impossible_to_See , CardTiming :: Before , CardType :: BOTH , Usertype :: INVMAN , 2, 2 , 2 , Make_Effect({new ImpossibleToSeeEffect()})));

    cards.deck.push_back(Card(CardName :: Into_Thin_Air , CardTiming :: After , CardType :: DEFENSE , Usertype :: INVMAN , 0, 4 , 1 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Into_Thin_Air , CardTiming :: After , CardType :: DEFENSE , Usertype :: INVMAN , 0, 4 , 1 , Make_Effect({})));

    cards.deck.push_back(Card(CardName :: Lurking , CardTiming :: After , CardType :: DEFENSE , Usertype :: INVMAN , 0, 2 , 2 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Lurking , CardTiming :: After , CardType :: DEFENSE , Usertype :: INVMAN , 0, 2 , 2 , Make_Effect({})));

    cards.deck.push_back(Card(CardName :: Reign_of_Terror , CardTiming :: Immediate , CardType :: EVENT , Usertype :: INVMAN , 0, 0 , 1 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Reign_of_Terror , CardTiming :: Immediate , CardType :: EVENT , Usertype :: INVMAN , 0, 0 , 1 , Make_Effect({})));

    cards.deck.push_back(Card(CardName :: Rolling_Fog , CardTiming :: Immediate , CardType :: EVENT , Usertype :: INVMAN , 0, 0 , 1 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Rolling_Fog , CardTiming :: Immediate , CardType :: EVENT , Usertype :: INVMAN , 0, 0 , 1 , Make_Effect({})));

    cards.deck.push_back(Card(CardName :: Slip_Away , CardTiming :: After , CardType :: ATTACK , Usertype :: INVMAN , 3, 0 , 2 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Slip_Away , CardTiming :: After , CardType :: ATTACK , Usertype :: INVMAN , 3, 0 , 2 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Slip_Away , CardTiming :: After , CardType :: ATTACK , Usertype :: INVMAN , 3, 0 , 2 , Make_Effect({})));

    cards.deck.push_back(Card(CardName :: Step_Lightly , CardTiming :: Immediate , CardType :: EVENT , Usertype :: INVMAN , 0, 0 , 1 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Step_Lightly , CardTiming :: Immediate , CardType :: EVENT , Usertype :: INVMAN , 0, 0 , 1 , Make_Effect({})));

    cards.deck.push_back(Card(CardName :: Vanish , CardTiming :: Immediate , CardType :: EVENT , Usertype :: INVMAN , 0, 0 , 3 , Make_Effect({})));
    cards.deck.push_back(Card(CardName :: Vanish , CardTiming :: Immediate , CardType :: EVENT , Usertype :: INVMAN , 0, 0 , 3 , Make_Effect({})));
}

void Invman :: assign_sidekicks(){
    sidekick.clear();
    sidekick.push_back(&token1);
    sidekick.push_back(&token2);
    sidekick.push_back(&token3);
}

vector<Sidekick*> Invman :: get_sidekick(){
    vector<Sidekick *> tokens;
    tokens.push_back(&token1);
    tokens.push_back(&token2);
    tokens.push_back(&token3);
    return tokens;
}
