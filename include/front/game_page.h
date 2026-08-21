#ifndef GAME_PAGE
#define GAME_PAGE

#include "raylib.h"
#include "handmenu.h"
#include "CardViewWindow.h"
#include "DeckCardWindow.h"
#include <vector>
#include <string>
#include <memory>

constexpr float GP_TOKEN_SRC_W       = 638.0f;  // sidekick token art source size
constexpr float GP_TOKEN_SRC_H       = 400.0f;
constexpr int   GP_SPACE_COUNT       = 32;      // numbered spaces on the board art
constexpr float GP_SPACE_RADIUS_NORM = 0.055f;  // highlight ring radius, as a fraction of map width

// one sidekick/token's visuals, filled by the caller each frame
struct SidekickVisual { Texture2D texture; int currentHP; int maxHP; bool showLife; };

// one hero's panel data, filled by the caller each frame from live game state
struct HeroPanelData {
    Texture2D portrait;
    const char* name;
    int currentHP;
    int maxHP;
    std::vector<SidekickVisual> sidekicks;
};

class GamePage {
    private:
        Rectangle DrawMap(Rectangle area, Texture2D mapTexture);
        Rectangle DrawHeroPanel(Rectangle area, const HeroPanelData &data, Font nameFont, Font labelFont, bool mirrored, Rectangle &outDeckBtn, Rectangle &outDiscardBtn);
        Rectangle DrawSidekickRow(Rectangle area, const std::vector<SidekickVisual> &sidekicks, Font labelFont);
        void DrawLifeBadge(Vector2 center, int currentHP, float radius);
        Rectangle DrawActionBar(Rectangle area, Font labelFont, int actionsRemaining, Rectangle &outEndTurnBtn);
        void DrawManeuverAttackScheme(Rectangle area, Font labelFont, Rectangle &outManeuver, Rectangle &outAttack, Rectangle &outScheme);

        Rectangle lastMapRect{};    // map's on-screen rect from last Draw(), used by HighlightSpace
        Rectangle leftDeckBtn{}, leftDiscardBtn{}, rightDeckBtn{}, rightDiscardBtn{}; // button rects from last Draw(), read back in Update()
        Rectangle maneuverBtn{}, attackBtn{}, schemeBtn{}, endTurnBtn{};

        std::unique_ptr<CardViewWindow> cardViewWindow; // shows one hand card full-size
        std::unique_ptr<DeckCardWindow> deckWindow;      // shows a deck/discard pile grid

    public:
        CPHandMenu handMenu;

        std::vector<Texture2D> leftDeckCards, leftDiscardCards, rightDeckCards, rightDiscardCards; // fill before calling Update()/Draw()

        void Init(const std::string &fontPath = ""); // builds CardViewWindow/DeckCardWindow, call once before Update()/Draw()
        void Update(int &handCardClicked); // handles hand-card clicks and deck/discard button clicks
        void Draw(Texture2D background, Font titleFont, Font labelFont, Texture2D mapTexture, HeroPanelData &leftHero, HeroPanelData &rightHero, const char *turnLabel, int actionsRemaining); // draws one frame

        void HighlightSpace(int spaceIndex); // ring around one board space; call after Draw()
        void HighlightSpaces(const std::vector<int> &spaceIndices); // ring around several spaces

        CardViewWindow* GetCardViewWindow() const { return cardViewWindow.get(); } // draw after rendering the scene to a texture
        DeckCardWindow* GetDeckCardWindow() const { return deckWindow.get(); }
};

#endif