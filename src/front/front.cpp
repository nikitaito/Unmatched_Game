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
    mapTexture = LoadTexture("../assets/map.png");

    draculaPortrait = LoadTexture("../assets/dracula/Dracula_wallpaper.png");
    invManPortrait  = LoadTexture("../assets/invisibleMan/inv_wallpaper.png");
    holmesPortrait  = LoadTexture("../assets/sherlock/sherlock_wallpaper.png");

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

std :: vector<Front :: InputStep> Front :: StepsForScheme(CardName name) const{
    using S = InputStep;
    switch(name){
        case CardName :: Administer_Aid:
        case CardName :: Master_of_Disguise:
        case CardName :: Mistform:
        case CardName :: Baptism_of_blood:
        case CardName :: Ravening_Seduction:
            return { S :: CurrentSpace, S :: TargetSpace };
        case CardName :: Confirm_Suspicion:
            return { S :: Prediction };
        case CardName :: Eliminate_The_Impossible:
            return { S :: OpponentCard };
        case CardName :: Rolling_Fog:
            return { S :: FogSpace, S :: FogDest };
        case CardName :: Step_Lightly:

            return { S :: TargetSpace };
        case CardName :: Vanish:
            return { S :: TargetSpace };
        default:
            return {};
    }
}

std :: vector<Front :: InputStep> Front :: StepsForCombat(CardName atk, bool hasDef, CardName def) const{
    using S = InputStep;
    std :: vector<S> steps;
    auto need = [&](S s){
        if(std :: find(steps.begin(), steps.end(), s) == steps.end())
            steps.push_back(s);
    };
    auto consider = [&](CardName name){
        switch(name){
            case CardName :: Dash:
            case CardName :: The_Game_Is_Afoot:
                need(S :: MoveDestination); break;
            case CardName :: Into_Thin_Air:
                need(S :: SelfMoveDestination); need(S :: FogSpace); need(S :: FogDest); break;
            case CardName :: Lurking:
                need(S :: SelfMoveDestination); need(S :: FogSpace); need(S :: FogDest); break;
            case CardName :: Slip_Away:
                need(S :: FogSpace); need(S :: FogDest); break;
            case CardName :: Covert_PreParation:
                need(S :: FogSpace); need(S :: FogDest);
                need(S :: SecondFogSpace); need(S :: SecondFogDest); break;
            case CardName :: ConFound:
                need(S :: OpponentCard); break;
            case CardName :: Elementary:
                need(S :: Prediction); break;
            case CardName :: Beastform:
                need(S :: BoostDiscard); break;
            default: break;
        }
    };
    consider(atk);
    if(hasDef) consider(def);
    return steps;
}

void Front :: BeginSchemeFlow(int handIndex, CardName name){
    flowKind = FlowKind :: Scheme;
    flowHandIndex = handIndex;
    flowCardName = name;
    flowSteps = StepsForScheme(name);
    flowStepIndex = 0;
    flowCurrent = flowTarget = -1;
    flowFogSpace = flowFogDest = -1;
    flowSecondFogSpace = flowSecondFogDest = -1;
    flowGuessValue = 0;
    flowGuessAttack = true;
    predictionDraftValue = 0;
    predictionDraftAttack = true;

    if(flowSteps.empty()){
        FinishFlow();
    } else {
        mode = Mode :: Flow;
    }
}

void Front :: BeginCombatFollowupFlow(){
    flowKind = FlowKind :: CombatFollowup;
    flowAttackCardName = game.get_CombatAttackCardName();
    flowHasDefenseCard = game.get_CombatHasDefense();
    flowDefenseCardName = flowHasDefenseCard ? game.get_CombatDefenseCardName() : CardName{};
    flowSteps = StepsForCombat(flowAttackCardName, flowHasDefenseCard, flowDefenseCardName);
    flowStepIndex = 0;
    flowMoveDestination = flowSelfMoveDestination = -1;
    flowFogSpace = flowFogDest = -1;
    flowSecondFogSpace = flowSecondFogDest = -1;
    flowBoostIndices.clear();
    flowGuessValue = 0;
    flowGuessAttack = true;
    predictionDraftValue = 0;
    predictionDraftAttack = true;

    if(flowSteps.empty()){
        FinishFlow();
    } else {
        mode = Mode :: Flow;
    }
}

void Front :: AdvanceFlow(){
    flowStepIndex++;
    if(flowStepIndex >= flowSteps.size())
        FinishFlow();
}

void Front :: CancelFlow(){
    flowKind = FlowKind :: None;
    flowSteps.clear();
    flowStepIndex = 0;
    mode = Mode :: Idle;
}

void Front :: FinishFlow(){
    if(flowKind == FlowKind :: Scheme){
        std :: string err;
        std :: vector<std :: string> log;
        Player *turnPlayer = game.get_turn();
        bool ok = game.PlayScheme(turnPlayer, flowHandIndex, flowCurrent, flowTarget,
                                   flowGuessValue, flowGuessAttack, err, log,
                                   flowFogSpace, flowFogDest, flowSecondFogSpace, flowSecondFogDest);
        if(!ok) ShowToast(err);
        else if(!log.empty()) ShowToast(log.back());
    }
    else if(flowKind == FlowKind :: CombatFollowup){
        auto log = game.ResolveCombat(flowMoveDestination, flowBoostIndices, flowSelfMoveDestination,
                                       flowFogSpace, flowFogDest, {}, flowGuessValue, flowGuessAttack,
                                       flowSecondFogSpace, flowSecondFogDest);
        showingCombatResult = true;
        combatPage.showingResult = true;
        combatPage.resultLog.clear();
        for(auto &l : log){ combatPage.resultLog += l; combatPage.resultLog += "\n"; }
    }

    flowKind = FlowKind :: None;
    flowSteps.clear();
    flowStepIndex = 0;
    flowCurrent = flowTarget = -1;
    flowFogSpace = flowFogDest = -1;
    flowSecondFogSpace = flowSecondFogDest = -1;
    flowMoveDestination = flowSelfMoveDestination = -1;
    flowBoostIndices.clear();
    flowGuessValue = 0;
    flowGuessAttack = true;
    mode = Mode :: Idle;
}

void Front :: DrawFlowPrompt(const char *question){
    int sw = GetScreenWidth();
    float fontSize = 22.0f;
    Vector2 size = MeasureTextEx(labelFont, question, fontSize, 1.0f);
    Rectangle box{ sw / 2.0f - size.x / 2 - 24, 16, size.x + 48, size.y + 24 };
    DrawRectangleRounded(box, 0.25f, 8, Color{ 20, 26, 45, 235 });
    DrawRectangleRoundedLinesEx(box, 0.25f, 8, 2, Color{ 212, 175, 90, 255 });
    DrawTextEx(labelFont, question, { box.x + 24, box.y + 12 }, fontSize, 1.0f, RAYWHITE);
}

void Front :: DrawPredictionPicker(){
    int sw = GetScreenWidth();
    float boxW = 460, boxH = 140;
    Rectangle box{ sw / 2.0f - boxW / 2, 90, boxW, boxH };
    DrawRectangleRounded(box, 0.08f, 8, Color{ 20, 26, 45, 240 });
    DrawRectangleRoundedLinesEx(box, 0.08f, 8, 2, Color{ 212, 175, 90, 255 });
    DrawTextEx(labelFont, "Name a printed value:", { box.x + 20, box.y + 14 }, 20, 1.0f, RAYWHITE);

    Vector2 mouse = GetMousePosition();
    bool leftClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    float cellSize = 44;
    float startX = box.x + 20;
    float rowY = box.y + 46;
    for(int v = 0; v <= 6; v++){
        Rectangle cell{ startX + v * (cellSize + 8), rowY, cellSize, cellSize };
        bool selected = (predictionDraftValue == v);
        bool hovering = CheckCollisionPointRec(mouse, cell);
        Color fill = selected ? Color{ 212, 175, 90, 255 } : (hovering ? Color{ 60, 70, 100, 255 } : Color{ 35, 46, 78, 255 });
        DrawRectangleRounded(cell, 0.2f, 6, fill);
        DrawRectangleRoundedLinesEx(cell, 0.2f, 6, 2, Color{ 198, 161, 91, 255 });
        const char *label = TextFormat("%d", v);
        Vector2 ls = MeasureTextEx(labelFont, label, 20, 1.0f);
        DrawTextEx(labelFont, label, { cell.x + cell.width / 2 - ls.x / 2, cell.y + cell.height / 2 - ls.y / 2 }, 20, 1.0f, selected ? Color{ 20, 24, 38, 255 } : RAYWHITE);
        if(leftClicked && hovering) predictionDraftValue = v;
    }

    Rectangle atkBtn{ box.x + 20, rowY + cellSize + 12, 90, 34 };
    Rectangle defBtn{ atkBtn.x + 100, atkBtn.y, 90, 34 };
    auto drawToggle = [&](Rectangle r, const char *label, bool active){
        DrawRectangleRounded(r, 0.2f, 6, active ? Color{ 212, 175, 90, 255 } : Color{ 35, 46, 78, 255 });
        DrawRectangleRoundedLinesEx(r, 0.2f, 6, 2, Color{ 198, 161, 91, 255 });
        Vector2 ls = MeasureTextEx(labelFont, label, 18, 1.0f);
        DrawTextEx(labelFont, label, { r.x + r.width / 2 - ls.x / 2, r.y + r.height / 2 - ls.y / 2 }, 18, 1.0f, active ? Color{ 20, 24, 38, 255 } : RAYWHITE);
    };
    drawToggle(atkBtn, "ATTACK", predictionDraftAttack);
    drawToggle(defBtn, "DEFENSE", !predictionDraftAttack);
    if(leftClicked && CheckCollisionPointRec(mouse, atkBtn)) predictionDraftAttack = true;
    if(leftClicked && CheckCollisionPointRec(mouse, defBtn)) predictionDraftAttack = false;

    Rectangle confirmBtn{ box.x + boxW - 130, atkBtn.y, 110, 34 };
    bool hoverConfirm = CheckCollisionPointRec(mouse, confirmBtn);
    DrawRectangleRounded(confirmBtn, 0.2f, 6, hoverConfirm ? Color{ 235, 200, 130, 255 } : Color{ 212, 175, 90, 255 });
    DrawRectangleRoundedLinesEx(confirmBtn, 0.2f, 6, 2, Color{ 198, 161, 91, 255 });
    Vector2 cs = MeasureTextEx(labelFont, "CONFIRM", 18, 1.0f);
    DrawTextEx(labelFont, "CONFIRM", { confirmBtn.x + confirmBtn.width / 2 - cs.x / 2, confirmBtn.y + confirmBtn.height / 2 - cs.y / 2 }, 18, 1.0f, Color{ 20, 24, 38, 255 });
    if(leftClicked && hoverConfirm){
        flowGuessValue = predictionDraftValue;
        flowGuessAttack = predictionDraftAttack;
        AdvanceFlow();
    }
}

void Front :: HandleFlowStep(){
    if(flowStepIndex >= flowSteps.size()){ FinishFlow(); return; }
    InputStep step = flowSteps[flowStepIndex];

    auto storeAndAdvance = [&](int value){
        switch(step){
            case InputStep :: CurrentSpace: flowCurrent = value; break;
            case InputStep :: TargetSpace: flowTarget = value; break;
            case InputStep :: FogSpace: flowFogSpace = value; break;
            case InputStep :: FogDest: flowFogDest = value; break;
            case InputStep :: SecondFogSpace: flowSecondFogSpace = value; break;
            case InputStep :: SecondFogDest: flowSecondFogDest = value; break;
            case InputStep :: MoveDestination: flowMoveDestination = value; break;
            case InputStep :: SelfMoveDestination: flowSelfMoveDestination = value; break;
            default: break;
        }
        AdvanceFlow();
    };

    switch(step){
        case InputStep :: CurrentSpace:
            DrawFlowPrompt("Select the fighter to move/act with (or Skip)");
            break;
        case InputStep :: TargetSpace:
            DrawFlowPrompt("Select the target space (or Skip)");
            break;
        case InputStep :: FogSpace:
            DrawFlowPrompt("Select a fog token to move (or Skip)");
            break;
        case InputStep :: FogDest:
            DrawFlowPrompt("Select where that fog token goes (or Skip)");
            break;
        case InputStep :: SecondFogSpace:
            DrawFlowPrompt("Opponent: select a different fog token (or Skip)");
            break;
        case InputStep :: SecondFogDest:
            DrawFlowPrompt("Opponent: select where it goes (or Skip)");
            break;
        case InputStep :: MoveDestination:
            DrawFlowPrompt("Select where to move after combat (or Skip)");
            break;
        case InputStep :: SelfMoveDestination:
            DrawFlowPrompt("Select your fighter's new space (or Skip)");
            break;

        case InputStep :: Prediction:
            DrawPredictionPicker();
            return;

        case InputStep :: OpponentCard: {
            DeckCardWindow *deckWin = gamePage.GetDeckCardWindow();
            if(!deckWin->IsOpen()){
                Player *turnPlayer = game.get_turn();
                bool attackCardIsConfound = (flowKind == FlowKind :: CombatFollowup && flowAttackCardName == CardName :: ConFound);

                Player *shownHandOwner;
                if(flowKind == FlowKind :: Scheme)
                    shownHandOwner = game.get_opponent(turnPlayer);
                else
                    shownHandOwner = attackCardIsConfound ? combatAttackerPlayer : combatDefenderPlayer;

                auto &hand = shownHandOwner->get_hand_cards();
                CharacterType handOwnerType = shownHandOwner->get_hero()->get_name();
                std :: vector<Texture2D> texs;
                std :: vector<std :: string> labels;
                for(auto &c : hand){
                    texs.push_back(CardTextureFor(c.get_CardName(), handOwnerType));
                    labels.push_back(CardDisplayName(c.get_CardName()));
                }

                bool allowDecline = (flowKind == FlowKind :: CombatFollowup) &&
                                     (flowAttackCardName == CardName :: ConFound ||
                                      (flowHasDefenseCard && flowDefenseCardName == CardName :: ConFound));
                size_t declineIndex = hand.size();
                if(allowDecline){
                    texs.push_back(Texture2D{});
                    labels.push_back("Decline (do not discard)");
                }

                std :: string title = allowDecline ? "Opponent's Hand - choose or decline" : "Opponent's Hand - choose one";
                deckWin->Open(texs, labels, title, true);
                deckWin->onCardClicked = [this, declineIndex](size_t idx){
                    flowGuessValue = ((int)idx == (int)declineIndex) ? 0 : (int)idx + 1;
                    gamePage.GetDeckCardWindow()->Close();

                    if(flowKind == FlowKind :: CombatFollowup && flowGuessValue == 0){

                        flowSteps.insert(flowSteps.begin() + flowStepIndex + 1,
                                          { InputStep :: FogSpace, InputStep :: FogDest });
                    }
                    AdvanceFlow();
                };
            }
            return;
        }

        case InputStep :: BoostDiscard: {
            DeckCardWindow *deckWin = gamePage.GetDeckCardWindow();
            if(!deckWin->IsOpen()){
                auto &hand = combatAttackerPlayer->get_hand_cards();
                CharacterType handOwnerType = combatAttackerPlayer->get_hero()->get_name();
                std :: vector<Texture2D> texs;
                std :: vector<std :: string> labels;
                for(auto &c : hand){
                    texs.push_back(CardTextureFor(c.get_CardName(), handOwnerType));
                    labels.push_back(CardDisplayName(c.get_CardName()));
                }
                deckWin->Open(texs, labels, "Discard cards for +1 Attack each (X to confirm)", true);
                deckWin->onCardClicked = [this](size_t idx){
                    auto it = std :: find(flowBoostIndices.begin(), flowBoostIndices.end(), (int)idx);
                    if(it == flowBoostIndices.end()) flowBoostIndices.push_back((int)idx);
                    else flowBoostIndices.erase(it);
                };
                return;
            }
            if(!deckWin->IsOpen())
                AdvanceFlow();
            return;
        }

        default:
            break;
    }

    Vector2 mouse = GetMousePosition();
    Rectangle skipBtn{ (float)GetScreenWidth() / 2 - 70, 90, 140, 40 };
    bool hoveringSkip = CheckCollisionPointRec(mouse, skipBtn);
    Color skipCol = hoveringSkip ? Color{ 200, 90, 80, 255 } : Color{ 90, 40, 40, 255 };
    DrawRectangleRounded(skipBtn, 0.3f, 6, skipCol);
    DrawRectangleRoundedLinesEx(skipBtn, 0.3f, 6, 2, RAYWHITE);
    Vector2 skipTextSize = MeasureTextEx(labelFont, "SKIP", 20, 1.0f);
    DrawTextEx(labelFont, "SKIP", { skipBtn.x + skipBtn.width / 2 - skipTextSize.x / 2, skipBtn.y + 10 }, 20, 1.0f, RAYWHITE);

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        if(hoveringSkip){
            storeAndAdvance(-1);
        } else {
            int space = gamePage.SpaceAt(mouse);
            if(space >= 0)
                storeAndAdvance(space);
        }
    }
}

void Front :: HandleIdleClicks(){
    Player *turnPlayer = game.get_turn();
    Vector2 mouse = GetMousePosition();

    if(mode == Mode :: Idle){
        if(CheckCollisionPointRec(mouse, gamePage.GetManeuverBtn())){
            std :: string err;
            if(!game.Maneuver(turnPlayer, err)){ ShowToast(err); return; }
            mode = Mode :: ManeuverPickFighter;
            return;
        }
        if(CheckCollisionPointRec(mouse, gamePage.GetAttackBtn())){
            if(turnPlayer->get_aciton() <= 0){ ShowToast("No actions remaining this turn."); return; }
            mode = Mode :: AttackPickAttacker;
            return;
        }
        if(CheckCollisionPointRec(mouse, gamePage.GetSchemeBtn())){
            if(turnPlayer->get_aciton() <= 0){ ShowToast("No actions remaining this turn."); return; }
            mode = Mode :: SchemePickCard;
            return;
        }
        if(CheckCollisionPointRec(mouse, gamePage.GetEndTurnBtn())){
            if(!game.CanEndTurn(turnPlayer)){
                if(turnPlayer->get_hand_cards().size() > 7) mode = Mode :: HandOverflow;
                else ShowToast("Use both actions before ending your turn.");
                return;
            }
            game.EndTurn();
            return;
        }
        if(turnPlayer->get_hero()->get_name() == CharacterType :: Dracula){
            int space = gamePage.SpaceAt(mouse);
            int dSpace = game.get_Board()->find_space_of_hero(turnPlayer->get_hero());
            if(space >= 0 && space == dSpace){
                mode = Mode :: BloodHarvestPickTarget;
                return;
            }
        }
        return;
    }

    if(mode == Mode :: ManeuverPickFighter){
        int space = gamePage.SpaceAt(mouse);
        auto own = OwnFighterSpaces(turnPlayer);
        if(space >= 0 && std :: find(own.begin(), own.end(), space) != own.end()){
            selectedFighterSpace = space;
            auto &spaces = game.get_Board()->get_spaces();
            Heroes *h = spaces[space].get_Hero();
            Sidekick *s = spaces[space].get_comrade();
            CharacterType t = h ? h->get_name() : s->get_name();
            int moveLimit = h ? h->get_Movement() : s->get_Movement();

            if(t == CharacterType :: Invman){
                Player *opp = game.get_opponent(turnPlayer);
                std :: vector<CharacterType> enemyTypes;
                enemyTypes.push_back(opp->get_hero()->get_name());
                for(auto *sk : opp->get_hero()->get_sidekick())
                    if(sk && sk->get_islive() && sk->occupies_space()) enemyTypes.push_back(sk->get_name());
                maneuverReachable = game.get_Board()->reachable_spaces_with_fog_jump(space, enemyTypes, true, moveLimit);
            } else {
                maneuverReachable = game.get_Board()->reachable_spaces(space, t, true, moveLimit);
            }
            mode = Mode :: ManeuverPickDestination;
        } else {
            mode = Mode :: Idle;
        }
        return;
    }

    if(mode == Mode :: ManeuverPickDestination){
        int space = gamePage.SpaceAt(mouse);
        if(space >= 0 && std :: find(maneuverReachable.begin(), maneuverReachable.end(), space) != maneuverReachable.end()){
            std :: string err;
            if(!game.MoveFighter(turnPlayer, selectedFighterSpace, space, err)) ShowToast(err);
        }
        mode = Mode :: Idle;
        selectedFighterSpace = -1;
        maneuverReachable.clear();
        return;
    }

    if(mode == Mode :: AttackPickAttacker){
        int space = gamePage.SpaceAt(mouse);
        auto own = OwnFighterSpaces(turnPlayer);
        if(space >= 0 && std :: find(own.begin(), own.end(), space) != own.end()){
            selectedFighterSpace = space;
            mode = Mode :: AttackPickTarget;
        } else {
            mode = Mode :: Idle;
        }
        return;
    }

    if(mode == Mode :: AttackPickTarget){
        int space = gamePage.SpaceAt(mouse);
        auto enemies = EnemyFighterSpaces(turnPlayer);
        if(space >= 0 && std :: find(enemies.begin(), enemies.end(), space) != enemies.end()){
            std :: string err;
            if(!game.DeclareAttack(turnPlayer, selectedFighterSpace, space, err)){
                ShowToast(err);
            } else {
                combatAttackerPlayer = turnPlayer;
                combatDefenderPlayer = game.get_opponent(turnPlayer);
                combatAttackerSpaceRef = selectedFighterSpace;
                combatDefenderSpaceRef = space;
            }
        }
        mode = Mode :: Idle;
        selectedFighterSpace = -1;
        return;
    }

    if(mode == Mode :: BloodHarvestPickTarget){
        int space = gamePage.SpaceAt(mouse);
        if(space >= 0){
            std :: string err;
            if(!game.BloodHarvest(turnPlayer, space, err)) ShowToast(err);
        }
        mode = Mode :: Idle;
        return;
    }
}

void Front :: HandleCombatClicks(CombatStage stage){
    if(showingCombatResult){
        if(combatPage.choosePressed){
            showingCombatResult = false;
            combatPage.showingResult = false;
            combatAttackerPlayer = nullptr;
            combatDefenderPlayer = nullptr;
            combatAttackerSpaceRef = combatDefenderSpaceRef = -1;
        }
        return;
    }

    if(stage == CombatStage :: AwaitAttackCard){
        if(combatPage.attackCardClicked != -1){
            std :: string err;
            if(!game.PlayAttackCard(combatPage.attackCardClicked, err)) ShowToast(err);
        }
    }
    else if(stage == CombatStage :: AwaitDefenseCard){
        if(combatPage.defenceCardClicked != -1){
            std :: string err;
            if(!game.PlayDefenseCard(combatPage.defenceCardClicked, err)) ShowToast(err);
            else if(game.get_CombatStage() == CombatStage :: Ready) BeginCombatFollowupFlow();
        }
        else if(combatPage.skipPressed){
            game.SkipDefense();
            if(game.get_CombatStage() == CombatStage :: Ready) BeginCombatFollowupFlow();
        }
    }
    else if(stage == CombatStage :: Ready){

        if(combatPage.choosePressed && mode != Mode :: Flow)
            BeginCombatFollowupFlow();
    }
}

void Front :: UpdateHandOverflow(){
    Player *turnPlayer = game.get_turn();
    if(turnPlayer->get_hand_cards().size() <= 7){
        mode = Mode :: Idle;
        return;
    }

    int discardIndex = -1;
    gamePage.Update(discardIndex);
    if(discardIndex >= 0 && discardIndex < (int)turnPlayer->get_hand_cards().size()){
        gamePage.GetCardViewWindow()->Close();
        std :: string err;
        game.DiscardExcess(turnPlayer, discardIndex, err);
        if(turnPlayer->get_hand_cards().size() <= 7){
            game.EndTurn();
            mode = Mode :: Idle;
        }
    }
}

void Front :: UpdateAndDrawGame(){
    Player *turnPlayer = game.get_turn();
    Player *p1 = game.get_player(1);
    Player *p2 = game.get_player(2);

    HeroPanelData leftHero  = BuildHeroPanel(p1);
    HeroPanelData rightHero = BuildHeroPanel(p2);

    PopulateHand(gamePage.handMenu, *turnPlayer);
    PopulateDeckAndDiscard();

    std :: string turnLabel = BuildTurnLabel();
    CombatStage stage = game.get_CombatStage();
    bool inCombatUI = (stage != CombatStage :: None) || showingCombatResult;

    CardViewWindow *cardView = gamePage.GetCardViewWindow();
    DeckCardWindow *deckWin  = gamePage.GetDeckCardWindow();
    bool windowsOpen = cardView->IsOpen() || deckWin->IsOpen();

    if(inCombatUI){
        combatPage.stage = stage;
        combatPage.showingResult = showingCombatResult;

        if(combatAttackerPlayer && combatDefenderPlayer){
            auto &spaces = game.get_Board()->get_spaces();
            auto nameAt = [&](int space) -> std :: string{
                if(space < 0 || space >= (int)spaces.size()) return "";
                if(Heroes *h = spaces[space].get_Hero()) return CharacterDisplayName(h->get_name());
                if(Sidekick *s = spaces[space].get_comrade()) return CharacterDisplayName(s->get_name());
                return "";
            };
            combatPage.attackerLabel = nameAt(combatAttackerSpaceRef) + " attacks";
            combatPage.defenderLabel = nameAt(combatDefenderSpaceRef) + " defends";
        }

        if(!showingCombatResult){
            if(stage == CombatStage :: AwaitAttackCard && combatAttackerPlayer)
                PopulateHand(combatPage.attackHand, *combatAttackerPlayer);
            if(stage == CombatStage :: AwaitDefenseCard && combatDefenderPlayer)
                PopulateHand(combatPage.defenceHand, *combatDefenderPlayer);
        }
    }

    int handCardClicked = -1;

    if(windowsOpen){
        cardView->Update();
        deckWin->Update();
    }
    else if(mode != Mode :: Flow && mode != Mode :: HandOverflow){
        if(!inCombatUI) gamePage.Update(handCardClicked);
        else            combatPage.Update();
    }

    EnsureSceneTexture();
    BeginTextureMode(sceneTexture);
        gamePage.Draw(background, titleFont, labelFont, mapTexture, leftHero, rightHero,
                       turnLabel.c_str(), turnPlayer->get_aciton());
        gamePage.DrawBoardPieces(BuildBoardPieces());
        if(inCombatUI)
            combatPage.Draw();
    EndTextureMode();

    DrawTexturePro(sceneTexture.texture,
        Rectangle{ 0, 0, (float)sceneTexture.texture.width, -(float)sceneTexture.texture.height },
        Rectangle{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
        Vector2{ 0, 0 }, 0.0f, WHITE);

    if(!inCombatUI){
        if(mode == Mode :: ManeuverPickFighter || mode == Mode :: AttackPickAttacker){
            gamePage.HighlightSpaces(OwnFighterSpaces(turnPlayer), GOLD);
        }
        else if(mode == Mode :: ManeuverPickDestination){
            gamePage.HighlightSpaces(maneuverReachable, GREEN);
        }
        else if(mode == Mode :: AttackPickTarget){
            gamePage.HighlightSpaces(EnemyFighterSpaces(turnPlayer), RED);
        }
        else if(mode == Mode :: BloodHarvestPickTarget){
            std :: vector<int> targets;
            int dSpace = game.get_Board()->find_space_of_hero(turnPlayer->get_hero());
            auto &spaces = game.get_Board()->get_spaces();
            for(size_t i = 0; i < spaces.size(); ++i){
                if((int)i == dSpace) continue;
                if(!game.get_Board()->AdjacentSpaces(dSpace, (int)i)) continue;
                if(spaces[i].get_Hero() || spaces[i].get_comrade()) targets.push_back((int)i);
            }
            gamePage.HighlightSpaces(targets, GOLD);
        }
        else if(mode == Mode :: Idle && turnPlayer->get_hero()->get_name() == CharacterType :: Dracula){
            DrawTextEx(labelFont, "Tip: click Dracula on the map to use Blood Harvest",
                       { 20, (float)GetScreenHeight() - 30 }, 16, 1.0f, Fade(RAYWHITE, 0.7f));
        }
    }

    if(mode == Mode :: Flow){
        HandleFlowStep();
    }
    else if(mode == Mode :: HandOverflow){
        DrawFlowPrompt("Discard down to 7 cards: click a card in your hand");
        UpdateHandOverflow();
    }
    else if(!windowsOpen){
        if(inCombatUI){
            HandleCombatClicks(stage);
        }
        else if(handCardClicked != -1){
            if(mode == Mode :: SchemePickCard){
                Card &c = turnPlayer->get_hand_cards()[handCardClicked];
                if(c.get_CardType() != CardType :: EVENT){
                    ShowToast("That is not a Scheme card.");
                } else {
                    cardView->Close();
                    BeginSchemeFlow(handCardClicked, c.get_CardName());
                }
            }

        }
        else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            HandleIdleClicks();
        }
    }

    DrawToast();

    if(cardView->IsOpen()) cardView->Draw(sceneTexture);
    if(deckWin->IsOpen())  deckWin->Draw(sceneTexture);
}
