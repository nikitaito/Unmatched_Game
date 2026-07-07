#pragma once

#include<string>
#include "Enums.h"

class Sidekick
{

    private:
        std::string name;
        Attacktype attacktype;
        int Health;
        int Movement;

    public:
        Sidekick(std::string, Attacktype, int, int);

        //get and set
        bool get_islive() const;
        Attacktype get_Attacktype() const;
        int get_Movement() const;    
        int get_Health() const;

        void Damage(int);

        //virtual
        virtual ~Sidekick() = 0;

};