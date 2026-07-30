#ifndef EFECT_H
#define EFECT_H

class Player;
class Heroes;
class Sidekick;
class Game;
class Card;
#include"Enums.h"
#include<functional>
#include<memory>
#include<vector>
#include<string>

struct  Context
{
    Player* ownplayer = nullptr;
    Player* targetplayer = nullptr;
    CombatResult result = CombatResult::Tie;

    Heroes* ownhero = nullptr;
    Sidekick* ownsidekick = nullptr;
    Heroes* targethero = nullptr;
    Sidekick* targetsidekick = nullptr;

    Game* game = nullptr;

    Card* attackCard = nullptr;
    Card* defenseCard = nullptr;
    Card* effectCard = nullptr;

    std :: vector<CardName> remove ;

    /// move information
    int current_space = -1;
    int target_space = -1;
    CharacterType chtype = CharacterType::SherlockHolmes;
    bool Allow_hidden_way = false;

    /// prediction / information cards (Confirm Suspicion, Elementary)
    int guessedValue = 0;
    bool guessAttack = true;      // true: naming an Attack value, false: a Defense value
    bool ignoreAttack = false;    // set by Elementary when the prediction is correct
    std :: vector<std :: string> log;

};



class Effect
{
    public:
        virtual ~Effect() = default;
        virtual void execute(Context & ) = 0;
};

class HealEffect : public Effect
{
    private:
        int amount;
    public:
        HealEffect(int);
        virtual void execute(Context &) override;
};

class HealIfAdjency : public Effect
{
    private:
        CharacterType chtype;   
    public:
        HealIfAdjency(CharacterType);
        virtual void execute(Context & ) override;

};

class DrawCardEffect : public Effect
{
    private:
        int count;
    public:
        DrawCardEffect(int);
        virtual void execute(Context & ) override;
};

class DrawDependingOnResult : public Effect
{
    private:
        int winDraw;
        int loseDraw;
    public:
        DrawDependingOnResult(int, int);
        void execute(Context& ) override;
};

class Discard : public Effect
{
    private:
        bool justremove;
    public:
        Discard(bool);
        virtual void execute(Context &) override;
        
};

class Boost_attack : public Effect
{
    private : 
        CharacterType chtype;
        bool  sistermode;
    public:
        Boost_attack(CharacterType , bool);
        virtual void execute (Context &) override;
};

class Boost_deffence : public Effect
{
    public:
        virtual void execute (Context &) override;
        
};

class Move : public Effect
{
    private:
        int cost;
    public:
        Move(int);
        virtual void execute(Context & ) override;
};

class ReplaceEffect : public Effect{
    private:
        int mode;
    public :
        ReplaceEffect(int);
        virtual void execute(Context & ) override;
};

class DamageEffect : public Effect
{
    private:
        int amount;
    public : 
        DamageEffect(int);
        virtual void execute(Context &) override;
};

class DamageIfAdjacent : public Effect
{
    
    private:
        int damage;
        CharacterType chtype;
    public:
        DamageIfAdjacent(int , CharacterType);
        virtual void execute(Context & ctx) override;
};

class Disable_effects : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class See_the_deck : public Effect
{
    public:
        virtual void execute(Context &) override;
};

// Confirm Suspicion: name an Attack or Defense value; the opponent must discard a
// card that prints that value (damage = discarded card's Boost). If no matching
// card exists, the opponent's hand is revealed instead (logged, no state change).
class ConfirmSuspicionEffect : public Effect
{
    public:
        virtual void execute(Context &) override;
};

// Elementary: name the opponent's printed Attack value before it is revealed.
// If correct, the attack is ignored for damage purposes and all effects on the
// opposing combat card are cancelled.
class ElementaryEffect : public Effect
{
    public:
        virtual void execute(Context &) override;
};

// Deduce Strategy: replace the opponent's printed Attack or Defense value
// (whichever role their card is playing) with this card's own Boost value.
class DeduceStrategyEffect : public Effect
{
    public:
        virtual void execute(Context &) override;
};



std :: vector<std :: unique_ptr<Effect>> Make_Effect(std :: vector<Effect *> effects);


#endif 
