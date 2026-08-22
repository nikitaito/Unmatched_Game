#pragma once
#include "raylib.h"
#include <functional>
#include <string>


class CardViewWindow
{
    private:
        bool         isOpen = false;
        Texture2D    cardTexture{};
        bool         hasCardTexture = false;
        std::string  cardLabel;      // shown when there's no texture: the card's name
        std::string  cardStatLine;   // shown when there's no texture: printed values

        Font         customFont{};
        int          fontBaseSize;

        Shader       blurShader{};
        bool         blurShaderLoaded = false;

        Rectangle    windowBounds{};   
        Rectangle    cardBounds{};        
        Rectangle    closeButtonBounds{}; 

        static constexpr float CARD_WIDTH  = 250.0f;
        static constexpr float CARD_HEIGHT = 349.0f;

        void CalculateLayout();
        void DrawDashedRectangle(Rectangle rect, float dashLen, float gapLen, float thickness, Color color) const;
        void DrawBlurredBackground(const RenderTexture2D& backgroundTexture) const;
        bool IsPointInCloseButton(Vector2 point) const;
        
    public:

        CardViewWindow(const std::string& fontPath, int fontBaseSize = 32);
        ~CardViewWindow();


        void Open(Texture2D cardTexture);
        void Open(Texture2D cardTexture, const std::string &label, const std::string &statLine = "");
        void Close();

        bool IsOpen() const { return isOpen; }

        void Update();
        void Draw(const RenderTexture2D& backgroundTexture);
        std::function<void()> onClose;


};
