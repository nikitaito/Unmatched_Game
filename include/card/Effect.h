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

    Heroes* mover_hero = nullptr;
    Sidekick* mover_sidekick = nullptr;

    Game* game = nullptr;

    Card* attackCard = nullptr;
    Card* defenseCard = nullptr;
    Card* effectCard = nullptr;

    std :: vector<CardName> remove ;
    std :: vector<int> removeBoosts ; // Boost value of each card in `remove`, same index order (used by Discard(false))

    /// move information
    int current_space = -1;
    int target_space = -1;
    CharacterType chtype = CharacterType::SherlockHolmes;
    bool Allow_hidden_way = false;

    int move_override_target = -1;

    int self_move_destination = -1;
    int fog_token_space = -1;
    int fog_token_destination = -1;

    int second_fog_token_space = -1;
    int second_fog_token_destination = -1;

    std :: vector<int> codedNotesReturnOrder;

    int guessedValue = 0;
    bool guessAttack = true;      
    bool ignoreAttack = false;   
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

class ReviveSisterEffect : public Effect
{
    public:
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


class ConfirmSuspicionEffect : public Effect
{
    public:
        virtual void execute(Context &) override;
};


class ElementaryEffect : public Effect
{
    public:
        virtual void execute(Context &) override;
};

class DeduceStrategyEffect : public Effect
{
    public:
        virtual void execute(Context &) override;
};

class DamageIfOnFog : public Effect
{
    private:
        int damage;
    public:
        DamageIfOnFog(int);
        virtual void execute(Context & ctx) override;
};

class EmergeFromMistEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class ImpossibleToSeeEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class SelfMoveEffect : public Effect
{
    private:
        int cost;
    public:
        SelfMoveEffect(int);
        virtual void execute(Context & ctx) override;
};

class MoveFogTokenEffect : public Effect
{
    private:
        int cost;                    
        bool requireEmptyDestination; 
    public:
        MoveFogTokenEffect(int , bool);
        virtual void execute(Context & ctx) override;
};

class PlaceSelfOnFogTokenEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class GainActionEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class MoveToFogTokenSpaceEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class CodedNotesEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class ConfoundEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class CovertPreparationEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class StepLightlyEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

class VanishEffect : public Effect
{
    public:
        virtual void execute(Context & ctx) override;
};

std :: vector<std :: unique_ptr<Effect>> Make_Effect(std :: vector<Effect *> effects);


#endif 
