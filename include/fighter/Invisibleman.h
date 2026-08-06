#pragma once

#include "Heroes.h"
#include "Enums.h"

#include <vector>

class Invman : public Heroes
{
    private:
        

    public:
        Invman();

        std::vector<Sidekick *> get_sisters();
        virtual void initial_deck() override ;
        virtual void assign_sidekicks() override;
        virtual std :: vector<Sidekick *> get_sidekick() override;
    

};