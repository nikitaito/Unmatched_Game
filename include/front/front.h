#ifndef FRONT_H
#define FRONT_H

#include "raylib.h"
#include "Enums.h"
#include "game/game.h"
#include "front/main_menu.h"
#include "front/age_page.h"
#include "front/choose.h"
#include "front/game_page.h"
#include "front/combat_page.h"

#include <string>
#include <vector>
#include <unordered_map>

class Front
{
    public:
        Front();
        ~Front();

        void Run();

    private:

        Texture2D background{};
        Texture2D mapTexture{};

        Texture2D draculaPortrait{}, invManPortrait{}, holmesPortrait{};

        Texture2D invManGamePortrait{};

        Texture2D sister1Token{}, sister2Token{}, sister3Token{};
        Texture2D fogToken{};
        Texture2D watsonToken{};

        Texture2D combatBackground{};
        Texture2D swordIcon{};

        Font titleFont{}, subtitleFont{}, buttonFont{}, labelFont{};

        std::unordered_map<std::string, Texture2D> cardArt;
        Texture2D CardTextureFor(CardName name, CharacterType owner);

        void LoadAssets();
        void UnloadAssets();
        Color HeroColorFor(CharacterType t);

        Page currentPage = Page::Menu;
        Page priorPage   = Page::Menu;

        Main_Menu  menuPage;
        AgePage    agePage;
        ChoosePage choosePage;
        GamePage   gamePage;
        CombatPage combatPage;

        int age1 = 0, age2 = 0;
        CharacterType character1{}, character2{};

        Game game;
        bool gameStarted = false;
        void StartMatch();

        std::string toastMessage;
        float toastTimer = 0.0f;
        void ShowToast(const std::string &msg);
        void DrawToast();

        enum class Mode {
            Idle,
            ManeuverPickFighter,
            ManeuverPickDestination,
            AttackPickAttacker,
            AttackPickTarget,
            BloodHarvestPickTarget,
            SchemePickCard,
            Flow,
            HandOverflow,
            PostCombatCodedNotes,
            PlaceVanishedHero,
            GameOver
        };
        Mode mode = Mode::Idle;

        int selectedFighterSpace = -1;
        std::vector<int> maneuverReachable;

        enum class InputStep {
            CurrentSpace, TargetSpace,
            FogSpace, FogDest,
            SecondFogSpace, SecondFogDest,
            MoveDestination, SelfMoveDestination,
            OpponentCard, BoostDiscard, Prediction
        };
        enum class FlowKind { None, Scheme, CombatFollowup };

        FlowKind  flowKind = FlowKind::None;
        std::vector<InputStep> flowSteps;
        size_t    flowStepIndex = 0;

        int  flowHandIndex = -1;
        CardName flowCardName{};
        CardName flowAttackCardName{}, flowDefenseCardName{};
        bool flowHasDefenseCard = false;
        int  flowCurrent = -1, flowTarget = -1;
        int  flowFogSpace = -1, flowFogDest = -1;
        int  flowSecondFogSpace = -1, flowSecondFogDest = -1;
        int  flowMoveDestination = -1, flowSelfMoveDestination = -1;
        std::vector<int> flowBoostIndices;
        int  flowGuessValue = 0;
        bool flowGuessAttack = true;
        bool flowAllowDeclineOnOpponentCard = false;

        void BeginSchemeFlow(int handIndex, CardName name);
        void BeginCombatFollowupFlow();
        void AdvanceFlow();
        void CancelFlow();
        void FinishFlow();
        std::vector<InputStep> StepsForScheme(CardName name) const;
        std::vector<InputStep> StepsForCombat(CardName atk, bool hasDef, CardName def) const;

        Player *combatAttackerPlayer = nullptr;
        Player *combatDefenderPlayer = nullptr;
        int combatAttackerSpaceRef = -1, combatDefenderSpaceRef = -1;
        bool showingCombatResult = false;

        Player *pendingCodedNotesPlayer = nullptr;
        int pendingCodedNotesDrawn = -1;
        std::vector<int> codedNotesPicks;
        void BeginCodedNotesChoice();
        void HandlePostCombatCodedNotes();
        void HandlePlaceVanishedHero();

        void UpdateAndDrawGame();
        RenderTexture2D sceneTexture{};
        int sceneTexW = 0, sceneTexH = 0;
        void EnsureSceneTexture();
        void HandleIdleClicks();
        void HandleFlowStep();
        void DrawFlowPrompt(const char *question);
        void DrawPredictionPicker();
        void HandleCombatClicks(CombatStage stage);
        void UpdateHandOverflow();

        HeroPanelData BuildHeroPanel(Player *p);
        void PopulateHand(CPHandMenu &menu, Player &p);
        void PopulateDeckAndDiscard();
        std::string BuildTurnLabel();

        std::vector<int> OwnFighterSpaces(Player *p);
        std::vector<int> EnemyFighterSpaces(Player *p);
        Texture2D PortraitFor(CharacterType t);
        Texture2D GamePortraitFor(CharacterType t);
        std::vector<BoardPieceVisual> BuildBoardPieces();

        int predictionDraftValue = 0;
        bool predictionDraftAttack = true;
};

#endif
