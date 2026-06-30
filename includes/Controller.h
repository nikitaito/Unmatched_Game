#pragma once

#include "Card.h"
#include "Controller.h"
#include "Dracula.h"
#include "SherlockHolmes.h"

#include <string>

class Controller
{
private:
    Dracula dracula;
    SherlockHolmes sherlock;

    Card Dracula_selected_card;
    Card Sherlock_selected_card;

    int DraculaAction = 2;
    int SherlockAction = 2;

public:
    Dracula *get_Dracula();
    SherlockHolmes *get_SherlockHolmes();

    int get_DraculaAction() const;
    void set_DraculaAction();

    int get_SherlockAction() const;
    void set_SherlockAction();

    Card get_Dracula_selected_card();
    Card get_Sherlock_selected_card();

    int dis_sumcards(); // Removes as many cards as the player wants
};