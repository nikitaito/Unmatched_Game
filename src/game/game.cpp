#include "game/game.h"
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

void Game :: choose (CharacterType ch1 , CharacterType ch2 , int position1 , int position2){

    player1.set_name("Player one");
    player2.set_name("Player two");

    turn = &player1;

    player1.assign_Characters(ch1);
    player2.assign_Characters(ch2);
    board.set_Hero(player1.get_hero() , position1);
    board.set_Hero(player2.get_hero() , position2);
    PlaceStartingSidekicks(&player1 , position1);
    PlaceStartingSidekicks(&player2 , position2);

    // switch(ch2){
    //     case CharacterType :: SherlockHolmes:
    //         // player1.set_age(p1.first);
    //         // player2.set_age(p2.first);
    //         player1.assign_Characters(ch1);
    //         player2.assign_Characters(ch2);
    //         board.set_Hero(player1.get_hero() , 4);
    //         board.set_Hero(player2.get_hero() , 24);
    //         PlaceStartingSidekicks(&player1 , 4);
    //         PlaceStartingSidekicks(&player2 , 24);
    //         break;

    //     case CharacterType :: Dracula:
    //         // player1.set_age(p1.first);
    //         // player2.set_age(p2.first);
    //         player1.assign_Characters(c);
    //         player2.assign_Characters(CharacterType :: SherlockHolmes);
    //         board.set_Hero(player1.get_hero() , 4);
    //         board.set_Hero(player2.get_hero() , 24);
    //         PlaceStartingSidekicks(&player1 , 4);
    //         PlaceStartingSidekicks(&player2 , 24);
    //         break;
    //     default:
    //         break;
    // }

    // ///////////
    // player1.set_name("Player one");
    // player2.set_name("Player two");
    // if(p1.first < p2.first){
    //     turn = &player1;
    //     switch(p1.second){
    //         case CharacterType :: SherlockHolmes:
    //             player1.set_age(p1.first);
    //             player2.set_age(p2.first);
    //             player1.assign_Characters(CharacterType :: SherlockHolmes);
    //             player2.assign_Characters(CharacterType :: Dracula);
    //             board.set_Hero(player1.get_hero() , 4);
    //             board.set_Hero(player2.get_hero() , 24);
    //             PlaceStartingSidekicks(&player1 , 4);
    //             PlaceStartingSidekicks(&player2 , 24);
    //             break;

    //         case CharacterType :: Dracula:
    //             player1.set_age(p1.first);
    //             player2.set_age(p2.first);
    //             player1.assign_Characters(CharacterType :: Dracula);
    //             player2.assign_Characters(CharacterType :: SherlockHolmes);
    //             board.set_Hero(player1.get_hero() , 4);
    //             board.set_Hero(player2.get_hero() , 24);
    //             PlaceStartingSidekicks(&player1 , 4);
    //             PlaceStartingSidekicks(&player2 , 24);
    //             break;
    //         default:
    //             break;
    //     }
    // }
    // else{
    //     turn = &player2;
    //     switch(p2.second){
    //         case CharacterType :: SherlockHolmes:
    //             player1.set_age(p1.first);
    //             player2.set_age(p2.first);
    //             player2.assign_Characters(CharacterType :: SherlockHolmes);
    //             player1.assign_Characters(CharacterType :: Dracula);
    //             board.set_Hero(player2.get_hero() , 4);
    //             board.set_Hero(player1.get_hero() , 24);
    //             PlaceStartingSidekicks(&player2 , 4);
    //             PlaceStartingSidekicks(&player1 , 24);
    //             break;

    //         case CharacterType :: Dracula:
    //             player1.set_age(p1.first);
    //             player2.set_age(p2.first);
    //             player2.assign_Characters(CharacterType :: Dracula);
    //             player1.assign_Characters(CharacterType :: SherlockHolmes);
    //             board.set_Hero(player2.get_hero() , 4);
    //             board.set_Hero(player1.get_hero() , 24);
    //             PlaceStartingSidekicks(&player2 , 4);
    //             PlaceStartingSidekicks(&player1 , 24);
    //             break;
    //         default:
    //             break;
    //     }
    // }
}

void Game::inital_hand_cards() {
    auto& cards1 = player1.get_hero()->get_deck_cards();
    auto& cards2 = player2.get_hero()->get_deck_cards();

    for (int i = 0; i < 5; i++) {

        if (!cards1.empty()) {
            int index = Rand(cards1.size());
            player1.add_card(std::move(cards1[index]));
            cards1.erase(cards1.begin() + index);
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

void Game :: RemoveDefeatedSidekicks(){
    auto & spaces = board.get_spaces_mut();
    for(auto & sp : spaces){
        Sidekick * s = sp.get_comrade();
        if(s && !s->get_islive())
            board.reset_space(sp.get_id());
    }
}

void Game :: DrawCard(Player * player , int x){
    for(int i = 0 ; i < x ; i++){ 
        if(((player->get_hero())->get_deck_cards()).empty()){

            for(auto & it  : player->get_hero()->get_sidekick()){
                it->Damage(2);
            }
            player->get_hero()->Damage(2);
            RemoveDefeatedSidekicks();
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
    bloodHarvestUsedThisTurn = false;
}

void Game :: PlaceStartingSidekicks(Player * p , int heroSpace){
    Heroes * hero = p->get_hero();
    auto sidekicks = hero->get_sidekick();

    if(hero->get_name() == CharacterType :: Dracula){
        vector<int> spots = (heroSpace == 24) ? vector<int>{21 , 22 , 23} : vector<int>{1 , 5 , 8};
        for(size_t i = 0 ; i < sidekicks.size() && i < spots.size() ; ++i)
            board.set_Comrade(sidekicks[i] , spots[i]);
    }
    else if(hero->get_name() == CharacterType :: Invman){
        vector<int> spots = (heroSpace == 24) ? vector<int>{21 , 22 , 23} : vector<int>{1 , 5 , 8};
        for(size_t i = 0 ; i < sidekicks.size() && i < spots.size() ; ++i)
            board.set_Token(sidekicks[i] , spots[i]);
    }
    else{
        int spot = (heroSpace == 4) ? 1 : 21;
        if(!sidekicks.empty())
            board.set_Comrade(sidekicks[0] , spot);
    }
}

Player* Game :: get_owner(CharacterType chtype){
    if(player1.get_hero()->get_name() == chtype)
        return &player1;
    if(player2.get_hero()->get_name() == chtype)
        return &player2;

    for(auto * sk : player1.get_hero()->get_sidekick())
        if(sk->get_name() == chtype)
            return &player1;

    for(auto * sk : player2.get_hero()->get_sidekick())
        if(sk->get_name() == chtype)
            return &player2;

    return nullptr;
}

Player* Game :: get_opponent(Player * p){
    if(p == &player1)
        return &player2;
    return &player1;
}

Usertype Game :: UsertypeOf(CharacterType chtype) const{
    switch(chtype){
        case CharacterType :: Dracula: return Usertype :: DRACULA;
        case CharacterType :: SherlockHolmes: return Usertype :: HOLMES;
        case CharacterType :: Sister: return Usertype :: SISTER;
        case CharacterType :: Dr_Watson: return Usertype :: DR_WATSON;
        case CharacterType :: Invman: return Usertype :: INVMAN;
        default: return Usertype :: ANY;
    }
}

void Game :: Teleport(int a , int b){
    board.Teleport(a , b);
}

bool Game :: ResolveActingFighter(Player * p , Usertype ut , Heroes *& outHero , Sidekick *& outSidekick , std :: string & err){
    outHero = nullptr;
    outSidekick = nullptr;
    Heroes * hero = p->get_hero();

    switch(ut){
        case Usertype :: ANY:
            if(hero->get_HP() > 0){
                outHero = hero;
                return true;
            }
            for(auto * sk : hero->get_sidekick()){
                if(sk->get_islive()){
                    outSidekick = sk;
                    return true;
                }
            }
            err = "No surviving fighter is available to play this card.";
            return false;

        case Usertype :: DRACULA:
            if(hero->get_name() != CharacterType :: Dracula){
                err = "This card can only be played by Dracula.";
                return false;
            }
            if(hero->get_HP() <= 0){
                err = "Dracula has been defeated and his cards can no longer be played.";
                return false;
            }
            outHero = hero;
            return true;

        case Usertype :: HOLMES:
            if(hero->get_name() != CharacterType :: SherlockHolmes){
                err = "This card can only be played by Sherlock Holmes.";
                return false;
            }
            if(hero->get_HP() <= 0){
                err = "Sherlock Holmes has been defeated and his cards can no longer be played.";
                return false;
            }
            outHero = hero;
            return true;

        case Usertype :: INVMAN:
            if(hero->get_name() != CharacterType :: Invman){
                err = "This card can only be played by the Invisible Man.";
                return false;
            }
            if(hero->get_HP() <= 0){
                err = "The Invisible Man has been defeated and his cards can no longer be played.";
                return false;
            }
            outHero = hero;
            return true;

        case Usertype :: DR_WATSON:
        case Usertype :: SISTER:{
            CharacterType want = (ut == Usertype :: DR_WATSON) ? CharacterType :: Dr_Watson : CharacterType :: Sister;
            for(auto * sk : hero->get_sidekick()){
                if(sk->get_name() == want && sk->get_islive()){
                    outSidekick = sk;
                    return true;
                }
            }
            err = "No surviving sidekick of that type is available to play this card.";
            return false;
        }
    }
    err = "Unknown card ownership.";
    return false;
}

bool Game :: Maneuver(Player * p , std :: string & err){
    if(p->get_aciton() <= 0){
        err = "No actions remaining this turn.";
        return false;
    }
    DrawCard(p , 1);
    DecreaseAction(p);
    return true;
}

bool Game :: MoveFighter(Player * p , int fromSpace , int toSpace , std :: string & err){
    if(!board.valid_space(fromSpace) || !board.valid_space(toSpace)){
        err = "Invalid space.";
        return false;
    }

    auto & spaces = board.get_spaces();
    Heroes * h = spaces[fromSpace].get_Hero();
    Sidekick * s = spaces[fromSpace].get_comrade();

    CharacterType fighterType;
    int moveLimit;

    if(h){
        if(get_owner(h->get_name()) != p){
            err = "That fighter does not belong to you.";
            return false;
        }
        fighterType = h->get_name();
        moveLimit = h->get_Movement();
    }
    else if(s){
        if(!s->get_islive()){
            err = "That fighter has been defeated.";
            return false;
        }
        if(get_owner(s->get_name()) != p){
            err = "That fighter does not belong to you.";
            return false;
        }
        fighterType = s->get_name();
        moveLimit = s->get_Movement();
    }
    else{
        err = "There is no fighter at that space.";
        return false;
    }

    try{
        Move_characters(fromSpace , toSpace , fighterType , true , moveLimit);
    }
    catch(const No_Way &){
        err = "No valid path within that fighter's movement range.";
        return false;
    }
    return true;
}

bool Game :: PlayScheme(Player * p , int handIndex , int current_space , int target_space , int guessedValue , bool guessAttack , std :: string & err , std :: vector<std :: string> & log){
    if(p->get_aciton() <= 0){
        err = "No actions remaining this turn.";
        return false;
    }

    auto & hand = p->get_hand_cards();
    if(handIndex < 0 || handIndex >= static_cast<int>(hand.size())){
        err = "Invalid hand index.";
        return false;
    }

    Card & c = hand[handIndex];
    if(c.get_CardType() != CardType :: EVENT){
        err = "That is not a Scheme card.";
        return false;
    }

    Heroes * actingHero = nullptr;
    Sidekick * actingSidekick = nullptr;
    if(!ResolveActingFighter(p , c.get_usertype() , actingHero , actingSidekick , err))
        return false;

    Player * opponent = get_opponent(p);
    if(c.get_CardName() == CardName :: Eliminate_The_Impossible){
        int idx = guessedValue - 1;
        if(idx < 0 || idx >= static_cast<int>(opponent->get_hand_cards().size())){
            err = "Invalid opponent card index. Usage: scheme <index> <current> <target> <opponent_card_index>";
            return false;
        }
    }

    Card played = p->take_hand_card(handIndex);

    Heroes * moverHero = nullptr;
    Sidekick * moverSidekick = nullptr;
    if(board.valid_space(current_space)){
        auto & spaces = board.get_spaces();
        moverHero = spaces[current_space].get_Hero();
        moverSidekick = spaces[current_space].get_comrade();
    }
    Heroes * targetSpaceHero = nullptr;
    Sidekick * targetSpaceSidekick = nullptr;
    if(board.valid_space(target_space)){
        auto & spaces = board.get_spaces();
        targetSpaceHero = spaces[target_space].get_Hero();
        targetSpaceSidekick = spaces[target_space].get_comrade();
    }

    Context ctx;
    ctx.game = this;
    ctx.ownplayer = p;
    ctx.targetplayer = opponent;
    ctx.ownhero = p->get_hero();
    ctx.ownsidekick = actingSidekick;
    
    ctx.targethero = targetSpaceHero;
    ctx.targetsidekick = targetSpaceSidekick;
    
    ctx.mover_hero = moverHero;
    ctx.mover_sidekick = moverSidekick;
    ctx.effectCard = &played;
    ctx.attackCard = nullptr;
    ctx.defenseCard = nullptr;
    ctx.current_space = current_space;
    ctx.target_space = target_space;
    ctx.chtype = actingSidekick ? actingSidekick->get_name() : ctx.ownhero->get_name();
    ctx.guessedValue = guessedValue;
    ctx.guessAttack = guessAttack;

    if(played.get_CardName() == CardName :: Eliminate_The_Impossible){
        auto & oppHand = ctx.targetplayer->get_hand_cards();
        int idx = guessedValue - 1;
        ctx.remove.push_back(oppHand[idx].get_CardName());
    }

    for(auto & eff : played.get_effects()){
        if(played.get_ApplyEffects())
            eff->execute(ctx);
    }

    log = ctx.log;
    p->discard_card(std :: move(played));
    DecreaseAction(p);
    RemoveDefeatedSidekicks();
    return true;
}

bool Game :: DeclareAttack(Player * attacker , int attackerSpace , int targetSpace , std :: string & err){
    if(combatStage != CombatStage :: None){
        err = "A combat is already in progress.";
        return false;
    }
    if(attacker->get_aciton() <= 0){
        err = "No actions remaining this turn.";
        return false;
    }
    if(!board.valid_space(attackerSpace) || !board.valid_space(targetSpace)){
        err = "Invalid space.";
        return false;
    }

    auto & spaces = board.get_spaces();
    Heroes * aH = spaces[attackerSpace].get_Hero();
    Sidekick * aS = spaces[attackerSpace].get_comrade();
    if(!aH && !aS){
        err = "No fighter at the attacker's space.";
        return false;
    }

    Player * owner = aH ? get_owner(aH->get_name()) : get_owner(aS->get_name());
    if(owner != attacker){
        err = "That fighter does not belong to you.";
        return false;
    }
    if(aS && !aS->get_islive()){
        err = "That fighter has been defeated.";
        return false;
    }

    Heroes * dH = spaces[targetSpace].get_Hero();
    Sidekick * dS = spaces[targetSpace].get_comrade();
    if(!dH && !dS){
        err = "No fighter at the target space.";
        return false;
    }

    Player * defOwner = dH ? get_owner(dH->get_name()) : get_owner(dS->get_name());
    if(defOwner == attacker){
        err = "You cannot attack your own fighter.";
        return false;
    }
    if(dS && !dS->get_islive()){
        err = "The target has already been defeated.";
        return false;
    }

    Attacktype atype = aH ? aH->get_Attacktype() : aS->get_Attacktype();
    bool adjacent = board.AdjacentSpaces(attackerSpace , targetSpace);
    bool sameZone = board.SameZone(attackerSpace , targetSpace);

    if(atype == Attacktype :: MELEE){
        if(!adjacent){
            err = "Melee fighters may only attack adjacent enemies.";
            return false;
        }
    }
    else{
        if(!adjacent && !sameZone){
            err = "Ranged fighters may attack adjacent enemies or any enemy in the same Zone.";
            return false;
        }
    }

    CharacterType fighterType = aH ? aH->get_name() : aS->get_name();
    Usertype needed = UsertypeOf(fighterType);
    bool hasCard = false;
    for(auto & c : attacker->get_hand_cards()){
        if((c.get_CardType() == CardType :: ATTACK || c.get_CardType() == CardType :: BOTH) &&
           (c.get_usertype() == Usertype :: ANY || c.get_usertype() == needed)){
            hasCard = true;
            break;
        }
    }
    if(!hasCard){
        err = "No legal Attack or Versatile card is available for that fighter.";
        return false;
    }

    combatAttackerPlayer = attacker;
    combatDefenderPlayer = defOwner;
    combatAttackerHero = aH;
    combatAttackerSidekick = aS;
    combatDefenderHero = dH;
    combatDefenderSidekick = dS;
    combatAttackerSpace = attackerSpace;
    combatDefenderSpace = targetSpace;
    combatHasDefense = false;
    combatStage = CombatStage :: AwaitAttackCard;
    return true;
}

bool Game :: PlayAttackCard(int handIndex , std :: string & err){
    if(combatStage != CombatStage :: AwaitAttackCard){
        err = "Not currently awaiting an attack card.";
        return false;
    }
    auto & hand = combatAttackerPlayer->get_hand_cards();
    if(handIndex < 0 || handIndex >= static_cast<int>(hand.size())){
        err = "Invalid hand index.";
        return false;
    }
    Card & c = hand[handIndex];
    if(c.get_CardType() != CardType :: ATTACK && c.get_CardType() != CardType :: BOTH){
        err = "That is not a legal Attack/Versatile card.";
        return false;
    }
    CharacterType fighterType = combatAttackerHero ? combatAttackerHero->get_name() : combatAttackerSidekick->get_name();
    Usertype needed = UsertypeOf(fighterType);
    if(c.get_usertype() != Usertype :: ANY && c.get_usertype() != needed){
        err = "That fighter cannot play this card.";
        return false;
    }

    combatAttackCard = combatAttackerPlayer->take_hand_card(handIndex);
    combatStage = CombatStage :: AwaitDefenseCard;
    return true;
}

bool Game :: PlayDefenseCard(int handIndex , std :: string & err){
    if(combatStage != CombatStage :: AwaitDefenseCard){
        err = "Not currently awaiting a defense card.";
        return false;
    }
    auto & hand = combatDefenderPlayer->get_hand_cards();
    if(handIndex < 0 || handIndex >= static_cast<int>(hand.size())){
        err = "Invalid hand index.";
        return false;
    }
    Card & c = hand[handIndex];
    if(c.get_CardType() != CardType :: DEFENSE && c.get_CardType() != CardType :: BOTH){
        err = "That is not a legal Defense/Versatile card.";
        return false;
    }
    CharacterType fighterType = combatDefenderHero ? combatDefenderHero->get_name() : combatDefenderSidekick->get_name();
    Usertype needed = UsertypeOf(fighterType);
    if(c.get_usertype() != Usertype :: ANY && c.get_usertype() != needed){
        err = "That fighter cannot play this card.";
        return false;
    }

    combatDefenseCard = combatDefenderPlayer->take_hand_card(handIndex);
    combatHasDefense = true;
    combatStage = CombatStage :: Ready;
    return true;
}

void Game :: SkipDefense(){
    if(combatStage == CombatStage :: AwaitDefenseCard){
        combatHasDefense = false;
        combatStage = CombatStage :: Ready;
    }
}

CombatStage Game :: get_CombatStage() const{
    return combatStage;
}

std :: vector<std :: string> Game :: ResolveCombat(int moveDestination, std :: vector<int> boostDiscardIndices){
    vector<string> log;
    if(combatStage != CombatStage :: Ready){
        log.push_back("Combat is not ready to resolve.");
        return log;
    }

    Context ctx;
    ctx.game = this;
    ctx.attackCard = &combatAttackCard;
    ctx.defenseCard = combatHasDefense ? &combatDefenseCard : nullptr;
    ctx.current_space = combatAttackerSpace;
    ctx.target_space = combatDefenderSpace;
    ctx.move_override_target = moveDestination;
    {
        auto & atkHand = combatAttackerPlayer->get_hand_cards();
        for(int idx : boostDiscardIndices){
            if(idx >= 0 && idx < static_cast<int>(atkHand.size()))
                ctx.remove.push_back(atkHand[idx].get_CardName());
        }
    }

    auto setPerspectiveAttacker = [&](){
        ctx.ownplayer = combatAttackerPlayer;
        ctx.targetplayer = combatDefenderPlayer;
        ctx.ownhero = combatAttackerPlayer->get_hero();
        ctx.ownsidekick = combatAttackerSidekick;
        ctx.targethero = combatDefenderPlayer->get_hero();
        ctx.targetsidekick = combatDefenderSidekick;
        ctx.chtype = combatAttackerHero ? combatAttackerHero->get_name() : combatAttackerSidekick->get_name();
    };
    auto setPerspectiveDefender = [&](){
        ctx.ownplayer = combatDefenderPlayer;
        ctx.targetplayer = combatAttackerPlayer;
        ctx.ownhero = combatDefenderPlayer->get_hero();
        ctx.ownsidekick = combatDefenderSidekick;
        ctx.targethero = combatAttackerPlayer->get_hero();
        ctx.targetsidekick = combatAttackerSidekick;
        ctx.chtype = combatDefenderHero ? combatDefenderHero->get_name() : combatDefenderSidekick->get_name();
    };

    auto resolveWindow = [&](CardTiming timing){
        if(combatHasDefense && combatDefenseCard.get_CardTiming() == timing && combatDefenseCard.get_ApplyEffects()){
            setPerspectiveDefender();
            ctx.effectCard = &combatDefenseCard;
            for(auto & eff : combatDefenseCard.get_effects())
                eff->execute(ctx);
        }
        if(combatAttackCard.get_CardTiming() == timing && combatAttackCard.get_ApplyEffects()){
            setPerspectiveAttacker();
            ctx.effectCard = &combatAttackCard;
            for(auto & eff : combatAttackCard.get_effects())
                eff->execute(ctx);
        }
    };

    resolveWindow(CardTiming :: Before);   
    resolveWindow(CardTiming :: During);   

    int atk = combatAttackCard.get_Attack();
    if(ctx.ignoreAttack)
        atk = 0;
    int def = combatHasDefense ? combatDefenseCard.get_Defense() : 0;
    int dmg = atk - def;

    bool attackerWon = false;
    if(dmg > 0){
        if(combatDefenderHero)
            combatDefenderHero->Damage(dmg);
        else if(combatDefenderSidekick)
            combatDefenderSidekick->Damage(dmg);
        attackerWon = true;
        log.push_back("Direct combat damage: " + std :: to_string(dmg));
    }
    else{
        log.push_back("No direct combat damage was dealt.");
    }
    log.push_back(attackerWon ? "The attacker wins the combat." : "The defender wins the combat.");

    if(combatHasDefense && combatDefenseCard.get_CardTiming() == CardTiming :: After && combatDefenseCard.get_ApplyEffects()){
        setPerspectiveDefender();
        ctx.effectCard = &combatDefenseCard;
        ctx.result = attackerWon ? CombatResult :: Lose : CombatResult :: Win;
        for(auto & eff : combatDefenseCard.get_effects())
            eff->execute(ctx);
    }
    if(combatAttackCard.get_CardTiming() == CardTiming :: After && combatAttackCard.get_ApplyEffects()){
        setPerspectiveAttacker();
        ctx.effectCard = &combatAttackCard;
        ctx.result = attackerWon ? CombatResult :: Win : CombatResult :: Lose;
        for(auto & eff : combatAttackCard.get_effects())
            eff->execute(ctx);
    }

    for(auto & s : ctx.log)
        log.push_back(s);

    combatAttackerPlayer->discard_card(std :: move(combatAttackCard));
    if(combatHasDefense)
        combatDefenderPlayer->discard_card(std :: move(combatDefenseCard));

    DecreaseAction(combatAttackerPlayer);

    combatStage = CombatStage :: None;
    combatAttackerPlayer = nullptr;
    combatDefenderPlayer = nullptr;
    combatAttackerHero = nullptr;
    combatDefenderHero = nullptr;
    combatAttackerSidekick = nullptr;
    combatDefenderSidekick = nullptr;
    combatHasDefense = false;

    RemoveDefeatedSidekicks();

    return log;
}

bool Game :: BloodHarvest(Player * p , int targetSpace , std :: string & err){
    Heroes * dracula = p->get_hero();
    if(dracula->get_name() != CharacterType :: Dracula){
        err = "Only Dracula has the Blood Harvest ability.";
        return false;
    }
    if(bloodHarvestUsedThisTurn){
        err = "Blood Harvest has already been used this turn.";
        return false;
    }
    if(!board.valid_space(targetSpace)){
        err = "Invalid space.";
        return false;
    }

    int dSpace = board.find_space_of_hero(dracula);
    if(dSpace < 0){
        err = "Dracula is not on the board.";
        return false;
    }
    if(!board.AdjacentSpaces(dSpace , targetSpace)){
        err = "The target must be adjacent to Dracula.";
        return false;
    }

    auto & spaces = board.get_spaces();
    Heroes * h = spaces[targetSpace].get_Hero();
    Sidekick * s = spaces[targetSpace].get_comrade();
    if(!h && !s){
        err = "There is no fighter at that space.";
        return false;
    }

    if(h)
        h->Damage(1);
    else
        s->Damage(1);

    DrawCard(p , 1);
    bloodHarvestUsedThisTurn = true;
    RemoveDefeatedSidekicks();
    return true;
}

bool Game :: CanEndTurn(Player * p) const{
    return p->get_aciton() <= 0 && p->get_hand_cards().size() <= 7;
}

bool Game :: DiscardExcess(Player * p , int handIndex , std :: string & err){
    auto & hand = p->get_hand_cards();
    if(hand.size() <= 7){
        err = "Hand size is already 7 or fewer.";
        return false;
    }
    if(handIndex < 0 || handIndex >= static_cast<int>(hand.size())){
        err = "Invalid hand index.";
        return false;
    }
    p->discard_card(p->take_hand_card(handIndex));
    return true;
}

void Game :: EndTurn(){
    ChangeTurn();
}