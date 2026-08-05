
#include "front/front.h"
#include <ctime>
#include "raylib.h"
#include "Enums.h"
#include "front/main_menu.h"
#include "front/age_page.h"

using namespace ftxui;


int main() {
    // srand(time(nullptr));
    // auto screen = ScreenInteractive::FitComponent();

    // Space space(2 , {5,6,7} , {10,31} , {LIGHT_BLUE , BROWN ,DARK_BLUE , YELLOW});

    // Game  gamect;

    // Page current_page = Page::Menu;

    // Main_menu menu;
    // Help_page help;
    // Age_page age;
    // Game_page game;

    // int age1;
    // int age2;


    // auto menu_page = menu.Make_menu_page(current_page , screen);
    // auto help_page = help.Make_page(current_page);
    // auto age_page = age.Make_page(current_page , & gamect);
    // auto game_page = game.Make_page(current_page , &gamect , &space);


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
    //         return game_page->Render();

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
    //         return game_page->OnEvent(event);

    //     case Page::End:
    //         return false;
    //     }

    //     return false;
    // });

    // screen.Loop(root);

    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "UNMATCHED");
    SetTargetFPS(60);

    
    Texture2D background = LoadTexture("../assets/background.png");

    Font titleFont    = LoadFontEx("../assets/fonts/Cinzel-Bold.ttf", 128, 0, 0);
    Font subtitleFont = LoadFontEx("../assets/fonts/Cinzel-Bold.ttf", 64, 0, 0);
    Font buttonFont   = LoadFontEx("../assets/fonts/Cinzel-SemiBold.ttf", 64, 0, 0);

    
    if (titleFont.texture.id == 0)    titleFont = GetFontDefault();
    if (subtitleFont.texture.id == 0) subtitleFont = GetFontDefault();
    if (buttonFont.texture.id == 0)   buttonFont = GetFontDefault();

    SetTextureFilter(titleFont.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(subtitleFont.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(buttonFont.texture, TEXTURE_FILTER_BILINEAR);

    
    Page current_page = Page::Menu;
    int age1 = 0;
    int age2 = 0;

    Main_Menu menuPage;
    AgePage agePage;

    
    while (!WindowShouldClose() && current_page != Page::Exit)
    {
        switch (current_page)
        {
            case Page::Menu:
                menuPage.make_Page(current_page, background, titleFont, subtitleFont, buttonFont);
                break;

            case Page::Age:
                agePage.Make_Page(current_page, background, titleFont, buttonFont , age1, age2);
                break;

            case Page::Help:
                current_page = Page::Menu;
                break;

            case Page::Choose:
                current_page = Page::Menu;
                break;

            default:
                current_page = Page::Exit;
                break;
        }
    }

    
    UnloadTexture(background);
    UnloadFont(titleFont);
    UnloadFont(subtitleFont);
    UnloadFont(buttonFont);
    CloseWindow();

    return 0;

}
