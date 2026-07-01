#include "Controller.h"

int Controller::get_DraculaAction() const
{
    return DraculaAction;
}

void Controller::set_DraculaAction()
{
    DraculaAction++;
}

int Controller::get_SherlockAction() const
{
    return SherlockAction;
}

void Controller::set_SherlockAction()
{
    SherlockAction++;
}

Dracula *Controller::get_Dracula()
{
    return &dracula;
}

SherlockHolmes *Controller::get_SherlockHolmes()
{
    return &sherlock;
}

Card Controller::get_Dracula_selected_card()
{
    return Dracula_selected_card;
}

Card Controller::get_Sherlock_selected_card()
{
    return Sherlock_selected_card;
}