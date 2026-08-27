#ifndef GAME_PAGE
#define GAME_PAGE

#include "raylib.h"
#include "handmenu.h"
#include "CardViewWindow.h"
#include "DeckCardWindow.h"
#include <vector>
#include <string>
#include <memory>

constexpr float GP_TOKEN_SRC_W       = 638.0f;  
constexpr float GP_TOKEN_SRC_H       = 400.0f;
constexpr int   GP_SPACE_COUNT       = 32;     
constexpr float GP_SPACE_RADIUS_NORM = 0.055f; 


struct SidekickVisual { Texture2D texture; int currentHP; int maxHP; bool showLife; };

struct HeroPanelData {
    Texture2D portrait;
    const char* name;
    int currentHP;
    int maxHP;
    std::vector<SidekickVisual> sidekicks;
};
struct BoardPieceVisual {
    int space = -1;
    bool isHeroDot = false;   
    bool isFogToken = false;  
    Color color = WHITE;
    Texture2D texture{};
    float scale = 1.0f;       
};

class GamePage {
    private:
        Rectangle DrawMap(Rectangle area, Texture2D mapTexture);
        Rectangle DrawHeroPanel(Rectangle area, const HeroPanelData &data, Font nameFont, Font labelFont, bool mirrored, Rectangle &outDeckBtn, Rectangle &outDiscardBtn);
        Rectangle DrawSidekickRow(Rectangle area, const std::vector<SidekickVisual> &sidekicks, Font labelFont);
        void DrawLifeBadge(Vector2 center, int currentHP, float radius);
        Rectangle DrawActionBar(Rectangle area, Font labelFont, int actionsRemaining, Rectangle &outEndTurnBtn, Rectangle &outSaveBtn);
        void DrawManeuverAttackScheme(Rectangle area, Font labelFont, Rectangle &outManeuver, Rectangle &outAttack, Rectangle &outScheme);

        Rectangle lastMapRect{};    
        Rectangle leftDeckBtn{}, leftDiscardBtn{}, rightDeckBtn{}, rightDiscardBtn{};
        Rectangle maneuverBtn{}, attackBtn{}, schemeBtn{}, endTurnBtn{};
        Rectangle saveBtn{};

        std::unique_ptr<CardViewWindow> cardViewWindow; 
        std::unique_ptr<DeckCardWindow> deckWindow;     

    public:
        CPHandMenu handMenu;

        std::vector<Texture2D> leftDeckCards, leftDiscardCards, rightDeckCards, rightDiscardCards; 
        std::vector<std::string> leftDeckLabels, leftDiscardLabels, rightDeckLabels, rightDiscardLabels; 
        std::string leftDeckTitle = "Your Deck", leftDiscardTitle = "Your Discard";
        std::string rightDeckTitle = "Opponent's Deck", rightDiscardTitle = "Opponent's Discard";

        void Init(const std::string &fontPath = ""); 
        void Update(int &handCardClicked);
        void Draw(Texture2D background, Font titleFont, Font labelFont, Texture2D mapTexture, HeroPanelData &leftHero, HeroPanelData &rightHero, const char *turnLabel, int actionsRemaining); 

        void HighlightSpace(int spaceIndex); 
        void HighlightSpaces(const std::vector<int> &spaceIndices); 
        void HighlightSpaces(const std::vector<int> &spaceIndices, Color color); 

        void DrawBoardPieces(const std::vector<BoardPieceVisual> &pieces);
        int SpaceAt(Vector2 point) const;
        Rectangle GetMapRect() const { return lastMapRect; }


        Rectangle GetManeuverBtn() const { return maneuverBtn; }
        Rectangle GetAttackBtn() const { return attackBtn; }
        Rectangle GetSchemeBtn() const { return schemeBtn; }
        Rectangle GetEndTurnBtn() const { return endTurnBtn; }
        Rectangle GetSaveBtn() const { return saveBtn; }

        CardViewWindow* GetCardViewWindow() const { return cardViewWindow.get(); } 
        DeckCardWindow* GetDeckCardWindow() const { return deckWindow.get(); }
};

#endif