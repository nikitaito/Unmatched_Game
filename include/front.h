#ifndef FRONT_H
#define FRONT_H

#include <ftxui/component/component_options.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <vector>

enum class Page {
    Menu,
    Help,
    Age,
    Game,
    End
};

class Main_menu
{
    private:
        std :: vector <std :: string> option = {"Exit" , "Play" , "Help"};
    public:
        ftxui :: Component Make_menu_page(Page & , ftxui :: ScreenInteractive &);
};

class Help_page
{
    public:
        ftxui :: Component Make_page(Page &);
};

class Age_page
{
    private:
        std::string st_age1;
        std::string st_age2;
        std::string error_message;

        bool ParseAge(const std::string& , int&);   
    public:
        ftxui :: Component Make_page(Page& , int & , int &);
};

class Game_page
{
    public:
        ftxui :: Component Make_page(Page&);

};




#endif


