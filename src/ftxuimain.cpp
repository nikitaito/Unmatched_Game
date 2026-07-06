
#include "front.h"

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::TerminalOutput();

    Page current_page = Page::Menu;

    Main_menu menu;
    Help_page help;
    Age_page age;

    int age1;
    int age2;

    auto menu_page = menu.Make_menu_page(current_page , screen);
    auto help_page = help.Make_page(current_page);
    auto age_page = age.Make_page(current_page , age1 , age2);


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
            return text("Game");

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
            return false;

        case Page::End:
            return false;
        }

        return false;
    });

    screen.Loop(root);
}
