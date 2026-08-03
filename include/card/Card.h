#pragma once

#include <string>
#include <functional>
#include <vector>
#include <memory>
#include "Enums.h"
#include "Effect.h"

class Card
{

    private:
        CardName name;
        CardTiming timing;      
        CardType cardtype; 
        Usertype usertype;
        int Attack;
        int Defense;
        int Boost;

        bool ApplyEffects{true};
        std :: vector<std :: unique_ptr<Effect>> Effects;
    public:
        Card() = default;
        Card(CardName, CardTiming, CardType, Usertype , int, int, int , std :: vector<std :: unique_ptr<Effect>>);

        //  Card(const Card&) = delete;
        // Card& operator=(const Card&) = delete;

        // Card(Card&&) noexcept = default;
        // Card& operator=(Card&&) noexcept = default;

        CardName get_CardName() const;
        CardTiming get_CardTiming() const;
        CardType get_CardType() const;
        Usertype get_usertype() const;

        int get_Boost() const;
        void set_Boost(int);

        int get_Attack() const;
        void set_Attack(int);

        int get_Defense() const;
        void set_Defence(int);

        bool get_ApplyEffects();
        void set_ApplyEffects(bool);

        std :: vector<std :: unique_ptr<Effect>>& get_effects() ;
        
        bool operator==(const Card & );

        // ~Card();
};