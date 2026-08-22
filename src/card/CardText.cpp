#include "card/CardText.h"

const char * CardDisplayName(CardName name){
    switch(name){
        case CardName::Feedingfrenzy:              return "Feeding Frenzy";
        case CardName::Mistform:                   return "Mistform";
        case CardName::Ambush:                      return "Ambush";
        case CardName::Baptism_of_blood:            return "Baptism of Blood";
        case CardName::Beastform:                    return "Beastform";
        case CardName::Dash:                          return "Dash";
        case CardName::Exploit:                        return "Exploit";
        case CardName::Look_into_my_eyes:               return "Look Into My Eyes";
        case CardName::Prey_upon:                        return "Prey Upon";
        case CardName::Ravening_Seduction:                return "Ravening Seduction";
        case CardName::Thirst_for_sustenance:              return "Thirst for Sustenance";

        case CardName::Administer_Aid:              return "Administer Aid";
        case CardName::Confirm_Suspicion:            return "Confirm Suspicion";
        case CardName::Counterpunch:                   return "Counter Punch";
        case CardName::Deduce_Strategy:                  return "Deduce Strategy";
        case CardName::Education_Never_Ends:              return "Education Never Ends";
        case CardName::Elementary:                          return "Elementary";
        case CardName::Eliminate_The_Impossible:              return "Eliminate the Impossible";
        case CardName::Feint:                                  return "Feint";
        case CardName::Fixed_Point_in_a_Changing_Age:            return "Fixed Point in a Changing Age";
        case CardName::Master_of_Disguise:                        return "Master of Disguise";
        case CardName::The_Game_Is_Afoot:                          return "The Game Is Afoot";
        case CardName::Service_Revolver:                            return "Service Revolver";
        case CardName::Study_Methods:                                return "Study Methods";

        case CardName::Coded_Notes:              return "Coded Notes";
        case CardName::ConFound:                   return "Confound - Extra";
        case CardName::Covert_PreParation:           return "Covert Preparation - Extra";
        case CardName::Deaming_of_Revenge:             return "Dreaming of Revenge";
        case CardName::Emerge_from_Mist:                 return "Emerging from the Fog";
        case CardName::Impossible_to_See:                  return "Invisible";
        case CardName::Into_Thin_Air:                        return "Vanishing into Thin Air";
        case CardName::Lurking:                                return "Ambush";
        case CardName::Reign_of_Terror:                          return "Reign of Terror";
        case CardName::Rolling_Fog:                                return "Rolling Fog";
        case CardName::Slip_Away:                                    return "Glide into the Distance";
        case CardName::Step_Lightly:                                   return "Walk Quietly";
        case CardName::Vanish:                                           return "Vanish - Extra";
    }
    return "Unknown Card";
}

const char * UsertypeLabel(Usertype type){
    switch(type){
        case Usertype::DR_WATSON: return "Dr. Watson";
        case Usertype::HOLMES:    return "Sherlock Holmes";
        case Usertype::SISTER:    return "Sister";
        case Usertype::DRACULA:   return "Dracula";
        case Usertype::INVMAN:    return "Invisible Man";
        case Usertype::ANY:       return "Any";
    }
    return "";
}

const char * CardTypeLabel(CardType type){
    switch(type){
        case CardType::ATTACK:  return "Attack";
        case CardType::DEFENSE: return "Defense";
        case CardType::EVENT:   return "Scheme";
        case CardType::BOTH:    return "Versatile";
    }
    return "";
}

std :: string CardStatLine(CardType type, int attack, int defense, int boost){
    std :: string line;
    switch(type){
        case CardType::ATTACK:
            line = "ATK " + std::to_string(attack);
            break;
        case CardType::DEFENSE:
            line = "DEF " + std::to_string(defense);
            break;
        case CardType::BOTH:
            line = "ATK/DEF " + std::to_string(attack) + "/" + std::to_string(defense);
            break;
        case CardType::EVENT:
            line = "Scheme";
            break;
    }
    line += "  Boost " + std::to_string(boost);
    return line;
}

const char * CharacterDisplayName(CharacterType type){
    switch(type){
        case CharacterType::SherlockHolmes: return "Sherlock Holmes";
        case CharacterType::Dracula:        return "Dracula";
        case CharacterType::Dr_Watson:      return "Dr. Watson";
        case CharacterType::Sister:         return "Sister";
        case CharacterType::Invman:         return "Invisible Man";
        case CharacterType::InvmanToken:    return "Fog Token";
    }
    return "";
}
