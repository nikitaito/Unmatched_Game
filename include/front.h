#ifndef FRONT_H
#define FRONT_H

#include <ftxui/component/component_options.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/canvas.hpp>
#include <vector>
#include "game.h"
#include "Card.h"
#include "Enums.h"

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
        ftxui :: Component Make_page(Page& , Game *);
};

class Game_page
{
    private:
        ftxui :: Element Node(std::string , ftxui :: Color );
        void ExecuteCommand(Game * );
        void AddActionLog(const CharacterType & , const std :: string&);
        ftxui :: Component left;
        ftxui :: Component right;
        ftxui :: Component map;
        ftxui :: Component bottom;
        ftxui :: Component middle;
        std :: string command;
        std :: vector<std ::string> action_log;

        Action_State AcSt = Action_State :: None;
        int movestaion;
        std :: string cardname;
    public:
        ftxui :: Component Make_Dashboard_dracula(Heroes*,int);
        ftxui :: Component Make_Dashboard_sherlock(Heroes*,int);
        ftxui :: Component Make_card(const Card &);
        ftxui :: Component Make_hand_cards(const std :: vector<Card> &);
        ftxui :: Component Make_map(std :: vector <Space>);
        ftxui :: Component Make_command_input(Game *);
        ftxui :: Component Make_location_info(Space);
        ftxui :: Component Make_game_command();
        ftxui :: Component Make_action_log();
        ftxui :: Component Make_page(Page& , Game* , Space *);

};

class end_page
{
    private:

    public:
        ftxui :: Component Make_page(const std :: string  , const std :: string );
};

class Front
{
    private:
    public:
};



#endif


