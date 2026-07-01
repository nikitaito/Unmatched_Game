#pragma once

#include "Heroes.h"
#include "Card.h"
#include "Enums.h"

#include <vector>

class SherlockHolmes : public Heroes
{
    public:
        SherlockHolmes();
        int discard_hand();
        virtual void initial_deck() override;
        virtual void initial_sidekicks() override;
};
