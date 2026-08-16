#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "board/board.h"
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
        void RemoveDefeatedSidekicks();
        void RecordStartOfTurnPositions();
        void RecordHeroAndSidekickPositions(Player *);

    public:

        int Rand(int x);
        Player * get_player(int) ;
        Player * get_turn();
        Player* get_player_of_hero(CharacterType);
        Player* get_owner(CharacterType);
        Player* get_opponent(Player *);
        void choose (CharacterType , CharacterType , int , int );
        void inital_hand_cards();
        Board * get_Board();
        void DrawCard(Player * , int);
        int Rand_Discard(Player *);
        void Move_characters(int , int , CharacterType , bool , int);
        void Move_FogToken(int , int , int);
        bool Adjacency(CharacterType , CharacterType);
        void Replace(int , int);
        void Teleport(int , int);
        void DecreaseAction(Player *);
        void IncreaseAction(Player *);
        void ChangeTurn();

        bool ResolveActingFighter(Player * , Usertype , Heroes *& , Sidekick *& , std :: string &);
        
        bool Maneuver(Player * , std :: string &);
        bool MoveFighter(Player * , int from , int to , std :: string &);

        bool PlayScheme(Player * , int handIndex , int current_space , int target_space , int guessedValue , bool guessAttack , std :: string & err , std :: vector<std :: string> & log , int fogTokenSpace = -1 , int fogTokenDestination = -1);

        bool DeclareAttack(Player * attacker , int attackerSpace , int targetSpace , std :: string & err);
        bool PlayAttackCard(int handIndex , std :: string & err);
        bool PlayDefenseCard(int handIndex , std :: string & err);
        void SkipDefense();
        std :: vector<std :: string> ResolveCombat(int moveDestination = -1, std :: vector<int> boostDiscardIndices = {}, int selfMoveDestination = -1, int fogTokenSpace = -1, int fogTokenDestination = -1, std :: vector<int> codedNotesReturnOrder = {});
        CombatStage get_CombatStage() const;

        bool BloodHarvest(Player * , int targetSpace , std :: string & err);

        bool CanEndTurn(Player *) const;
        bool DiscardExcess(Player * , int handIndex , std :: string & err);
        void EndTurn();

};



#endif
