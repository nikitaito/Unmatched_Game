#include "front.h"
#include <string>
using namespace ftxui;


Component Main_menu :: Make_menu_page(Page & current_page , ScreenInteractive & screen){
    auto play = Button("Play", [&]{current_page = Page :: Age;});

    auto exit = Button("Exit", [&]{screen.Exit();});

    auto help = Button("Help" , [&]{current_page = Page :: Help;});

    auto container = Container::Vertical({
        play,
        exit,
        help
    });

    return Renderer(container , [play , exit , help] {
        return vbox({
            text("UNMATCHED") | bold | color(Color::Yellow) | center,
            separator(),
            play->Render() | color(Color :: Green),
            exit->Render() | color(Color :: Red),
            help->Render() | color(Color :: Blue)
        }) | border | center;
    });
}

Component Help_page :: Make_page(Page& current_page) {

    std::string help_text = 
        "Step into an arena where history, mythology, and fiction collide. "
        "Unmatched is an exhilarating board game that lets legendary warriors and "
        "iconic heroes face off in unforgettable duels. Master unique abilities, "
        "outthink your opponents, and unleash powerful combinations as every "
        "battle tells a different story.";

    auto paragraph_element = paragraph(help_text)
                           | size(WIDTH, LESS_THAN, 60)  // حداکثر عرض ۶۰ کاراکتر
                           | border
                           | center;

    auto exit = Button("Exit", [&] { current_page = Page::Menu; });

    auto paragraph_component = Renderer([paragraph_element] {
        return paragraph_element;
    });

    auto container = Container::Vertical({
        paragraph_component,
        exit,
    });

    return Renderer(container, [exit , paragraph_component ] {
        return vbox({
            text("UNMATCHED") | bold | color(Color::Yellow) | center,
            separator(),
            paragraph_component->Render() | flex, 
            exit->Render() | color(Color :: Red) | center 
        }) | border | size(HEIGHT, EQUAL, 15); 
    });
}

bool Age_page :: ParseAge(const std::string& str, int& age) {
    try {
        size_t pos;
        age = std::stoi(str, &pos);

        if (pos != str.size() || age < 0)
            return false;

        return true;
    }
    catch (...) {
        return false;
    }
}

Component Age_page::Make_page(Page& current_page, int& age1, int& age2) {
    
    error_message.clear();

    auto input1 = Input(&st_age1, "Please Enter the age of player one : ");
    auto input2 = Input(&st_age2, "Please Enter the age of player two : ");

    auto exit = Button("Exit", [&] { current_page = Page::Menu; });

    auto next = Button("Next", [this, &current_page, &age1, &age2] {
        if (!ParseAge(st_age1, age1) || !ParseAge(st_age2, age2)) {
            error_message = "Age must be a positive number and cannot be empty.";
            return;
        }
        error_message.clear();
        current_page = Page::Game;
    });

    auto container = Container::Vertical({input1, input2, next, exit});

    return Renderer(container, [this, input1, input2, exit, next] {
        Elements elements = {
            text("UNMATCHED") | bold | color(Color::Yellow) | center,
            separator(),
            input1->Render() ,
            separator(),
            input2->Render() ,
            separator(),
            next->Render() | color(Color::Green),
            exit->Render() | color(Color::Red) ,
        };

        if (!error_message.empty()) {
            elements.push_back(text(error_message) | bold | color(Color::Red));
        }

        return vbox(elements) | border | size(HEIGHT, EQUAL, 15);
    });
}

Component Game_page :: Make_page(Page& current_page){
    
}

