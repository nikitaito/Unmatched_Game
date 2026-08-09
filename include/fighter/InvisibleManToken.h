#pragma once

#include "Sidekick.h"

class InvisibleManToken : public Sidekick
{
    public:
        InvisibleManToken();
        ~InvisibleManToken() override = default;

        bool occupies_space() const override;

        // this token has no life the way Dr_Watson/Sister do: it can't be
        // removed from the board by taking damage
        bool get_islive() const override;
        void Damage(int) override;
};
