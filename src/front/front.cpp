#include "front/front.h"
#include "card/CardText.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

Front :: Front(){
    srand((unsigned int)time(nullptr));
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(1280, 720, "UNMATCHED");
    SetTargetFPS(60);
    LoadAssets();
    gamePage.Init();
}

Front :: ~Front(){
    if(sceneTexture.id != 0)
        UnloadRenderTexture(sceneTexture);
    UnloadAssets();
    CloseWindow();
}

void Front :: LoadAssets(){
    background = LoadTexture("../assets/background.png");
    mapTexture = LoadTexture("../assets/board_map.png");

    draculaPortrait = LoadTexture("../assets/dracula/Dracula_wallpaper.png");
    invManPortrait  = LoadTexture("../assets/invisibleMan/invArt.png");
    holmesPortrait  = LoadTexture("../assets/sherlock/holmsArt.png");

    invManGamePortrait = LoadTexture("../assets/invisibleMan/inv_wallpaper.png");

    sister1Token = LoadTexture("../assets/dracula/sis1.png");
    sister2Token = LoadTexture("../assets/dracula/sis2.png");
    sister3Token = LoadTexture("../assets/dracula/sis3.png");
    fogToken     = LoadTexture("../assets/invisibleMan/fog.png");
    watsonToken  = LoadTexture("../assets/sherlock/drwatson.png");

    combatBackground = LoadTexture("../assets/combatpage.png");
    swordIcon        = LoadTexture("../assets/sword1.png");

    titleFont    = LoadFontEx("../assets/fonts/Cinzel-ExtraBold.ttf", 128, 0, 0);
    subtitleFont = LoadFontEx("../assets/fonts/Cinzel-Bold.ttf", 64, 0, 0);
    buttonFont   = LoadFontEx("../assets/fonts/Cinzel-SemiBold.ttf", 64, 0, 0);
    labelFont    = LoadFontEx("../assets/fonts/Cinzel-Medium.ttf", 48, 0, 0);

    if(titleFont.texture.id == 0)    titleFont = GetFontDefault();
    if(subtitleFont.texture.id == 0) subtitleFont = GetFontDefault();
    if(buttonFont.texture.id == 0)   buttonFont = GetFontDefault();
    if(labelFont.texture.id == 0)    labelFont = GetFontDefault();

    SetTextureFilter(titleFont.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(subtitleFont.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(buttonFont.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(labelFont.texture, TEXTURE_FILTER_BILINEAR);

    struct CardOwnerPair { CardName name; CharacterType owner; };
    static const CardOwnerPair cardsToLoad[] = {

        { CardName::Feedingfrenzy, CharacterType::Dracula },
        { CardName::Mistform, CharacterType::Dracula },
        { CardName::Ambush, CharacterType::Dracula },
        { CardName::Baptism_of_blood, CharacterType::Dracula },
        { CardName::Beastform, CharacterType::Dracula },
        { CardName::Dash, CharacterType::Dracula },
        { CardName::Exploit, CharacterType::Dracula },
        { CardName::Look_into_my_eyes, CharacterType::Dracula },
        { CardName::Prey_upon, CharacterType::Dracula },
        { CardName::Ravening_Seduction, CharacterType::Dracula },
        { CardName::Thirst_for_sustenance, CharacterType::Dracula },
        { CardName::Feint, CharacterType::Dracula },

        { CardName::Administer_Aid, CharacterType::SherlockHolmes },
        { CardName::Confirm_Suspicion, CharacterType::SherlockHolmes },
        { CardName::Counterpunch, CharacterType::SherlockHolmes },
        { CardName::Deduce_Strategy, CharacterType::SherlockHolmes },
        { CardName::Education_Never_Ends, CharacterType::SherlockHolmes },
        { CardName::Elementary, CharacterType::SherlockHolmes },
        { CardName::Eliminate_The_Impossible, CharacterType::SherlockHolmes },
        { CardName::Feint, CharacterType::SherlockHolmes },
        { CardName::Fixed_Point_in_a_Changing_Age, CharacterType::SherlockHolmes },
        { CardName::Master_of_Disguise, CharacterType::SherlockHolmes },
        { CardName::The_Game_Is_Afoot, CharacterType::SherlockHolmes },
        { CardName::Service_Revolver, CharacterType::SherlockHolmes },
        { CardName::Study_Methods, CharacterType::SherlockHolmes },

        { CardName::Coded_Notes, CharacterType::Invman },
        { CardName::ConFound, CharacterType::Invman },
        { CardName::Covert_PreParation, CharacterType::Invman },
        { CardName::Deaming_of_Revenge, CharacterType::Invman },
        { CardName::Emerge_from_Mist, CharacterType::Invman },
        { CardName::Impossible_to_See, CharacterType::Invman },
        { CardName::Into_Thin_Air, CharacterType::Invman },
        { CardName::Lurking, CharacterType::Invman },
        { CardName::Reign_of_Terror, CharacterType::Invman },
        { CardName::Rolling_Fog, CharacterType::Invman },
        { CardName::Slip_Away, CharacterType::Invman },
        { CardName::Step_Lightly, CharacterType::Invman },
        { CardName::Vanish, CharacterType::Invman },
    };

    for(const auto &entry : cardsToLoad){
        const char *path = CardImagePath(entry.name, entry.owner);
        if(path[0] == '\0' || cardArt.find(path) != cardArt.end())
            continue;
        cardArt[path] = LoadTexture(path);
    }
}

Texture2D Front :: CardTextureFor(CardName name, CharacterType owner){
    const char *path = CardImagePath(name, owner);
    auto it = cardArt.find(path);
    return (it != cardArt.end()) ? it->second : Texture2D{};
}

void Front :: UnloadAssets(){
    if(background.id)         UnloadTexture(background);
    if(mapTexture.id)          UnloadTexture(mapTexture);
    if(draculaPortrait.id)     UnloadTexture(draculaPortrait);
    if(invManPortrait.id)      UnloadTexture(invManPortrait);
    if(holmesPortrait.id)      UnloadTexture(holmesPortrait);
    if(invManGamePortrait.id)  UnloadTexture(invManGamePortrait);
    if(sister1Token.id)        UnloadTexture(sister1Token);
    if(sister2Token.id)        UnloadTexture(sister2Token);
    if(sister3Token.id)        UnloadTexture(sister3Token);
    if(fogToken.id)            UnloadTexture(fogToken);
    if(watsonToken.id)         UnloadTexture(watsonToken);
    if(combatBackground.id)    UnloadTexture(combatBackground);
    if(swordIcon.id)           UnloadTexture(swordIcon);

    for(auto &entry : cardArt)
        if(entry.second.id) UnloadTexture(entry.second);
    cardArt.clear();

    Font def = GetFontDefault();
    if(titleFont.texture.id != def.texture.id)    UnloadFont(titleFont);
    if(subtitleFont.texture.id != def.texture.id) UnloadFont(subtitleFont);
    if(buttonFont.texture.id != def.texture.id)   UnloadFont(buttonFont);
    if(labelFont.texture.id != def.texture.id)    UnloadFont(labelFont);
}

void Front :: EnsureSceneTexture(){
    int w = GetScreenWidth(), h = GetScreenHeight();
    if(sceneTexture.id == 0 || sceneTexW != w || sceneTexH != h){
        if(sceneTexture.id != 0)
            UnloadRenderTexture(sceneTexture);
        sceneTexture = LoadRenderTexture(w, h);
        sceneTexW = w;
        sceneTexH = h;
    }
}

void Front :: ShowToast(const std :: string &msg){
    toastMessage = msg;
    toastTimer = 3.0f;
}

void Front :: DrawToast(){
    if(toastTimer <= 0.0f || toastMessage.empty())
        return;

    int sw = GetScreenWidth();
    float fontSize = 20.0f;
    Vector2 size = MeasureTextEx(labelFont, toastMessage.c_str(), fontSize, 1.0f);
    Rectangle box{ sw / 2.0f - size.x / 2 - 20, 16, size.x + 40, size.y + 20 };

    float alpha = (toastTimer < 0.5f) ? (toastTimer / 0.5f) : 1.0f;
    DrawRectangleRounded(box, 0.3f, 8, Fade(Color{ 40, 18, 18, 235 }, alpha));
    DrawRectangleRoundedLinesEx(box, 0.3f, 8, 2, Fade(Color{ 200, 90, 80, 255 }, alpha));
    DrawTextEx(labelFont, toastMessage.c_str(), { box.x + 20, box.y + 10 }, fontSize, 1.0f, Fade(RAYWHITE, alpha));
}

void Front :: Run(){
    while(!WindowShouldClose() && currentPage != Page :: Exit){
        if(currentPage != priorPage){
            if(currentPage == Page :: Age)    agePage.Reset();
            if(currentPage == Page :: Choose) choosePage.Reset();
            priorPage = currentPage;
        }

        BeginDrawing();

        switch(currentPage){
            case Page :: Menu:
                menuPage.make_Page(currentPage, background, titleFont, subtitleFont, buttonFont);
                break;

            case Page :: Age:
                agePage.Make_Page(currentPage, background, titleFont, buttonFont, age1, age2);
                break;

            case Page :: Help:
                currentPage = Page :: Menu;
                break;

            case Page :: Choose:
                choosePage.Make_Page(currentPage, background, titleFont, labelFont,
                                      draculaPortrait, invManPortrait, holmesPortrait,
                                      age1, age2, character1, character2);
                break;

            case Page :: Game:
                StartMatch();
                UpdateAndDrawGame();
                break;

            default:
                currentPage = Page :: Exit;
                break;
        }

        if(toastTimer > 0.0f){
            toastTimer -= GetFrameTime();
            DrawToast();
        }

        EndDrawing();
    }
}

