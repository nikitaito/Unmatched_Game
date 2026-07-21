#pragma once

#include "Heroes.h"
#include "Card.h"
#include "Enums.h"

#include <vector>

class Dracula : public Heroes
{
    private:
        Sister sister1;
        Sister sister2;
        Sister sister3;

    public:
        Dracula();

        virtual void initial_deck() override ;
        virtual void assign_sidekicks() override;
        virtual std :: vector<Sidekick *> get_sidekick() override;
    

};