#pragma once

#include "Heroes.h"
#include "Card.h"
#include "Enums.h"

#include <vector>

class SherlockHolmes : public Heroes
{
    private:
        Dr_Watson dr_watson;
    public:
        SherlockHolmes();
        int discard_hand();
        virtual void initial_deck() override;
        virtual void assign_sidekicks() override;
};
