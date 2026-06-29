#pragma once

#include "Heroes.h"
#include "Dr_Watson.h"
#include"Card.h"

#include<vector>

class SherlockHolmes : public Heroes
{
private:
    //... متعلقات و کارت ها

    Dr_Watson Watson;

    std::vector<Card> deck;
public:
    SherlockHolmes();
};
