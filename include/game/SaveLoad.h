#ifndef GAME_SAVE_LOAD_H
#define GAME_SAVE_LOAD_H

#include "Enums.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>


struct CardSaveData
{
    CardName name{};
    int  attack = 0;
    int  defense = 0;
    int  boost = 0;
    bool applyEffects = true;
    bool valueLocked = false;
};

struct SidekickSaveData
{
    CharacterType type{};
    int  health = 0;
    int  startTurnSpace = -1;
    int  boardSpace = -1;   
};

struct HeroSaveData
{
    CharacterType type{};
    int  health = 0;
    int  startTurnSpace = -1;
    int  boardSpace = -1;

    std :: vector<CardSaveData> deck;
    std :: vector<CardSaveData> topOfDeck;
    std :: vector<SidekickSaveData> sidekicks;
};

struct PlayerSaveData
{
    std :: string name;
    int action = 2;

    HeroSaveData hero;

    std :: vector<CardSaveData> hand;
    std :: vector<CardSaveData> discard;
};

struct GameSaveData
{
    PlayerSaveData player1;
    PlayerSaveData player2;

    bool player1Turn = true;
    bool bloodHarvestUsedThisTurn = false;

    bool gameOver = false;
    int  winner = 0; 
};

NLOHMANN_JSON_SERIALIZE_ENUM(CardName, {
    {CardName :: Feedingfrenzy, "Feedingfrenzy"},
    {CardName :: Mistform, "Mistform"},
    {CardName :: Ambush, "Ambush"},
    {CardName :: Baptism_of_blood, "Baptism_of_blood"},
    {CardName :: Beastform, "Beastform"},
    {CardName :: Dash, "Dash"},
    {CardName :: Exploit, "Exploit"},
    {CardName :: Look_into_my_eyes, "Look_into_my_eyes"},
    {CardName :: Prey_upon, "Prey_upon"},
    {CardName :: Ravening_Seduction, "Ravening_Seduction"},
    {CardName :: Thirst_for_sustenance, "Thirst_for_sustenance"},

    {CardName :: Administer_Aid, "Administer_Aid"},
    {CardName :: Confirm_Suspicion, "Confirm_Suspicion"},
    {CardName :: Counterpunch, "Counterpunch"},
    {CardName :: Deduce_Strategy, "Deduce_Strategy"},
    {CardName :: Education_Never_Ends, "Education_Never_Ends"},
    {CardName :: Elementary, "Elementary"},
    {CardName :: Eliminate_The_Impossible, "Eliminate_The_Impossible"},
    {CardName :: Feint, "Feint"},
    {CardName :: Fixed_Point_in_a_Changing_Age, "Fixed_Point_in_a_Changing_Age"},
    {CardName :: Master_of_Disguise, "Master_of_Disguise"},
    {CardName :: The_Game_Is_Afoot, "The_Game_Is_Afoot"},
    {CardName :: Service_Revolver, "Service_Revolver"},
    {CardName :: Study_Methods, "Study_Methods"},

    {CardName :: Coded_Notes, "Coded_Notes"},
    {CardName :: ConFound, "ConFound"},
    {CardName :: Covert_PreParation, "Covert_PreParation"},
    {CardName :: Deaming_of_Revenge, "Deaming_of_Revenge"},
    {CardName :: Emerge_from_Mist, "Emerge_from_Mist"},
    {CardName :: Impossible_to_See, "Impossible_to_See"},
    {CardName :: Into_Thin_Air, "Into_Thin_Air"},
    {CardName :: Lurking, "Lurking"},
    {CardName :: Reign_of_Terror, "Reign_of_Terror"},
    {CardName :: Rolling_Fog, "Rolling_Fog"},
    {CardName :: Slip_Away, "Slip_Away"},
    {CardName :: Step_Lightly, "Step_Lightly"},
    {CardName :: Vanish, "Vanish"},
})

NLOHMANN_JSON_SERIALIZE_ENUM(CharacterType, {
    {CharacterType :: SherlockHolmes, "SherlockHolmes"},
    {CharacterType :: Dracula, "Dracula"},
    {CharacterType :: Dr_Watson, "Dr_Watson"},
    {CharacterType :: Sister, "Sister"},
    {CharacterType :: Invman, "Invman"},
    {CharacterType :: InvmanToken, "InvmanToken"},
})


void to_json(nlohmann :: json & j, const CardSaveData & c);
void from_json(const nlohmann :: json & j, CardSaveData & c);

void to_json(nlohmann :: json & j, const SidekickSaveData & s);
void from_json(const nlohmann :: json & j, SidekickSaveData & s);

void to_json(nlohmann :: json & j, const HeroSaveData & h);
void from_json(const nlohmann :: json & j, HeroSaveData & h);

void to_json(nlohmann :: json & j, const PlayerSaveData & p);
void from_json(const nlohmann :: json & j, PlayerSaveData & p);

void to_json(nlohmann :: json & j, const GameSaveData & g);
void from_json(const nlohmann :: json & j, GameSaveData & g);

bool WriteGameSaveJson(const GameSaveData & data, const std :: string & filePath);
bool ReadGameSaveJson(const std :: string & filePath, GameSaveData & outData);

#endif
