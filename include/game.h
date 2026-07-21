#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "board.h"
#include "exption_control.h"
class Game
{
    private:
        Player player1;
        Player player2;
        Board board;

        Player * turn;
    public:

        int Rand(int x);
        Player * get_player(int) ;
        Player * get_turn();
        Player* get_player_of_hero(CharacterType);
        void Place_sidekicks_in_hero_zone(Heroes *);
        void choose(std :: pair< int , CharacterType > , std :: pair< int , CharacterType >);
        void inital_hand_cards();
        Board * get_Board();
        void DrawCard(Player * , int);
        int Rand_Discard(Player *);
        void Move_characters(int , int , CharacterType , bool , int);
        bool Adjacency(CharacterType , CharacterType);
        bool All_Adjacency(CharacterType);
        void Replace(int , int);
        void DecreaseAction(Player *);
        void IncreaseAction(Player *);
        void ChangeTurn();
        void Attack_resolver(Heroes * , CharacterType chtype , Card * Ata);
        

        
};



#endif
