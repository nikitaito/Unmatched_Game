
#include "front.h"
#include <ctime>

using namespace ftxui;


int main() {
    srand(time(nullptr));
    auto screen = ScreenInteractive::FitComponent();

    Space space(2 , {5,6,7} , {10,31} , {LIGHT_BLUE , BROWN ,DARK_BLUE , YELLOW});

    Game  gamect;

    Page current_page = Page::Menu;

    Main_menu menu;
    Help_page help;
    Age_page age;
    Game_page game;

    int age1;
    int age2;


    auto menu_page = menu.Make_menu_page(current_page , screen);
    auto help_page = help.Make_page(current_page);
    auto age_page = age.Make_page(current_page , & gamect);
    auto game_page = game.Make_page(current_page , &gamect , &space);


    auto root = CatchEvent(
    Renderer([&] {
        switch (current_page) {
        case Page::Menu:
            return menu_page->Render();

        case Page::Help:
            return help_page->Render();

        case Page :: Age:
            return age_page->Render();

        case Page::Game:
            return game_page->Render();

        case Page::End:
            return text("End");
        }

        return text("Unknown");
    }),
    [&](Event event) -> bool {
        switch (current_page) {
        case Page::Menu:
            return menu_page->OnEvent(event);

        case Page::Help:
            return help_page->OnEvent(event);
        
        case Page :: Age:
            return age_page->OnEvent(event);

        case Page:: Game:
            return game_page->OnEvent(event);

        case Page::End:
            return false;
        }

        return false;
    });

    screen.Loop(root);
}
