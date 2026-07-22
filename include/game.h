#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "board.h"
#include "exption_control.h"
#include <string>
#include <vector>

class Game
{
    private:
        Player player1;
        Player player2;
        Board board;

        Player * turn;

        // -- combat engine state (only one combat can be in progress at a time) --
        CombatStage combatStage = CombatStage::None;
        Player * combatAttackerPlayer = nullptr;
        Player * combatDefenderPlayer = nullptr;
        Heroes * combatAttackerHero = nullptr;
        Sidekick * combatAttackerSidekick = nullptr;
        Heroes * combatDefenderHero = nullptr;
        Sidekick * combatDefenderSidekick = nullptr;
        int combatAttackerSpace = -1;
        int combatDefenderSpace = -1;
        Card combatAttackCard;
        Card combatDefenseCard;
        bool combatHasDefense = false;

        bool bloodHarvestUsedThisTurn = false;

        void PlaceStartingSidekicks(Player * , int heroSpace);
        Usertype UsertypeOf(CharacterType) const;

    public:

        int Rand(int x);
        Player * get_player(int) ;
        Player * get_turn();
        Player* get_player_of_hero(CharacterType);
        Player* get_owner(CharacterType);
        Player* get_opponent(Player *);
        void choose(std :: pair< int , CharacterType > , std :: pair< int , CharacterType >);
        void inital_hand_cards();
        Board * get_Board();
        void DrawCard(Player * , int);
        int Rand_Discard(Player *);
        void Move_characters(int , int , CharacterType , bool , int);
        bool Adjacency(CharacterType , CharacterType);
        void Replace(int , int);
        void Teleport(int , int);
        void DecreaseAction(Player *);
        void IncreaseAction(Player *);
        void ChangeTurn();

        // -- fighter / ownership resolution used by Scheme + Attack + Blood Harvest --
        bool ResolveActingFighter(Player * , Usertype , Heroes *& , Sidekick *& , std :: string &);

        // -- Maneuver action --
        bool Maneuver(Player * , std :: string &);
        bool MoveFighter(Player * , int from , int to , std :: string &);

        // -- Scheme action --
        bool PlayScheme(Player * , int handIndex , int current_space , int target_space ,
                         int guessedValue , bool guessAttack , std :: string & err , std :: vector<std :: string> & log);

        // -- Attack action / combat engine --
        bool DeclareAttack(Player * attacker , int attackerSpace , int targetSpace , std :: string & err);
        bool PlayAttackCard(int handIndex , std :: string & err);
        bool PlayDefenseCard(int handIndex , std :: string & err);
        void SkipDefense();
        std :: vector<std :: string> ResolveCombat();
        CombatStage get_CombatStage() const;

        // -- Dracula's Blood Harvest (start-of-turn optional ability) --
        bool BloodHarvest(Player * , int targetSpace , std :: string & err);

        // -- End of turn --
        bool CanEndTurn(Player *) const;
        bool DiscardExcess(Player * , int handIndex , std :: string & err);
        void EndTurn();

};



#endif
