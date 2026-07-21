#pragma once


enum class CardName
{
    Feedingfrenzy,
    Mistform,
    Ambush,
    Baptism_of_blood,
    Beastform,
    Dash,
    Exploit,
    Look_into_my_eyes,
    Prey_upon,
    Ravening_Seduction,
    Thirst_for_sustenance,

    Administer_Aid, 
    Confirm_Suspicion,
    Counterpunch,
    Deduce_Strategy,
    Education_Never_Ends,
    Elementary,
    Eliminate_The_Impossible,
    Feint,
    Fixed_Point_in_a_Changing_Age,
    Master_of_Disguise,
    The_Game_Is_Afoot,
    Service_Revolver,
    Study_Methods,

};

enum class CardTiming
{
    During,
    Before,
    After,
    Immediate,
};

enum class Style
{
    ARRGD,
    INTEL
};

enum class Attacktype{
    MELEE,
    RANGED
};

enum class Usertype{
    DR_WATSON,
    HOLMES,
    SISTER,
    DRACULA,
    ANY
 };

enum class CharacterType{
    SherlockHolmes,
    Dracula,
    Dr_Watson,
    Sister
};


enum class CombatResult
{
    Win,
    Lose,
    Tie
};
enum class CardType{
    ATTACK,
    DEFENSE,
    EVENT,
    BOTH
};

enum Zone{
    LIGHT_BLUE,
    DARK_BLUE,
    BROWN,
    YELLOW,
    GREEN,
    PURPULE,
    GRAY
};

enum class Page {
    Menu,
    Help,
    Age,
    Game,
    End
};

enum class Action_State{
    None,
    Maneuver,
    Attack,
    Schame,
    Move,
    
};
