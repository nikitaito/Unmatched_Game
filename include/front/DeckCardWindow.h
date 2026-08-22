#pragma once
#include "raylib.h"
#include <functional>
#include <string>
#include <vector>

class DeckCardWindow
{
    private:
        bool isOpen = false;
        std::vector<Texture2D> cardTextures;
        std::vector<std::string> cardLabels; // shown on cells with no texture (this project ships no card art)
        std::string windowTitle = "Deck Card";
        bool pickMode = false; // when true, a "Decline"/close-only affordance is drawn alongside picking

        Font customFont{};
        int  fontBaseSize;

        Shader blurShader{};
        bool   blurShaderLoaded = false;


        static constexpr int   COLUMNS       = 3;
        static constexpr int   VISIBLE_ROWS  = 3;
        static constexpr float CELL_WIDTH    = 140.0f;
        static constexpr float CELL_HEIGHT   = 196.0f; 
        static constexpr float CELL_GAP      = 20.0f;
        static constexpr float SCROLLBAR_W   = 30.0f;
        static constexpr float TITLE_HEIGHT  = 60.0f;
        static constexpr float PADDING       = 30.0f;

        Rectangle windowBounds{};
        Rectangle closeButtonBounds{};
        Rectangle gridArea{};         
        Rectangle scrollbarTrack{};
        Rectangle scrollUpButton{};
        Rectangle scrollDownButton{};
        Rectangle scrollThumb{};

        float scrollOffset   = 0.0f;   
        float maxScrollOffset = 0.0f;
        bool  draggingThumb  = false;
        float dragStartMouseY = 0.0f;
        float dragStartOffset = 0.0f;

        void CalculateLayout();
        void UpdateScrollBounds();
        void DrawDashedRectangle(Rectangle rect, float dashLen, float gapLen, float thickness, Color color) const;
        void DrawBlurredBackground(const RenderTexture2D& backgroundTexture) const;
        bool IsPointInCloseButton(Vector2 point) const;
        void UpdateScrollThumbRect();
    public:
        DeckCardWindow(const std::string& fontPath, int fontBaseSize = 32);
        ~DeckCardWindow();


        void Open(const std::vector<Texture2D>& cards);
        // labels.size() should equal cards.size() (or be empty to skip labels);
        // 'title' overrides the "Deck Card" heading (e.g. "Opponent's Hand");
        // 'pick' just changes the heading style to hint the grid is clickable.
        void Open(const std::vector<Texture2D>& cards, const std::vector<std::string>& labels, const std::string &title = "Deck Card", bool pick = false);
        void Close();

        bool IsOpen() const { return isOpen; }

        void Update();
        void Draw(const RenderTexture2D& backgroundTexture);


        std::function<void()> onClose;
        std::function<void(size_t index)> onCardClicked;
};
