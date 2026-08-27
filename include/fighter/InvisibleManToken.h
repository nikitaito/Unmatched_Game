#pragma once

#include "Sidekick.h"

class InvisibleManToken : public Sidekick
{
    public:
        InvisibleManToken();
        ~InvisibleManToken() override = default;

        bool occupies_space() const override;
        bool get_islive() const override;
        void Damage(int) override;
};
