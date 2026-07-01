#pragma once

#include "Heroes.h"
#include "Card.h"
#include "Enums.h"

#include <vector>

class Dracula : public Heroes
{
    public:
        Dracula();

        std::vector<Sidekick> get_sisters();
        void DrawnCard();
        virtual void initial_deck() override ;
        virtual void initial_sidekicks() override;

    

};