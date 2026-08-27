#include "game/SaveLoad.h"
#include <fstream>

using json = nlohmann :: json;

void to_json(json & j, const CardSaveData & c){
    j = json{
        { "name", c.name },
        { "attack", c.attack },
        { "defense", c.defense },
        { "boost", c.boost },
        { "applyEffects", c.applyEffects },
        { "valueLocked", c.valueLocked },
    };
}

void from_json(const json & j, CardSaveData & c){
    j.at("name").get_to(c.name);
    j.at("attack").get_to(c.attack);
    j.at("defense").get_to(c.defense);
    j.at("boost").get_to(c.boost);
    c.applyEffects = j.value("applyEffects", true);
    c.valueLocked = j.value("valueLocked", false);
}

void to_json(json & j, const SidekickSaveData & s){
    j = json{
        { "type", s.type },
        { "health", s.health },
        { "startTurnSpace", s.startTurnSpace },
        { "boardSpace", s.boardSpace },
    };
}

void from_json(const json & j, SidekickSaveData & s){
    j.at("type").get_to(s.type);
    j.at("health").get_to(s.health);
    s.startTurnSpace = j.value("startTurnSpace", -1);
    s.boardSpace = j.value("boardSpace", -1);
}

void to_json(json & j, const HeroSaveData & h){
    j = json{
        { "type", h.type },
        { "health", h.health },
        { "startTurnSpace", h.startTurnSpace },
        { "boardSpace", h.boardSpace },
        { "deck", h.deck },
        { "topOfDeck", h.topOfDeck },
        { "sidekicks", h.sidekicks },
    };
}

void from_json(const json & j, HeroSaveData & h){
    j.at("type").get_to(h.type);
    j.at("health").get_to(h.health);
    h.startTurnSpace = j.value("startTurnSpace", -1);
    h.boardSpace = j.value("boardSpace", -1);
    j.at("deck").get_to(h.deck);
    j.at("topOfDeck").get_to(h.topOfDeck);
    j.at("sidekicks").get_to(h.sidekicks);
}

void to_json(json & j, const PlayerSaveData & p){
    j = json{
        { "name", p.name },
        { "action", p.action },
        { "hero", p.hero },
        { "hand", p.hand },
        { "discard", p.discard },
    };
}

void from_json(const json & j, PlayerSaveData & p){
    j.at("name").get_to(p.name);
    p.action = j.value("action", 2);
    j.at("hero").get_to(p.hero);
    j.at("hand").get_to(p.hand);
    j.at("discard").get_to(p.discard);
}

void to_json(json & j, const GameSaveData & g){
    j = json{
        { "saveVersion", 1 },
        { "player1", g.player1 },
        { "player2", g.player2 },
        { "player1Turn", g.player1Turn },
        { "bloodHarvestUsedThisTurn", g.bloodHarvestUsedThisTurn },
        { "gameOver", g.gameOver },
        { "winner", g.winner },
    };
}

void from_json(const json & j, GameSaveData & g){
    j.at("player1").get_to(g.player1);
    j.at("player2").get_to(g.player2);
    g.player1Turn = j.value("player1Turn", true);
    g.bloodHarvestUsedThisTurn = j.value("bloodHarvestUsedThisTurn", false);
    g.gameOver = j.value("gameOver", false);
    g.winner = j.value("winner", 0);
}

bool WriteGameSaveJson(const GameSaveData & data, const std :: string & filePath){
    std :: ofstream file(filePath, std :: ios :: out | std :: ios :: trunc | std :: ios :: binary);
    if(!file.is_open())
        return false;

    json j = data;
    file << j.dump(2);
    return file.good();
}

bool ReadGameSaveJson(const std :: string & filePath, GameSaveData & outData){
    std :: ifstream file(filePath, std :: ios :: in | std :: ios :: binary);
    if(!file.is_open())
        return false;

    try{
        json j;
        file >> j;
        GameSaveData data = j.get<GameSaveData>();
        outData = std :: move(data);
    }
    catch(const std :: exception &){
        return false;
    }
    return true;
}
