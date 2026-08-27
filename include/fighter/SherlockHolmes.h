#pragma once

#include "Heroes.h"
#include "Enums.h"

#include <vector>

class SherlockHolmes : public Heroes
{
    private:
        Dr_Watson dr_watson;
    public:
        SherlockHolmes();
        virtual void initial_deck() override;
        virtual void assign_sidekicks() override;
        virtual std :: vector<Sidekick *> get_sidekick() override;
};
