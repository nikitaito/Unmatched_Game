#include "front.h"
#include <string>
#include <sstream>
#include <regex>
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

Component Age_page::Make_page(Page& current_page, Game* game) {
    error_message.clear();

    auto input1 = Input(&st_age1, "Please Enter the age of player one : ");
    auto input2 = Input(&st_age2, "Please Enter the age of player two : ");

    auto exit = Button("Exit", [&current_page] {
        current_page = Page::Menu;
    });

    auto next = Button("Next", [this, &current_page, game] {
        int age1;
        int age2;

        if (!ParseAge(st_age1, age1) || !ParseAge(st_age2, age2)) {
            error_message = "Age must be a positive number and cannot be empty.";
            return;
        }

        error_message.clear();

        std::pair<int, CharacterType> p1{ age1 , CharacterType::SherlockHolmes};

        std::pair<int, CharacterType> p2{ age2 , CharacterType::Dracula};

        game->choose(p1, p2);
        game->inital_hand_cards();

        current_page = Page::Game;
    });

    auto container = Container::Vertical({
        input1,
        input2,
        next,
        exit
    });

    return Renderer(container, [this, input1, input2, exit, next] {
        Elements elements = {
            text("UNMATCHED") | bold | color(Color::Yellow) | center,
            separator(),
            input1->Render(),
            separator(),
            input2->Render(),
            separator(),
            next->Render() | color(Color::Green),
            exit->Render() | color(Color::Red)
        };

        if (!error_message.empty()) {
            elements.push_back(
                text(error_message) | bold | color(Color::Red)
            );
        }

        return vbox(elements)
             | border
             | size(HEIGHT, EQUAL, 15);
    });
}

Element Game_page :: Node(std::string character, Color col) {
    return text("(" + character + ")") | color(col) | bold;
} 

Component Game_page::Make_map(std :: vector<Space> Graph) {
    std :: vector<Element> Nodes;
    for (auto & it : Graph){
        Color col;
        std :: string character;
        if(it.get_Hero() && it.get_Hero()->get_name() == CharacterType :: SherlockHolmes){
            character = "S";
            col = Color :: Blue; 
        }
        else if(it.get_Hero() && it.get_Hero()->get_name() == CharacterType :: Dracula){
            character = "D";
            col = Color :: Red; 
        }
        else if(it.get_comrade() && it.get_comrade()->get_name() == CharacterType :: Dr_Watson){
            character = "d";
            col = Color :: Blue; 
        }
        else if(it.get_comrade() && it.get_comrade()->get_name() == CharacterType :: Sister){
            character = "s";
            col = Color :: Red; 
        }
        else if(!(it.get_Hidden_way().empty())){
            character = "~";
            col = Color :: Green;
        }
        else{
            character = "-";
            col = Color :: White;
        }
        Nodes.push_back(Node(character , col));

    }


    return Renderer([Nodes]{
        return vbox({
            text("Map") | color(Color :: Green) | center,
            separator() | color(Color :: Yellow),
            hbox({text("   ") , Nodes[0] , text("-----") , Nodes[1] , text("          ") , Nodes[5] , text("-----") , Nodes[6] , text("    ") ,Nodes[29] , text("-----") , Nodes[31] , text("       ")}),
            hbox({text("   /          \\         /  \\   /  \\   /   \\          ")}),
            hbox({text(" ") , Nodes[2] , text("---") ,Nodes[3], text("     \\--") ,Nodes[4], text("--/    ") ,Nodes[7], text("----") ,Nodes[28], text("----") ,Nodes[30], text("           ")}),
            hbox({text("  |       \\        |                |      |            ")}),
            hbox({text(" ") ,Nodes[10], text("--") ,Nodes[9], text("--") ,Nodes[8] , text("------                |      |             ")}),
            hbox({text("   \\                                |      |            ")}),
            hbox({text("    ") , Nodes[11], text("---") ,Nodes[12], text("---") ,Nodes[13], text("---") ,Nodes[14], text("           |     ") ,Nodes[22], text("            ")}),
            hbox({text("       \\           \\     \\_________") ,Nodes[21], text("___/   \\___") , Nodes[23] , text(" ")}),
            hbox({text("        |            ") , Nodes[15], text("______     /  \\  \\") ,Nodes[24], text("____/|    ")}),
            hbox({text("        |            /  \\     \\   /    \\          |   ")}),
            hbox({text("       ") ,Nodes[18], text("---") ,Nodes[17], text("---") ,Nodes[16], text("---") ,Nodes[19], text("---") ,Nodes[20], text("------") , Nodes[25], text("------") ,Nodes[26], text("     ")}),
            hbox({text("                                          \\     /       ")}),
            hbox({text("                                           ") , Nodes[27], text("_/         ")}),
            separator() | color(Color :: Yellow),
            text("Legend :"),
            text("(D) Draacula") | color(Color :: Red),
            text("(S) Sherlock Holmes") | color(Color :: Blue),
            text("(-) Normal location") ,
            text("(~) Hidden way") | color(Color :: Green)
        }) | borderStyled(Color :: Yellow);
    });
}

Component Game_page :: Make_Dashboard_dracula(Heroes * hero, int dis){
    int Hp = hero->get_HP();
    int Hp_max = hero->get_HP_max();
    int Deck = hero->get_deck_cards().size();
    int Move = hero->get_Movement();
    std :: string attack ;
    switch (hero->get_Attacktype())
    {
        case Attacktype :: MELEE:
            attack = "MELEE";
            break;
        
        case Attacktype :: RANGED:
            attack = "RANGED";
            break;
    }

    std :: string HP = "[";
    for(int i = 1 ; i <= Hp_max ; i++){
        if(i <= Hp)
            HP += "#";
        else
            HP += " ";
    }
    HP += ']';
    return Renderer([Hp, Hp_max, Deck, dis , HP , attack , Move]{
        return vbox({
            text("DRACULA") | color(Color :: Red) | center,
            hbox({text("Health: "),text(std::to_string(Hp)) | color(Color::Red),text(" / " + std::to_string(Hp_max))})|center,
            text(HP) | color(Color :: Red) | center,
            hbox({text("Range : ") , text(attack)}) | center,
            hbox({text("Move : ") , text(std :: to_string(Move))})| center,
            text("-------------------------------------------------------") | color(Color :: Red) | center | bold,
            hbox({text("Deck : ") , text(std :: to_string(Deck))}) | center ,
            text("-------------------------------------------------------") | color(Color :: Red) | center | bold,
            hbox({text("Discard : ") , text(std :: to_string(dis))}) | center
        }) | borderStyled(Color::Red) | bold | size(WIDTH, EQUAL, 55);
    });
}

Component Game_page :: Make_Dashboard_sherlock(Heroes * hero, int dis){
    int Hp = hero->get_HP();
    int Hp_max = hero->get_HP_max();
    int Deck = hero->get_deck_cards().size();
    int Move = hero->get_Movement();
    std :: string attack ;
    switch (hero->get_Attacktype())
    {
        case Attacktype :: MELEE:
            attack = "MELEE";
            break;
        
        case Attacktype :: RANGED:
            attack = "RANGED";
            break;
    }

    std :: string HP = "[";
    for(int i = 1 ; i <= Hp_max ; i++){
        if(i <= Hp)
            HP += "#";
        else
            HP += " ";
    }
    HP += ']';
    return Renderer([Hp, Hp_max, Deck, dis , HP , attack , Move]{
        return vbox({
            text("SHERLOCK HOLMES") | color(Color :: Blue) | center,
            hbox({text("Health: "),text(std::to_string(Hp)) | color(Color::Blue),text(" / " + std::to_string(Hp_max))})|center,
            text(HP) | color(Color :: Blue) | center,
            hbox({text("Range : ") , text(attack)}) | center,
            hbox({text("Move : ") , text(std :: to_string(Move))})| center,
            text("-------------------------------------------------------") | color(Color :: Blue) | center | bold,
            hbox({text("Deck : ") , text(std :: to_string(Deck))}) | center ,
            text("-------------------------------------------------------") | color(Color :: Blue) | center | bold,
            hbox({text("Discard : ") , text(std :: to_string(dis))}) | center
        }) | borderStyled(Color::Blue) | bold | size(WIDTH, EQUAL, 55);
    });
}

Component Game_page :: Make_card(const Card & card , int index){

    Color col ;
    std :: string type;
    std :: string card_name;
    std :: string user_type;
    std :: string Power;
    std :: string timing;
    std :: string boost = std :: to_string(card.get_Boost());

    switch (card.get_CardType())
    {
        case CardType :: ATTACK :
            col = Color :: Red;
            type = "[ATTACK]";
            break;
        
        case CardType :: DEFENSE :
            col = Color :: Blue;
            type = "[DEFENSE]";
            break;
        case CardType :: BOTH :
            col = Color :: Purple;
            type = "[BOTH]";
            break;
        case CardType :: EVENT :
            col = Color :: Yellow;
            type = "[EVENT]";
            break;
    }

    ////////////////////////////////////

    switch (card.get_CardName()){
        case CardName::Feedingfrenzy:
            card_name = "Feeding Frenzy";
            break;
        case CardName::Mistform:
            card_name = "Mistform";
            break;
        case CardName::Ambush:
            card_name = "Ambush";
            break;
        case CardName::Baptism_of_blood:
            card_name = "Baptism of Blood";
            break;
        case CardName::Beastform:
            card_name = "Beastform";
            break;
        case CardName::Dash:
            card_name = "Dash";
            break;
        case CardName::Exploit:
            card_name = "Exploit";
            break;
        case CardName::Look_into_my_eyes:
            card_name = "Look Into My Eyes";
            break;
        case CardName::Prey_upon:
            card_name = "Prey Upon";
            break;
        case CardName::Ravening_Seduction:
            card_name = "Ravening Seduction";
            break;
        case CardName::Thirst_for_sustenance:
            card_name = "Thirst for Sustenance";
            break;
        case CardName::Administer_Aid:
            card_name = "Administer Aid";
            break;
        case CardName::Confirm_Suspicion:
            card_name = "Confirm Suspicion";
            break;
        case CardName::Counterpunch:
            card_name = "Counterpunch";
            break;
        case CardName::Deduce_Strategy:
            card_name = "Deduce Strategy";
            break;
        case CardName::Education_Never_Ends:
            card_name = "Education Never Ends";
            break;
        case CardName::Elementary:
            card_name = "Elementary";
            break;
        case CardName::Eliminate_The_Impossible:
            card_name = "Eliminate The Impossible";
            break;
        case CardName::Feint:
            card_name = "Feint";
            break;
        case CardName::Fixed_Point_in_a_Changing_Age:
            card_name = "Fixed Point in a Changing Age";
            break;
        case CardName::Master_of_Disguise:
            card_name = "Master of Disguise";
            break;
        case CardName::The_Game_Is_Afoot:
            card_name = "The Game Is Afoot";
            break;
        case CardName::Service_Revolver:
            card_name = "Service Revolver";
            break;
        case CardName::Study_Methods:
            card_name = "Study Methods";
            break;
        default:
            card_name = "Unknown";
            break;
    }

    ////////////////////////

    switch (card.get_usertype()) {
        case Usertype::DR_WATSON:
            user_type = "Dr. Watson";
            break;

        case Usertype::HOLMES:
            user_type = "Holmes";
            break;

        case Usertype::SISTER:
            user_type = "Sister";
            break;

        case Usertype::DRACULA:
            user_type = "Dracula";
            break;

        case Usertype::ANY:
            user_type = "Any";
            break;

        default:
            user_type = "Unknown";
            break;
    }
    ////////////////////////////
    switch (card.get_CardTiming())
    {
        case CardTiming::During:
            timing = "DURING";
            break;

        case CardTiming::Before:
            timing = "BEFORE";
            break;

        case CardTiming::After:
            timing = "AFTER";
            break;

        case CardTiming::Immediate:
            timing = "IMMEDIATE";
            break;
    }
    /////////////////////////////////

    if(card.get_Attack() != 0)
        Power = std :: to_string(card.get_Attack());
    else if(card.get_Defense() != 0)
        Power = std :: to_string(card.get_Defense());
    else
        Power = "ϟ";

    return Renderer([col , type , card_name ,user_type , Power , boost , timing , index]{
        return vbox({
            text("#" + std :: to_string(index)) | center | bold | color(Color :: White),
            text(type) | center | color(col) | bold,
            separator() | color(col),
            hbox({
                text(user_type),
                filler(),
                text(Power) | color(col),
            }),
            separator() | color(col),
            paragraphAlignCenter(card_name),
            separator() | color(col),
            text("Boost: " + boost) | center,
            separator() | color(col),
            text(timing) | center | bold,
        })
        | size(WIDTH, EQUAL, 12)
        | size(HEIGHT, EQUAL, 12)
        | borderStyled(col);
    }); 
}

Component Game_page :: Make_hand_cards (const std::vector<Card> & cards) {
    std::vector<Component> components;

    for (size_t i = 0; i < cards.size(); ++i)
        components.push_back(Make_card(cards[i] , static_cast<int>(i) + 1));

    return Renderer([components = std::move(components)] {
        std::vector<Element> rows;

        const int per_row = 4;

        for (size_t i = 0; i < components.size(); i += per_row) {
            std::vector<Element> row;

            for (size_t j = i; j < std::min(i + per_row, components.size()); ++j)
                row.push_back(components[j]->Render());

            rows.push_back(hbox(std::move(row)));
        }

        return vbox(std::move(rows));
    });
}

void Game_page :: ExecuteCommand(Game * game){
    std :: istringstream iss(command);
    std :: string cmd;
    iss >> cmd;

    Player * turnPlayer = game->get_turn();
    CharacterType actorType = turnPlayer->get_hero()->get_name();
    std :: string err;

    if(cmd.empty())
        return;

    if(cmd == "help" || cmd == "quit"){
        AddActionLog(actorType , cmd);
        return;
    }

    if(cmd == "hand"){
        std :: string summary = "Hand size: " + std :: to_string(turnPlayer->get_hand_cards().size());
        AddActionLog(actorType , summary);
        return;
    }

    if(cmd == "deck"){
        std :: string summary = "Deck size: " + std :: to_string(turnPlayer->get_hero()->get_deck_cards().size());
        AddActionLog(actorType , summary);
        return;
    }

    if(cmd == "Action<Maneuver>"){
        AcSt = Action_State :: Maneuver;
        if(game->Maneuver(turnPlayer , err))
            AddActionLog(actorType , "Maneuver: drew a card.");
        else
            AddActionLog(actorType , "Maneuver failed: " + err);
        return;
    }

    if(cmd == "Action<Attack>"){
        AcSt = Action_State :: Attack;
        AddActionLog(actorType , "Attack: use 'attack <from> <to>' to declare.");
        return;
    }

    if(cmd == "Action<Scheme>"){
        AcSt = Action_State :: Scheme;
        AddActionLog(actorType , "Scheme: use 'scheme <index> <current> <target> [value] [A|D]'.");
        return;
    }

    if(cmd == "move"){
        int from , to;
        if(!(iss >> from >> to)){
            AddActionLog(actorType , "Usage: move <from> <to>");
            return;
        }
        if(game->MoveFighter(turnPlayer , from , to , err))
            AddActionLog(actorType , "Moved from " + std :: to_string(from) + " to " + std :: to_string(to));
        else
            AddActionLog(actorType , "Move failed: " + err);
        return;
    }

    if(cmd == "attack"){
        int from , to;
        if(!(iss >> from >> to)){
            AddActionLog(actorType , "Usage: attack <from> <to>");
            return;
        }
        if(game->DeclareAttack(turnPlayer , from , to , err))
            AddActionLog(actorType , "Attack declared. Use 'play <index>' to choose your Attack card.");
        else
            AddActionLog(actorType , "Attack failed: " + err);
        return;
    }

    if(cmd == "play"){
        int index;
        if(!(iss >> index)){
            AddActionLog(actorType , "Usage: play <card_index>");
            return;
        }
        index -= 1; // hand indices are shown 1-based to the player

        CombatStage stage = game->get_CombatStage();
        if(stage == CombatStage :: AwaitAttackCard){
            if(game->PlayAttackCard(index , err))
                AddActionLog(actorType , "Attack card played. Defender may 'play <index>' a Defense card or 'skip'.");
            else
                AddActionLog(actorType , "Could not play card: " + err);
        }
        else if(stage == CombatStage :: AwaitDefenseCard){
            if(game->PlayDefenseCard(index , err))
                AddActionLog(actorType , "Defense card played. Use 'resolve' to resolve combat.");
            else
                AddActionLog(actorType , "Could not play card: " + err);
        }
        else{
            AddActionLog(actorType , "There is no pending combat card to play.");
        }
        return;
    }

    if(cmd == "skip"){
        if(game->get_CombatStage() == CombatStage :: AwaitDefenseCard){
            game->SkipDefense();
            AddActionLog(actorType , "Defense skipped. Use 'resolve' to resolve combat.");
        }
        else{
            AddActionLog(actorType , "There is nothing to skip right now.");
        }
        return;
    }

    if(cmd == "resolve"){
        if(game->get_CombatStage() != CombatStage :: Ready){
            AddActionLog(actorType , "Combat is not ready to resolve yet.");
            return;
        }
        int moveDestination = -1;
        std :: vector<int> discardIndices;
        if(iss >> moveDestination){
            int extra;
            while(iss >> extra)
                discardIndices.push_back(extra - 1);
        }
        else{
            moveDestination = -1;
        }
        auto log = game->ResolveCombat(moveDestination , discardIndices);
        for(auto & line : log)
            AddActionLog(actorType , line);
        AcSt = Action_State :: None;
        return;
    }

    if(cmd == "scheme"){
        int index , current_space , target_space;
        int guessedValue = 0;
        std :: string valueKind;
        if(!(iss >> index >> current_space >> target_space)){
            AddActionLog(actorType , "Usage: scheme <index> <current> <target> [value] [A|D]");
            return;
        }
        iss >> guessedValue;
        bool guessAttack = true;
        if(iss >> valueKind && !valueKind.empty() && (valueKind[0] == 'D' || valueKind[0] == 'd'))
            guessAttack = false;

        index -= 1;
        std :: vector<std :: string> log;
        if(game->PlayScheme(turnPlayer , index , current_space , target_space , guessedValue , guessAttack , err , log)){
            AddActionLog(actorType , "Scheme resolved.");
            for(auto & line : log)
                AddActionLog(actorType , line);
        }
        else{
            AddActionLog(actorType , "Scheme failed: " + err);
        }
        return;
    }

    if(cmd == "bloodharvest"){
        int target_space;
        if(!(iss >> target_space)){
            AddActionLog(actorType , "Usage: bloodharvest <target_space>");
            return;
        }
        if(game->BloodHarvest(turnPlayer , target_space , err))
            AddActionLog(actorType , "Blood Harvest: dealt 1 damage and drew a card.");
        else
            AddActionLog(actorType , "Blood Harvest failed: " + err);
        return;
    }

    if(cmd == "discard"){
        int index;
        if(!(iss >> index)){
            AddActionLog(actorType , "Usage: discard <card_index>");
            return;
        }
        index -= 1;
        if(game->DiscardExcess(turnPlayer , index , err))
            AddActionLog(actorType , "Discarded a card.");
        else
            AddActionLog(actorType , "Discard failed: " + err);
        return;
    }

    if(cmd == "end"){
        if(game->CanEndTurn(turnPlayer)){
            game->EndTurn();
            AcSt = Action_State :: None;
            AddActionLog(actorType , "Turn ended.");
        }
        else{
            AddActionLog(actorType , "Cannot end turn yet: use both actions and discard down to 7 cards.");
        }
        return;
    }

    AddActionLog(actorType , "Unknown command: " + command);
}

Component Game_page :: Make_command_input(Game * game){
    return Input(&command, "Enter Command...")
        | bgcolor(Color::Black) 
        | CatchEvent([& , game](Event event) {
            if (event == Event::Return) {
                ExecuteCommand(game);
                command.clear();
                return true;
            }
            return false;
        });
}

Component Game_page :: Make_game_command(){
    return Renderer([] {
        return vbox({
            text("GAME COMMANDS ") | color(Color::Yellow),
            text(""),
            text("Action<Maneuver> - draw a card (start of Maneuver)") | color(Color :: Yellow1),
            text("move <from> <to> - move a fighter between spaces") | color(Color :: Yellow1),
            text("Action<Attack> - begin the Attack action") | color(Color :: Yellow1),
            text("attack <from> <to> - declare attacker/target") | color(Color :: Yellow1),
            text("play <card_index> - play the pending Attack/Defense card (1-based)") | color(Color :: Yellow1),
            text("skip - skip playing a Defense card") | color(Color :: Yellow1),
            text("resolve [destination] [discard_idx...] - resolve the declared combat") | color(Color :: Yellow1),
            text("  (destination needed for After-combat move cards like Dash / The Game Is Afoot)") | color(Color :: Yellow1),
            text("  (Beastform: discard_idx... = hand card #s to discard for +1 Attack each)") | color(Color :: Yellow1),
            text("Action<Scheme> - begin the Scheme action") | color(Color :: Yellow1),
            text("scheme <index> <current> <target> [value] [A|D] - play a Scheme card") | color(Color :: Yellow1),
            text("  (Confirm Suspicion: value=guess, A/D=which stat)") | color(Color :: Yellow1),
            text("  (Eliminate the Impossible: value=opponent card # to discard)") | color(Color :: Yellow1),
            text("bloodharvest <target_space> - Dracula's start-of-turn ability") | color(Color :: Yellow1),
            text("discard <card_index> - discard down to 7 cards") | color(Color :: Yellow1),
            text("end - end your turn") | color(Color :: Yellow1),
            text("hand - Show your hand") | color(Color :: Yellow1),
            text("deck - Show deck info") | color(Color :: Yellow1),
            text("help - Show this help") | color(Color :: Yellow1),
            text("quit - Quit game") | color(Color :: Yellow1),
        }) | borderStyled(Color :: Yellow) | size(WIDTH, EQUAL, 74) | size(HEIGHT, EQUAL, 26);
    });
}

Component Game_page::Make_action_log() {
    return Renderer([this] {
        std::vector<Element> row;

        for (auto& e : action_log)
            row.push_back(text(e));

        return vbox({
            text("ACTION LOG :") | color(Color::Yellow),
            text(""),
            vbox(std::move(row)),
            text("...")
        }) | borderStyled(Color::Yellow)
          | size(WIDTH, EQUAL, 55) | size(HEIGHT, EQUAL, 11);
    });
}

void Game_page::AddActionLog(const CharacterType & chtype, const std :: string& command) {
    std :: string name;
    switch (chtype)
    {
    case CharacterType ::Dracula :
        name = "Dracula";
        break;
    
    case CharacterType ::SherlockHolmes :
        name = "Sherlock";
        break;
    case CharacterType ::Sister :
        name = "Sister";
        break;
    case CharacterType ::Dr_Watson :
        name = "Dr_Watson";
        break;
    }
    action_log.push_back(">" + name + " : " + command);

    if (action_log.size() > 6)
        action_log.erase(action_log.begin());
}

Component Game_page::Make_location_info(Space space) {
    std::vector<Element> zone;
    std :: string neighbor;

    for (auto& it : space.get_zone()) {
        switch (it) {
            case LIGHT_BLUE:
                zone.push_back(text("Light Blue"));
                break;

            case DARK_BLUE:
                zone.push_back(text("Dark Blue"));
                break;

            case BROWN:
                zone.push_back(text("Brown"));
                break;

            case YELLOW:
                zone.push_back(text("Yellow"));
                break;

            case GREEN:
                zone.push_back(text("Green"));
                break;

            case PURPULE:
                zone.push_back(text("Purple"));
                break;

            case GRAY:
                zone.push_back(text("Gray"));
                break;
        }
    }

    for(auto & it : space.get_neighbor()){
        std :: string x;
        x = "n" + std :: to_string(it) +", ";
        neighbor.append(x);

    }

    return Renderer([zone = std::move(zone), space , neighbor] {
        std::vector<Element> row;
        row.push_back(text("Zone : "));

        for (const auto& e : zone){
            row.push_back(e);
            row.push_back(text(","));
        }
        
        return vbox({
            text("LOCATION INFO :") | color(Color::Yellow),
            text(""),
            text("Current Location : n" + std::to_string(space.get_id())),
            text("Connected to : " + neighbor),
            text(""),
            separator() | color(Color :: Yellow),
            text(""),
            hbox(std::move(row)),
            text(""),
        }) | borderStyled(Color :: Yellow) | size(WIDTH, EQUAL, 55);
    });
}

Component Game_page :: Make_page(Page& current_page , Game* game , Space * space){
    left = Renderer([this , game]{
        return vbox({
            Make_Dashboard_dracula(game->get_player_of_hero(CharacterType :: Dracula)->get_hero(), game->get_player_of_hero(CharacterType :: Dracula)->get_dis_cards().size())->Render(),
            Make_hand_cards(game->get_player_of_hero(CharacterType :: Dracula)->get_hand_cards())->Render(),
            Make_action_log()->Render()
        });
    });

    map = Renderer([this , game]{
        return vbox({
            Make_map(game->get_Board()->get_spaces())->Render(),
            Make_game_command()->Render()
        });
    });

    right = Renderer([this  ,space , game ]{
        return vbox({
            Make_Dashboard_sherlock(game->get_player_of_hero(CharacterType :: SherlockHolmes)->get_hero(), game->get_player_of_hero(CharacterType :: SherlockHolmes)->get_dis_cards().size())->Render(),
            Make_hand_cards(game->get_player_of_hero(CharacterType ::SherlockHolmes)->get_hand_cards())->Render(),
            Make_location_info(*space)->Render()
        });
    });
    
    auto input = Make_command_input(game);

    bottom = Container::Vertical({
        input,
    });

    return Renderer(bottom , [this , game] {
        return vbox({
            text("UNMATCHED") | bold | color(Color::Yellow) | center,
            separator() | color(Color::Cyan1),
            hbox({ text("Turn : ")  , text(game->get_turn()->get_name())}) | center,
            separator() | color(Color::Cyan1),
            hbox({ left->Render()   | flex, map->Render() | flex, right->Render()  | flex}),
            separator() | color(Color::Cyan1),
            bottom->Render() 
        }) | borderStyled(Color :: Yellow);
    });
}

Component end_page :: Make_page(const std::string winner,const std::string loser) {

    return Renderer([=] {

        return vbox({
            filler(),

            hbox({
                filler(),

                vbox({
                    text("Unmatched") | bold | color(Color::Yellow) | center,
                    separator(),

                    text("🏆 Winner") | bold | color(Color::Green) | center,
                    text(winner) | color(Color::GreenLight) | center,

                    separator(),

                    text("💀 Loser") | bold | color(Color::Red) | center,
                    text(loser) | color(Color::RedLight) | center,
                })
                | borderHeavy
                | size(WIDTH, EQUAL, 50),

                filler(),
            }),
            
            filler(),
        })| bgcolor(Color::Black);
    });
}


