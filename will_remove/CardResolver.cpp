#include "CardResolver.h"
#include "Card.h"

void CardResolver::excute(Card *selectedcard, Controller *controller)
{

    if (controller != nullptr)
    {
        switch (selectedcard->get_CardType())
        {

        case CardType::Feedingfrenzy:
        {
            if (selectedcard->get_ApplyEffects())
            {
            }
            break;
        }

        case CardType::Mistform:
        {
            if (selectedcard->get_ApplyEffects())
            {
                // put Dracula in any space ...

                controller->set_DraculaAction();
            }
            break;
        }

        case CardType::Ambush:
        {
            if (selectedcard->get_ApplyEffects())
            {
                selectedcard->set_Boost(controller->get_SherlockHolmes()->discard_hand());
                // بعد از محاسبه این مقدار افزایش یافه برمیگردد
            }

            break;
        }

        case CardType::Baptism_of_blood:
        {
            if (selectedcard->get_ApplyEffects())
            {
                controller->get_Dracula()->set_Health(2);

                {
                    for (auto const &s : controller->get_Dracula()->get_sisters())
                    {
                        if (s->get_islive() == false)
                        {
                            // put on Dracula zone ...
                        }
                    }
                }
            }
        }
        case CardType::Beastform:
        {
            if (selectedcard->get_ApplyEffects())
            {
                // selectet much cards in hand ... (how Draw front ?)

                selectedcard->set_Attack(controller->dis_sumcards() /* ... */);
            }

            break;
        }

        case CardType::Dash:
        {
            if (selectedcard->get_ApplyEffects())
            {
                // مبارز را تا سه خانه میتوان جابجا کرد
            }

            break;
        }

        case CardType::Exploit:
        {
            if (selectedcard->get_ApplyEffects())
            {
                controller->get_Dracula()->DrawnCard();
            }

            break;
        }

        case CardType::Look_into_my_eyes:
        {
            if (selectedcard->get_ApplyEffects())
            {
                selectedcard->set_Defence(controller->get_Sherlock_selected_card().get_Boost());
                // بعد از محاسبه این مقدار افزایش یافه برمیگردد
            }

            break;
        }

        case CardType::Prey_upon:
        {
            if (selectedcard->get_ApplyEffects())
            {
                // ...
            }

            break;
        }

        case CardType::Ravening_Seduction:
        {
            if (selectedcard->get_ApplyEffects())
            {

                // ؟؟؟ ...
            }

            break;
        }

        case CardType::Thirst_for_sustenance:
        {
            if (selectedcard->get_ApplyEffects())
            {
                if (3 - (controller->get_Sherlock_selected_card().get_Defense()) >= 1)
                {
                    // قرار دادن دراکولا در هر خانه ای کنار مبارز های حریف
                }
            }
            break;
        }
        case CardType::Feint:
        {
            if (selectedcard->get_ApplyEffects())
            {
                controller->get_Sherlock_selected_card().set_ApplyEffects(false);
                break;
            }
        }
        }
    }
}
