#include "game.h"
#include <iostream>
using namespace std;

int Game :: Rand(int x){
    return rand() % x;
}

Player * Game :: get_player(int x){
    if(x == 1)
        return &player1;
    else 
        return &player2;
}

Player* Game :: get_player_of_hero(CharacterType chtype){
    if(player1.get_hero()->get_name() == chtype)
        return &player1;
    else
        return &player2;
} 

Player * Game :: get_turn(){
    return turn;
}

void Game :: Place_sidekicks_in_hero_zone(Heroes * hero){
    Space * hero_space = board.search_hero(hero);

    if(hero_space == nullptr)
        throw No_Way();

    std :: vector<int> empty_spaces = board.get_empty_spaces_in_zone(hero_space->get_zone());

    for(auto * sidekick : hero->get_sidekick()){
        if(empty_spaces.empty())
            throw NoSpaceException();

        int chosen_id = empty_spaces.front();
        empty_spaces.erase(empty_spaces.begin());

        board.set_Comrade(sidekick , chosen_id);
    }
}

void Game :: choose (pair< int , CharacterType > p1 , pair< int , CharacterType > p2){
    player1.set_name("Player one");
    player2.set_name("Player two");
    if(p1.first < p2.first){
        turn = &player1;
        switch(p1.second){
            case CharacterType :: SherlockHolmes:
                player1.set_age(p1.first);
                player2.set_age(p2.first);
                player1.assign_Characters(CharacterType :: SherlockHolmes);
                player2.assign_Characters(CharacterType :: Dracula);
                board.set_Hero(player1.get_hero() , 4);
                board.set_Hero(player2.get_hero() , 24);
                break;

            case CharacterType :: Dracula:
                player1.set_age(p1.first);
                player2.set_age(p2.first);
                player1.assign_Characters(CharacterType :: Dracula);
                player2.assign_Characters(CharacterType :: SherlockHolmes);
                board.set_Hero(player1.get_hero() , 4);
                board.set_Hero(player2.get_hero() , 24);
                break;
            default:
                break;
        }
    }
    else{
        turn = &player2;
        switch(p2.second){
            case CharacterType :: SherlockHolmes:
                player1.set_age(p1.first);
                player2.set_age(p2.first);
                player2.assign_Characters(CharacterType :: SherlockHolmes);
                player1.assign_Characters(CharacterType :: Dracula);
                board.set_Hero(player2.get_hero() , 4);
                board.set_Hero(player1.get_hero() , 24);
                break;

            case CharacterType :: Dracula:
                player1.set_age(p1.first);
                player2.set_age(p2.first);
                player2.assign_Characters(CharacterType :: Dracula);
                player1.assign_Characters(CharacterType :: SherlockHolmes);
                board.set_Hero(player2.get_hero() , 4);
                board.set_Hero(player1.get_hero() , 24);
                break;
            default:
                break;
        }
    }
}

void Game::inital_hand_cards() {
    auto& cards1 = player1.get_hero()->get_deck_cards();
    auto& cards2 = player2.get_hero()->get_deck_cards();

    for (int i = 0; i < 5; i++) {

        if (!cards1.empty()) {
            int index = Rand(cards1.size());
            std::cout << "cards1 size: " << cards1.size() << '\n';
            std::cout << "index: " << index << '\n';
            player1.add_card(std::move(cards1[index]));
            cards1.erase(cards1.begin() + index);
            std::cout << "Card erased successfully\n";
        }

        if (!cards2.empty()) {
            int index = Rand(cards2.size());

            player2.add_card(std::move(cards2[index]));
            cards2.erase(cards2.begin() + index);
        }
    }
}

Board * Game :: get_Board(){
    return &board;
}

void Game :: DrawCard(Player * player , int x){
    for(int i = 0 ; i < x ; i++){ 
        if(((player->get_hero())->get_deck_cards()).empty()){

            for(auto & it  : player->get_hero()->get_sidekick()){
                it->Damage(2);
            }
            player->get_hero()->Damage(2);
        }
        else{

            int size = ((player->get_hero())->get_deck_cards()).size();
            auto & deck = ((player->get_hero())->get_deck_cards());
            int index = Rand(size);
            player->add_card(std :: move(deck[index]));
            deck.erase(deck.begin() + index);
        }
    }
}

int Game :: Rand_Discard(Player * player ){
    int size = (player->get_hand_cards()).size();
    int index = Rand(size);
    CardName name = player->get_hand_cards()[index].get_CardName();
    return player->remove_card(name);
}

void Game :: Move_characters(int current, int target , CharacterType charactertype , bool allowhiddenway , int cost){
    if(board.is_way(current , target , charactertype , allowhiddenway , cost) == false)
        throw No_Way();
    
    board.Move(current , target);
}

bool Game :: Adjacency(CharacterType ch1, CharacterType ch2){
    return board.Adjacency(ch1 , ch2);
}

bool Game :: All_Adjacency(CharacterType  ch1){
    switch(ch1){
        case CharacterType ::Dracula:
            if(Adjacency(ch1 , CharacterType :: Dr_Watson) || Adjacency(ch1 , CharacterType :: SherlockHolmes))
                return true;
            break;
        case CharacterType ::Dr_Watson:
            if(Adjacency(ch1 , CharacterType :: Dracula) || Adjacency(ch1 , CharacterType :: Sister))
                return true;
            break;
        case CharacterType ::Sister:
            if(Adjacency(ch1 , CharacterType :: Dr_Watson) || Adjacency(ch1 , CharacterType :: SherlockHolmes))
                return true;
            break;
        case CharacterType ::SherlockHolmes:
            if(Adjacency(ch1 , CharacterType :: Dracula) || Adjacency(ch1 , CharacterType :: Sister))
                return true;
            break;
    }
    return false;
} 

void Game :: Replace(int a , int b){
    board.Swap(a , b);
}

void Game :: DecreaseAction(Player * player){
    player->decrease_action(1);
}

void Game :: IncreaseAction(Player * player){
    player->increase_action(1);
}

void Game :: ChangeTurn(){
    if(turn == &player1){
        turn = &player2;
        player1.reset_action();
    }
    else{
        turn = &player1;
        player2.reset_action();
    }
}


