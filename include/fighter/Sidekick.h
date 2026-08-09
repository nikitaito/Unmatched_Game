#pragma once

#include<string>
#include "Enums.h"

class Sidekick
{

    private:
        CharacterType name;
        Attacktype attacktype;
        int Health;
        int Health_max;
        int Movement;

    public:
        Sidekick(CharacterType, Attacktype, int, int);

        //get and set
        Attacktype get_Attacktype() const;
        int get_Movement() const;    
        int get_Health() const;
        int get_Health_max() const;
        CharacterType get_name() const;

        void Heal(int);

        //virtual
        virtual bool occupies_space() const { return true; }
        virtual void Damage(int);
        virtual bool get_islive() const;
        virtual ~Sidekick() = 0;

};