#pragma once

#include "Heroes.h"
#include "Sisters.h"
#include "Card.h"

#include <vector>

class Dracula : public Heroes
{

private:
    //... متعلقات و کارت ها

    Sisters s1, s2, s3;

    std::vector<Sisters *> sisters{&s1, &s2, &s3};

    std::vector<Card> deck;
    std::vector<Card> hand;
    std::vector<Card> discard;

public:
    Dracula();

    std::vector<Sisters *> get_sisters();
    void DrawnCard();

    

};