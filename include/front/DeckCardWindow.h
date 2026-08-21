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
        void Close();

        bool IsOpen() const { return isOpen; }

        void Update();
        void Draw(const RenderTexture2D& backgroundTexture);


        std::function<void()> onClose;
        std::function<void(size_t index)> onCardClicked;
};
