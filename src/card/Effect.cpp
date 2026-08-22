#include "card/Effect.h"
#include "game/game.h"
#include <algorithm>

using namespace std;

HealEffect :: HealEffect (int amount) : amount(amount){}

void HealEffect :: execute(Context & ctx){
    if (ctx.ownhero == nullptr)
            return;

        ctx.ownhero->Heal(amount);
}
//////////////////////////
HealIfAdjency :: HealIfAdjency(CharacterType chtypes) : chtype(chtypes) {}

void HealIfAdjency :: execute(Context & ctx){
    if(ctx.ownsidekick && ctx.ownsidekick->get_name() == CharacterType ::Dr_Watson){
        if(ctx.game->Adjacency(CharacterType :: Dr_Watson , chtype)){
            ctx.ownsidekick->Heal(1);
            if(ctx.ownhero)
                ctx.ownhero->Heal(1);
        }
    }
}
//////////////////////////
DrawCardEffect :: DrawCardEffect(int count) : count(count) {}

void DrawCardEffect :: execute(Context & ctx){
    if(ctx.ownplayer == nullptr)
        return;
    for(int x = count ; x > 0 ; x--)
        ctx.game->DrawCard(ctx.ownplayer , 1);
}
//////////////////////////
DrawDependingOnResult :: DrawDependingOnResult(int winDraw, int loseDraw) : winDraw(winDraw) , loseDraw(loseDraw) {}

void DrawDependingOnResult :: execute(Context & ctx) {
    switch (ctx.result)
    {
        case CombatResult::Win:
            ctx.game->DrawCard(ctx.targetplayer , winDraw);
            break;

        case CombatResult::Lose:
            ctx.game->DrawCard(ctx.ownplayer , loseDraw);
            break;

        default:
            break;
    }
}
//////////////////////////
Discard :: Discard(bool mode) : justremove(mode){}

void Discard :: execute(Context & ctx){
    if(justremove){
        for (auto & it  : ctx.remove)
            ctx.targetplayer->remove_card(it);
    }
    else{
        for (auto & it  : ctx.remove){
            ctx.attackCard->set_Attack(ctx.attackCard->get_Attack() + 1);
            ctx.ownplayer->remove_card(it);
        }
    }
}
//////////////////////////
Boost_attack :: Boost_attack (CharacterType ch , bool mode) : chtype(ch) , sistermode(mode){}

void Boost_attack :: execute(Context & ctx){
    if(sistermode){
        int i = 0;
        const auto & spaces = ctx.game->get_Board()->get_spaces();
        if(ctx.target_space >= 0 && ctx.target_space < static_cast<int>(spaces.size())){
            const auto & target_zones = spaces[ctx.target_space].get_zone();
            for(const auto & sp : spaces){
                if(sp.get_comrade() && sp.get_comrade()->get_name() == chtype && sp.get_comrade()->get_islive()){
                    const auto & sister_zones = sp.get_zone();
                    bool shared = false;
                    for(auto z : sister_zones){
                        if(std::find(target_zones.begin(), target_zones.end(), z) != target_zones.end()){
                            shared = true;
                            break;
                        }
                    }
                    if(shared)
                        i++;
                }
            }
        }
        ctx.attackCard->set_Attack(i);
    }
    else{
        int boost = ctx.game->Rand_Discard(ctx.targetplayer);
        ctx.attackCard->set_Attack(boost);
    }
}
/////////////////////////
void Boost_deffence :: execute(Context & ctx){
    if(!ctx.attackCard || !ctx.defenseCard)
        return;

    int boost = ctx.attackCard->get_Boost();
    ctx.defenseCard->set_Defence(boost);
}
/////////////////////////
Move :: Move(int x) : cost(x){}

void Move :: execute(Context & ctx){
    int destination = (ctx.move_override_target >= 0) ? ctx.move_override_target : ctx.target_space;
    try{
        ctx.game->Move_characters(ctx.current_space , destination , ctx.chtype , ctx.Allow_hidden_way , cost);
    }
    catch(const std :: exception &){
        ctx.log.push_back("Move effect had no legal destination and was skipped.");
    }
}
////////////////////////
ReplaceEffect :: ReplaceEffect(int x) : mode(x) {}

void ReplaceEffect :: execute(Context & ctx){
    if(mode == 1){
        ctx.game->Replace(ctx.current_space  , ctx.target_space);
    }
    else if(mode == 2){
        ctx.game->Teleport(ctx.current_space , ctx.target_space);
        ctx.game->IncreaseAction(ctx.ownplayer);
    }
    else if(mode == 3){
        if(ctx.result == CombatResult :: Win)
            ctx.game->Teleport(ctx.current_space , ctx.target_space);
    }
    else if(mode == 4){
        ctx.game->Teleport(ctx.current_space , ctx.target_space);
    }
}
/////////////////////// 
DamageEffect :: DamageEffect (int x) : amount(x) {}

void DamageEffect :: execute(Context & ctx){
    if(ctx.targethero)
        ctx.targethero->Damage(amount);
    else if(ctx.targetsidekick)
        ctx.targetsidekick->Damage(amount);
}
//////////////////////
DamageIfAdjacent :: DamageIfAdjacent(int d , CharacterType ch) : damage(d) , chtype(ch){}

void DamageIfAdjacent :: execute(Context & ctx){
    if (!ctx.ownhero)
        return;

    if (!ctx.game)
        return;

    if(chtype == CharacterType :: Dracula){
        int self_space = ctx.game->get_Board()->find_space_of_hero(ctx.ownhero);
        if(self_space < 0)
            return;

        const auto & spaces = ctx.game->get_Board()->get_spaces();
        for(int nb : spaces[self_space].get_neighbor()){
            Heroes * h = spaces[nb].get_Hero();
            Sidekick * s = spaces[nb].get_comrade();

            if(h && ctx.game->get_owner(h->get_name()) != ctx.ownplayer){
                h->Damage(damage);
                ctx.ownhero->Heal(damage);
            }
            else if(s && ctx.game->get_owner(s->get_name()) != ctx.ownplayer){
                s->Damage(damage);
                ctx.ownhero->Heal(damage);
            }
        }
    }
    else if(chtype == CharacterType :: SherlockHolmes){
        CharacterType selfType = ctx.ownhero->get_name();
        if(ctx.targethero){
            if(ctx.game->Adjacency(selfType , ctx.targethero->get_name()))
                ctx.targethero->Damage(damage);
        }
        else if(ctx.targetsidekick){
            if(ctx.game->Adjacency(selfType , ctx.targetsidekick->get_name()))
                ctx.targetsidekick->Damage(damage);
        }
    }
    else if(chtype == CharacterType :: Sister){
        int i = 0;
        if(ctx.target_space >= 0){
            const auto & spaces = ctx.game->get_Board()->get_spaces();
            for(int nb : spaces[ctx.target_space].get_neighbor()){
                if(spaces[nb].get_comrade() && spaces[nb].get_comrade()->get_name() == CharacterType :: Sister)
                    i++;
            }
        }
        if(ctx.mover_hero)
            ctx.mover_hero->Damage(i);
        else if(ctx.mover_sidekick)
            ctx.mover_sidekick->Damage(i);
    }
    else if(chtype == CharacterType :: Invman){
        // Reign of Terror: if the Invisible Man is on a fog token space, damage every enemy fighter.
        if(!ctx.targetplayer)
            return;

        Board * board = ctx.game->get_Board();
        int self_space = board->find_space_of_hero(ctx.ownhero);
        if(self_space < 0)
            return;

        const auto & spaces = board->get_spaces();
        if(spaces[self_space].get_token() == nullptr)
            return;

        Heroes * enemyHero = ctx.targetplayer->get_hero();
        if(!enemyHero)
            return;

        if(enemyHero->get_HP() > 0)
            enemyHero->Damage(damage);

        for(Sidekick * sk : enemyHero->get_sidekick()){
            if(sk && sk->get_islive())
                sk->Damage(damage);
        }
    }

}
/////////////////////
void Disable_effects :: execute(Context & ctx){
    if(ctx.effectCard == ctx.attackCard && ctx.defenseCard)
        ctx.defenseCard->set_ApplyEffects(false);
    else if(ctx.effectCard == ctx.defenseCard && ctx.attackCard)
        ctx.attackCard->set_ApplyEffects(false);
}
////////////////////
void See_the_deck :: execute(Context & ctx){
    if(ctx.result == CombatResult :: Win && ctx.targetplayer){
        ctx.log.push_back("Opponent's hand revealed.");
    }
}
////////////////////
void ConfirmSuspicionEffect :: execute(Context & ctx){
    if(!ctx.targetplayer)
        return;

    auto & hand = ctx.targetplayer->get_hand_cards();
    CardName foundName{};
    int foundBoost = 0;
    bool found = false;

    for(auto & c : hand){
        int val = ctx.guessAttack ? c.get_Attack() : c.get_Defense();
        if(val == ctx.guessedValue){
            foundName = c.get_CardName();
            foundBoost = c.get_Boost();
            found = true;
            break;
        }
    }

    if(found){
        ctx.targetplayer->remove_card(foundName);
        if(ctx.targethero)
            ctx.targethero->Damage(foundBoost);
        ctx.log.push_back("Matching card discarded.");
    }
    else{
        ctx.log.push_back("No matching card - hand revealed instead.");
    }
}
////////////////////
void ElementaryEffect :: execute(Context & ctx){
    if(!ctx.attackCard)
        return;

    if(ctx.attackCard->get_Attack() == ctx.guessedValue){
        ctx.ignoreAttack = true;
        ctx.attackCard->set_ApplyEffects(false);
        ctx.log.push_back("Prediction correct - attack ignored.");
    }
    else{
        ctx.log.push_back("Prediction incorrect.");
    }
}
////////////////////
void DeduceStrategyEffect :: execute(Context & ctx){
    if(!ctx.effectCard)
        return;

    int boost = ctx.effectCard->get_Boost();

    if(ctx.effectCard == ctx.attackCard && ctx.defenseCard){
        int delta = boost - ctx.defenseCard->get_Defense();
        ctx.defenseCard->set_Defence(delta);
    }
    else if(ctx.effectCard == ctx.defenseCard && ctx.attackCard){
        int delta = boost - ctx.attackCard->get_Attack();
        ctx.attackCard->set_Attack(delta);
    }
}

vector<unique_ptr<Effect>> Make_Effect(vector<Effect *> effects){
    vector<unique_ptr<Effect>> result;

    for (auto* effect : effects)
        result.emplace_back(effect);

    return result;
}
//////////////////////
DamageIfOnFog :: DamageIfOnFog(int d) : damage(d){}

void DamageIfOnFog :: execute(Context & ctx){
    if(!ctx.ownhero || !ctx.game)
        return;

    Board * board = ctx.game->get_Board();
    int selfSpace = board->find_space_of_hero(ctx.ownhero);
    if(selfSpace < 0)
        return;

    const auto & spaces = board->get_spaces();
    if(spaces[selfSpace].get_token() == nullptr)
        return;

    for(const auto & sp : spaces){
        if(sp.get_token() == nullptr)
            continue;

        Heroes * h = sp.get_Hero();
        if(h && ctx.game->get_owner(h->get_name()) == ctx.targetplayer)
            h->Damage(damage);

        Sidekick * s = sp.get_comrade();
        if(s && s->get_islive() && ctx.game->get_owner(s->get_name()) == ctx.targetplayer)
            s->Damage(damage);
    }
}
//////////////////////
void EmergeFromMistEffect :: execute(Context & ctx){
    if(!ctx.ownhero || !ctx.game || !ctx.effectCard)
        return;

    int startSpace = ctx.ownhero->get_StartTurnSpace();
    if(startSpace < 0)
        return;

    const auto & spaces = ctx.game->get_Board()->get_spaces();
    if(startSpace >= static_cast<int>(spaces.size()))
        return;

    if(spaces[startSpace].get_token() != nullptr){
        int delta = 5 - ctx.effectCard->get_Attack();
        ctx.effectCard->set_Attack(delta);
        ctx.log.push_back("Emerging from the Fog: attack value becomes 5.");
    }
}
//////////////////////
SelfMoveEffect :: SelfMoveEffect(int c) : cost(c){}

void SelfMoveEffect :: execute(Context & ctx){
    if(!ctx.ownhero || !ctx.game)
        return;

    if(ctx.self_move_destination < 0)
        return;

    Board * board = ctx.game->get_Board();
    int selfSpace = board->find_space_of_hero(ctx.ownhero);
    if(selfSpace < 0 || selfSpace == ctx.self_move_destination)
        return;

    try{
        ctx.game->Move_characters(selfSpace , ctx.self_move_destination , ctx.ownhero->get_name() , false , cost);
        ctx.log.push_back("The Invisible Man slips to a new space.");
    }
    catch(const std :: exception &){
        ctx.log.push_back("No legal space for the Invisible Man to move to.");
    }
}
//////////////////////
MoveFogTokenEffect :: MoveFogTokenEffect(int c , bool requireEmpty) : cost(c) , requireEmptyDestination(requireEmpty){}

void MoveFogTokenEffect :: execute(Context & ctx){
    if(!ctx.game)
        return;

    if(ctx.fog_token_space < 0 || ctx.fog_token_destination < 0 || ctx.fog_token_space == ctx.fog_token_destination)
        return;

    Board * board = ctx.game->get_Board();
    const auto & spaces = board->get_spaces();
    if(ctx.fog_token_destination >= static_cast<int>(spaces.size()))
        return;

    if(requireEmptyDestination && !spaces[ctx.fog_token_destination].empty()){
        ctx.log.push_back("The destination space is not empty.");
        return;
    }

    try{
        int effectiveCost = (cost < 0) ? board->get_space_count() : cost;
        ctx.game->Move_FogToken(ctx.fog_token_space , ctx.fog_token_destination , effectiveCost);
        ctx.log.push_back("A fog token drifts to a new space.");
    }
    catch(const std :: exception &){
        ctx.log.push_back("The fog token had no legal destination.");
    }
}
//////////////////////
void PlaceSelfOnFogTokenEffect :: execute(Context & ctx){
    if(!ctx.ownhero || !ctx.game)
        return;

    if(ctx.fog_token_destination < 0)
        return;

    Board * board = ctx.game->get_Board();
    int selfSpace = board->find_space_of_hero(ctx.ownhero);
    if(selfSpace < 0 || selfSpace == ctx.fog_token_destination)
        return;

    try{
        ctx.game->Teleport(selfSpace , ctx.fog_token_destination);
        ctx.log.push_back("The Invisible Man appears where the fog token landed.");
    }
    catch(const std :: exception &){
        ctx.log.push_back("Could not place the Invisible Man on the new space.");
    }
}
//////////////////////
void GainActionEffect :: execute(Context & ctx){
    if(!ctx.game || !ctx.ownplayer)
        return;

    ctx.game->IncreaseAction(ctx.ownplayer);
    ctx.log.push_back("Gained 1 action.");
}
//////////////////////
void MoveToFogTokenSpaceEffect :: execute(Context & ctx){
    if(!ctx.ownhero || !ctx.game)
        return;

    if(ctx.self_move_destination < 0)
        return;

    Board * board = ctx.game->get_Board();
    int selfSpace = board->find_space_of_hero(ctx.ownhero);
    if(selfSpace < 0 || selfSpace == ctx.self_move_destination)
        return;

    const auto & spaces = board->get_spaces();
    if(ctx.self_move_destination >= static_cast<int>(spaces.size()))
        return;

    if(spaces[ctx.self_move_destination].get_token() == nullptr){
        ctx.log.push_back("Lurking: the chosen space does not contain a fog token.");
        return;
    }

    try{
        ctx.game->Teleport(selfSpace , ctx.self_move_destination);
        ctx.log.push_back("The Invisible Man slips onto the fog token.");
    }
    catch(const std :: exception &){
        ctx.log.push_back("Could not move the Invisible Man onto the fog token.");
    }
}
//////////////////////
void ImpossibleToSeeEffect :: execute(Context & ctx){
    Card * target = nullptr;
    bool targetIsAttack = false;

    if(ctx.effectCard == ctx.attackCard && ctx.defenseCard){
        target = ctx.defenseCard;
        targetIsAttack = false;
    }
    else if(ctx.effectCard == ctx.defenseCard && ctx.attackCard){
        target = ctx.attackCard;
        targetIsAttack = true;
    }

    if(!target)
        return;

    if(targetIsAttack)
        target->set_Attack(-target->get_Attack());
    else
        target->set_Defence(-target->get_Defense());

    target->LockValue();
    ctx.log.push_back("Impossible to See: opponent's card value is locked at 0.");
}
//////////////////////
void CodedNotesEffect :: execute(Context & ctx){
    if(!ctx.ownhero || !ctx.ownplayer || !ctx.game)
        return;

    auto & hand = ctx.ownplayer->get_hand_cards();
    int beforeDraw = static_cast<int>(hand.size());

    ctx.game->DrawCard(ctx.ownplayer , 3);

    int actuallyDrawn = static_cast<int>(hand.size()) - beforeDraw;
    if(actuallyDrawn <= 0){
        ctx.log.push_back("Coded Notes: no cards left to draw.");
        return;
    }

    if(ctx.codedNotesReturnOrder.size() != 2){
        ctx.log.push_back("Coded Notes: no valid choice supplied, drawn cards stay in hand.");
        return;
    }

    int pos0 = ctx.codedNotesReturnOrder[0];
    int pos1 = ctx.codedNotesReturnOrder[1];

    if(pos0 < 0 || pos1 < 0 || pos0 == pos1 || pos0 >= actuallyDrawn || pos1 >= actuallyDrawn){
        ctx.log.push_back("Coded Notes: invalid choice, drawn cards stay in hand.");
        return;
    }

    int idx0 = beforeDraw + pos0;
    int idx1 = beforeDraw + pos1;

    // Take the higher hand index first so removing it doesn't shift the lower
    // index out from under us; slots[0] must stay the one that goes on top.
    std :: vector<Card> slots(2);
    if(idx0 > idx1){
        slots[0] = ctx.ownplayer->take_hand_card(idx0);
        slots[1] = ctx.ownplayer->take_hand_card(idx1);
    }
    else{
        slots[1] = ctx.ownplayer->take_hand_card(idx1);
        slots[0] = ctx.ownplayer->take_hand_card(idx0);
    }

    ctx.ownhero->add_to_top_of_deck(std :: move(slots));
    ctx.log.push_back("Coded Notes: 2 cards placed on top of the deck.");
}
//////////////////
void ConfoundEffect :: execute(Context & ctx){
    if(!ctx.game)
        return;

    if(!ctx.remove.empty()){
        if(ctx.targetplayer)
            for(auto & cn : ctx.remove)
                ctx.targetplayer->remove_card(cn);
        ctx.log.push_back("Your opponent discards a card.");
        return;
    }

    if(ctx.fog_token_space >= 0 && ctx.fog_token_destination >= 0 && ctx.fog_token_space != ctx.fog_token_destination){
        try{
            ctx.game->Move_FogToken(ctx.fog_token_space , ctx.fog_token_destination , ctx.game->get_Board()->get_space_count());
            ctx.log.push_back("A fog token moves to a new location.");
        }
        catch(const std :: exception &){
            ctx.log.push_back("No legal destination for that fog token.");
        }
    }
}
//////////////////////
