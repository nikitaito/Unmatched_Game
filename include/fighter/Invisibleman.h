#pragma once

#include "Heroes.h"
#include "Enums.h"
#include "InvisibleManToken.h"

#include <vector>

class Invman : public Heroes
{
    private:
        InvisibleManToken token1;
        InvisibleManToken token2;
        InvisibleManToken token3;

    public:
        Invman();
        virtual void initial_deck() override;
        virtual void assign_sidekicks() override;
        virtual std :: vector<Sidekick *> get_sidekick() override;

};