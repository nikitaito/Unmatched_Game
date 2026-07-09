
#include "front.h"

using namespace ftxui;


int main() {
    auto screen = ScreenInteractive::FitComponent();
    Card card1(CardName ::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType ::BOTH , Usertype :: SISTER ,0, 0, 3);
    Card card2(CardName ::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType ::BOTH , Usertype :: SISTER ,0, 0, 3);

    Card card3(CardName ::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType ::BOTH , Usertype :: SISTER ,0, 0, 3);

    Card card4(CardName ::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType ::BOTH , Usertype :: SISTER ,0, 0, 3);

    Card card5(CardName ::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType ::BOTH , Usertype :: SISTER ,0, 0, 3);

    Card card6(CardName ::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType ::BOTH , Usertype :: SISTER ,0, 0, 3);

    Card card7(CardName ::Fixed_Point_in_a_Changing_Age, CardTiming::After, CardType ::BOTH , Usertype :: SISTER ,0, 0, 3);

    std :: vector<Card> cards = {card1 , card2 , card3 , card4 , card5 , card6 , card7};

    // SherlockHolmes sh;
    // Dracula dr;
    // Sister st;
    // Dr_Watson dw;
    // set_Hero(&sh , 5);
    // set_Hero(&dr , 6);
    // set_Comrade(&dw , 10);
    // set_Comrade(&st , 11);
    
    Page current_page = Page::Menu;

    // Main_menu menu;
    // Help_page help;
    // Age_page age;

    // int age1;
    // int age2;

    // auto menu_page = menu.Make_menu_page(current_page , screen);
    // auto help_page = help.Make_page(current_page);
    // auto age_page = age.Make_page(current_page , age1 , age2);


    // auto root = CatchEvent(
    // Renderer([&] {
    //     switch (current_page) {
    //     case Page::Menu:
    //         return menu_page->Render();

    //     case Page::Help:
    //         return help_page->Render();
    //     case Page :: Age:
    //         return age_page->Render();
    //     case Page::Game:
    //         return text("Game");

    //     case Page::End:
    //         return text("End");
    //     }

    //     return text("Unknown");
    // }),
    // [&](Event event) -> bool {
    //     switch (current_page) {
    //     case Page::Menu:
    //         return menu_page->OnEvent(event);

    //     case Page::Help:
    //         return help_page->OnEvent(event);
        
    //     case Page :: Age:
    //         return age_page->OnEvent(event);

    //     case Page:: Game:
    //         return false;

    //     case Page::End:
    //         return false;
    //     }

    //     return false;
    // });

    Game_page game;
    end_page end;

    screen.Loop(game.Make_page(current_page , cards));
}
