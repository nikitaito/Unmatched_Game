#pragma once

#include<string>
#include "Enums.h"

class Sidekick
{

    private:
        CharacterType name;
        Attacktype attacktype;
        int Health;
        int Movement;

    public:
        Sidekick(CharacterType, Attacktype, int, int);

        //get and set
        bool get_islive() const;
        Attacktype get_Attacktype() const;
        int get_Movement() const;    
        int get_Health() const;
        CharacterType get_name() const;

        void Damage(int);
        void Heal(int);

        //virtual
        virtual ~Sidekick() = 0;

};