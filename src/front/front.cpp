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

void Front :: StartMatch(){
    if(gameStarted)
        return;
    gameStarted = true;

    int pos1 = (rand() % 2 == 0) ? 4 : 24;
    int pos2 = (pos1 == 4) ? 24 : 4;
    game.choose(character1, character2, pos1, pos2);
    game.inital_hand_cards();

    combatPage.Init(Rectangle{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() });
    combatPage.backgroundImage = combatBackground;
    combatPage.centerIcon = swordIcon;
}

Texture2D Front :: PortraitFor(CharacterType t){
    switch(t){
        case CharacterType :: Dracula:        return draculaPortrait;
        case CharacterType :: Invman:         return invManPortrait;
        case CharacterType :: SherlockHolmes: return holmesPortrait;
        default: return Texture2D{};
    }
}

Texture2D Front :: GamePortraitFor(CharacterType t){
    switch(t){
        case CharacterType :: Dracula:        return draculaPortrait;
        case CharacterType :: Invman:         return invManGamePortrait;
        case CharacterType :: SherlockHolmes: return holmesPortrait;
        default: return Texture2D{};
    }
}

Color Front :: HeroColorFor(CharacterType t){
    switch(t){
        case CharacterType :: SherlockHolmes: return Color{ 235, 200, 60, 255 };
        case CharacterType :: Invman:         return Color{ 70, 140, 235, 255 };
        case CharacterType :: Dracula:        return Color{ 200, 40, 45, 255 };
        default: return RAYWHITE;
    }
}

std :: vector<BoardPieceVisual> Front :: BuildBoardPieces(){
    std :: vector<BoardPieceVisual> pieces;
    auto &spaces = game.get_Board()->get_spaces();

    auto sisterTextureFor = [&](Sidekick *sk, Heroes *owner) -> Texture2D {
        auto list = owner->get_sidekick();
        for(size_t i = 0; i < list.size(); ++i){
            if(list[i] == sk)
                return (i == 0) ? sister1Token : (i == 1) ? sister2Token : sister3Token;
        }
        return Texture2D{};
    };

    for(size_t i = 0; i < spaces.size(); ++i){
        int space = (int)i;

        if(Heroes *hero = spaces[i].get_Hero()){
            BoardPieceVisual v;
            v.space = space;
            v.isHeroDot = true;
            v.color = HeroColorFor(hero->get_name());
            pieces.push_back(v);
        }

        if(Sidekick *comrade = spaces[i].get_comrade()){
            if(comrade->get_islive()){
                Player *owner = game.get_owner(comrade->get_name());
                Heroes *ownerHero = owner ? owner->get_hero() : nullptr;

                BoardPieceVisual v;
                v.space = space;
                v.isHeroDot = false;
                if(comrade->get_name() == CharacterType :: Dr_Watson)
                    v.texture = watsonToken;
                else if(comrade->get_name() == CharacterType :: Sister && ownerHero)
                    v.texture = sisterTextureFor(comrade, ownerHero);
                pieces.push_back(v);
            }
        }

        if(spaces[i].get_token()){
            BoardPieceVisual v;
            v.space = space;
            v.isFogToken = true;
            v.texture = fogToken;
            pieces.push_back(v);
        }
    }

    return pieces;
}

HeroPanelData Front :: BuildHeroPanel(Player *p){
    HeroPanelData data;
    Heroes *hero = p->get_hero();
    data.portrait  = GamePortraitFor(hero->get_name());
    data.name      = CharacterDisplayName(hero->get_name());
    data.currentHP = hero->get_HP();
    data.maxHP     = hero->get_HP_max();

    int sisterIndex = 0;
    for(Sidekick *sk : hero->get_sidekick()){
        if(!sk) continue;
        bool tokenKind = (sk->get_name() == CharacterType :: InvmanToken);
        if(!tokenKind && !sk->get_islive()) continue;

        SidekickVisual v{};
        if(sk->get_name() == CharacterType :: Dr_Watson){
            v.texture = watsonToken;
        }
        else if(sk->get_name() == CharacterType :: Sister){

            switch(sisterIndex){
                case 0:  v.texture = sister1Token; break;
                case 1:  v.texture = sister2Token; break;
                default: v.texture = sister3Token; break;
            }
            sisterIndex++;
        }
        else if(tokenKind){
            v.texture = fogToken;
        }
        v.showLife  = !tokenKind;
        v.currentHP = tokenKind ? 0 : sk->get_Health();
        v.maxHP     = tokenKind ? 0 : sk->get_Health_max();
        data.sidekicks.push_back(v);
    }
    return data;
}

void Front :: PopulateHand(CPHandMenu &menu, Player &p){
    auto &hand = p.get_hand_cards();
    CharacterType owner = p.get_hero()->get_name();
    int n = std :: min((int)hand.size(), CP_MAX_HAND);
    menu.count = n;
    for(int i = 0; i < n; ++i){
        Card &c = hand[i];
        CPHandCard &slot = menu.cards[i];
        Texture2D tex = CardTextureFor(c.get_CardName(), owner);
        slot.cardId    = i;
        slot.texture   = tex;
        slot.hasTexture = (tex.id != 0) ? 1 : 0;
        slot.name      = CardDisplayName(c.get_CardName());
        slot.statLine  = CardStatLine(c.get_CardType(), c.get_Attack(), c.get_Defense(), c.get_Boost());
        slot.type      = c.get_CardType();
        slot.disabled  = false;
    }
}

void Front :: PopulateDeckAndDiscard(){
    Player *p1 = game.get_player(1);
    Player *p2 = game.get_player(2);

    auto fillDeck = [](Player *p, std :: vector<Texture2D> &texOut, std :: vector<std :: string> &labelOut){

        int n = (int)p->get_hero()->get_deck_cards().size();
        texOut.assign(n, Texture2D{});
        labelOut.assign(n, std :: string());
    };
    auto fillDiscard = [this](Player *p, std :: vector<Texture2D> &texOut, std :: vector<std :: string> &labelOut){

        auto &pile = p->get_dis_cards();
        CharacterType owner = p->get_hero()->get_name();
        texOut.clear();
        labelOut.clear();
        for(auto &c : pile){
            texOut.push_back(CardTextureFor(c.get_CardName(), owner));
            labelOut.push_back(CardDisplayName(c.get_CardName()));
        }
    };

    fillDeck(p1, gamePage.leftDeckCards, gamePage.leftDeckLabels);
    fillDiscard(p1, gamePage.leftDiscardCards, gamePage.leftDiscardLabels);
    fillDeck(p2, gamePage.rightDeckCards, gamePage.rightDeckLabels);
    fillDiscard(p2, gamePage.rightDiscardCards, gamePage.rightDiscardLabels);
}

std :: string Front :: BuildTurnLabel(){
    Player *t = game.get_turn();
    return std :: string(CharacterDisplayName(t->get_hero()->get_name())) + "'s Turn";
}

std :: vector<int> Front :: OwnFighterSpaces(Player *p){
    std :: vector<int> out;
    auto &spaces = game.get_Board()->get_spaces();
    for(size_t i = 0; i < spaces.size(); ++i){
        Heroes *h = spaces[i].get_Hero();
        Sidekick *s = spaces[i].get_comrade();
        if(h && game.get_owner(h->get_name()) == p) out.push_back((int)i);
        else if(s && s->get_islive() && game.get_owner(s->get_name()) == p) out.push_back((int)i);
    }
    return out;
}

std :: vector<int> Front :: EnemyFighterSpaces(Player *p){
    std :: vector<int> out;
    Player *opp = game.get_opponent(p);
    auto &spaces = game.get_Board()->get_spaces();
    for(size_t i = 0; i < spaces.size(); ++i){
        Heroes *h = spaces[i].get_Hero();
        Sidekick *s = spaces[i].get_comrade();
        if(h && game.get_owner(h->get_name()) == opp) out.push_back((int)i);
        else if(s && s->get_islive() && game.get_owner(s->get_name()) == opp) out.push_back((int)i);
    }
    return out;
}

