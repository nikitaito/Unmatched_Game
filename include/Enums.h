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

    Coded_Notes,
    ConFound,
    Covert_PreParation,
    Deaming_of_Revenge,
    Emerge_from_Mist,
    Impossible_to_See,
    Into_Thin_Air,
    Lurking,
    Reign_of_Terror,
    Rolling_Fog,
    Slip_Away,
    Step_Lightly,
    Vanish,
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
    INTEL,
    STEALTH
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
    INVMAN,
    ANY
 };

enum class CharacterType{
    SherlockHolmes,
    Dracula,
    Dr_Watson,
    Sister,
    Invman,
    InvmanToken
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

enum class Zone{
    LightBlue,
    DarkBlue,
    Brown,
    Yellow,
    Green,
    Purple,
    Gray
};

enum class Page {
    Menu,
    Help,
    Age,
    Exit,
    Choose,
    Game,
    End,
    Load
};

enum class Action_State{
    None,
    Maneuver,
    Attack,
    Scheme,
    Move,
    
};

enum class CombatStage{
    None,
    AwaitAttackCard,
    AwaitDefenseCard,
    Ready
};
