#include "Effect.h"
#include "game.h"

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
            ctx.targethero->Heal(1);
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
            ctx.ownplayer->remove_card(it);
    }
    else{
        for (auto & it  : ctx.remove){
            int attack = ctx.attackCard->get_Attack() ;
            ctx.attackCard->set_Attack(attack + 1);
            ctx.ownplayer->remove_card(it);
        }
    }
}
//////////////////////////
Boost_attack :: Boost_attack (CharacterType ch , bool mode) : chtype(ch) , sistermode(mode){}

void Boost_attack :: execute(Context & ctx){
    if(sistermode){
        int i = 0;
        vector<Space> spaces = ctx.game->get_Board()->get_spaces();
        for(auto it : spaces){
            if(it.get_zone() == spaces[ctx.current_space].get_zone() &&
                it.get_comrade() && 
                it.get_comrade()->get_name() == chtype){
                    i++;
                }
        }
        int attack = ctx.attackCard->get_Attack();
        ctx.attackCard->set_Attack(attack + i);
    }
    else{
        int boost = ctx.game->Rand_Discard(ctx.targetplayer);
        int attack = ctx.attackCard->get_Attack();
        ctx.attackCard->set_Attack(attack + boost);
    }
}
/////////////////////////
void Boost_deffence :: execute(Context & ctx){
    int boost = ctx.attackCard->get_Attack();
    int last_attack = ctx.attackCard->get_Defense();
    ctx.defenseCard->set_Defence(last_attack + boost);
}
/////////////////////////
Move :: Move(int x) : cost(x){}

void Move :: execute(Context & ctx){
    ctx.game->Move_characters(ctx.current_space , ctx.target_space , ctx.chtype , ctx.Allow_hidden_way , cost);
}
////////////////////////
ReplaceEffect :: ReplaceEffect(int x) : mode(x) {}

void ReplaceEffect :: execute(Context & ctx){
    if(mode == 1)
        ctx.game->Replace(ctx.current_space  , ctx.target_space);

    else if(mode == 2){
        ctx.game->Replace(ctx.current_space , ctx.target_space);
        ctx.game->IncreaseAction(ctx.ownplayer);
    }

    else if(mode == 3){
        if(ctx.result == CombatResult :: Win)
            ctx.game->Replace(ctx.current_space , ctx.target_space);
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
        Space * situation = ctx.game->get_Board()->search_hero(ctx.ownhero);
        for(auto & it : situation->get_neighbor()){
            if(ctx.game->get_Board()->get_spaces()[it].get_Hero()){
                ctx.game->get_Board()->get_spaces()[it].get_Hero()->Damage(damage);
                ctx.ownhero->Heal(1);
            }

            else if(ctx.game->get_Board()->get_spaces()[it].get_comrade()){
                ctx.game->get_Board()->get_spaces()[it].get_comrade()->Damage(damage);
                ctx.ownhero->Heal(1);
            }
        }
    }
    else if(chtype == CharacterType :: SherlockHolmes){
        CharacterType chtype = ctx.ownhero->get_name();
        CharacterType chtype2;
        if(ctx.targethero){
            chtype2 = ctx.targethero->get_name();
            if(ctx.game->Adjacency(chtype , chtype2))
                ctx.targethero->Damage(damage);
        }
        else if(ctx.targetsidekick){
            chtype2 = ctx.targetsidekick->get_name();
            if(ctx.game->Adjacency(chtype , chtype2))
                ctx.targetsidekick->Damage(damage);
        }   
    } 
    else if(chtype == CharacterType :: Sister){
        int i = 0;
        Space * situation = ctx.game->get_Board()->search_comrades(ctx.ownsidekick);
        for(auto & it : situation->get_neighbor()){

            if(ctx.game->get_Board()->get_spaces()[it].get_comrade() && ctx.game->get_Board()->get_spaces()[it].get_comrade()->get_name() == CharacterType :: Sister)
                i++;

        } 
        if(ctx.targethero)
            ctx.targethero->Damage(i);
        else if(ctx.targetsidekick)
            ctx.targetsidekick->Damage(i);
    }
    
}
/////////////////////
void Disable_effects :: execute(Context & ctx){
    for(auto & it : ctx.ownplayer->get_hand_cards())
        it.set_ApplyEffects(false);
}
////////////////////
void See_the_deck :: execute(Context & ctx){
    if(ctx.result == CombatResult :: Win)
        ctx.targetplayer->get_hand_cards();

}

vector<unique_ptr<Effect>> Make_Effect(vector<Effect *> effects){
    vector<unique_ptr<Effect>> result;

    for (auto* effect : effects)
        result.emplace_back(effect);

    return result;
}
