#include "CardViewWindow.h"
#include "raymath.h"

struct CardWindowTheme
{
    inline static const Color Overlay        = { 0, 0, 0, 140 };      
    inline static const Color WindowBg       = { 28, 24, 22, 235 };   
    inline static const Color WindowBorder   = { 198, 156, 84, 255 }; 
    inline static const Color CardFrame      = { 236, 224, 200, 255 };
    inline static const Color TitleText      = { 230, 214, 180, 255 };
    inline static const Color CloseBtnBg     = { 60, 48, 40, 255 };
    inline static const Color CloseBtnBgHov  = { 120, 40, 40, 255 };
    inline static const Color CloseBtnBorder = { 160, 50, 45, 255 };
    inline static const Color CloseBtnText   = { 230, 80, 70, 255 };
};

CardViewWindow::CardViewWindow(const std::string& fontPath, int fontBaseSize_): fontBaseSize(fontBaseSize_){
    customFont = LoadFontEx(fontPath.c_str(), fontBaseSize, nullptr, 0);
    if (customFont.texture.id == 0)
    {
        customFont = GetFontDefault();
    }
    else
    {
        SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);
    }
    blurShader = LoadShader(0, "../assets/shaders/blur.fs");
    blurShaderLoaded = (blurShader.id != 0);
}

CardViewWindow::~CardViewWindow(){
    if (customFont.texture.id != GetFontDefault().texture.id)
        UnloadFont(customFont);

    if (blurShaderLoaded)
        UnloadShader(blurShader);
}

void CardViewWindow::Open(Texture2D card){
    cardTexture = card;
    hasCardTexture = true;
    cardLabel.clear();
    cardStatLine.clear();
    isOpen = true;
    CalculateLayout();
}

void CardViewWindow::Open(Texture2D card, const std::string &label, const std::string &statLine){
    cardTexture = card;
    hasCardTexture = (card.id != 0);
    cardLabel = label;
    cardStatLine = statLine;
    isOpen = true;
    CalculateLayout();
}

void CardViewWindow::Close(){
    isOpen = false;
    if (onClose) onClose();
}

void CardViewWindow::CalculateLayout(){
    const float screenW = (float)GetScreenWidth();
    const float screenH = (float)GetScreenHeight();

    const float paddingX   = 70.0f;
    const float paddingTop = 90.0f;   
    const float paddingBottom = 60.0f;

    const float windowW = CARD_WIDTH + paddingX * 2.0f;
    const float windowH = CARD_HEIGHT + paddingTop + paddingBottom;

    windowBounds = {
        (screenW - windowW) / 2.0f,
        (screenH - windowH) / 2.0f,
        windowW,
        windowH
    };

    cardBounds = {
        windowBounds.x + paddingX,
        windowBounds.y + paddingTop,
        CARD_WIDTH,
        CARD_HEIGHT
    };

    const float btnSize = 36.0f;
    const float btnMargin = 16.0f;
    closeButtonBounds = {
        windowBounds.x + windowBounds.width - btnSize - btnMargin,
        windowBounds.y + btnMargin,
        btnSize,
        btnSize
    };
}

bool CardViewWindow::IsPointInCloseButton(Vector2 point) const{
    return CheckCollisionPointRec(point, closeButtonBounds);
}

void CardViewWindow::Update(){
    if (!isOpen) return;

    CalculateLayout();

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (IsPointInCloseButton(mouse))
        {
            Close();
            return;
        }
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        Close();
    }
}

void CardViewWindow::DrawDashedRectangle(Rectangle rect, float dashLen, float gapLen,float thickness, Color color) const{
    float step = dashLen + gapLen;

    for (float x = rect.x; x < rect.x + rect.width; x += step)
    {
        float segEnd = fminf(x + dashLen, rect.x + rect.width);
        DrawLineEx({ x, rect.y }, { segEnd, rect.y }, thickness, color);
        DrawLineEx({ x, rect.y + rect.height }, { segEnd, rect.y + rect.height }, thickness, color);
    }
    for (float y = rect.y; y < rect.y + rect.height; y += step)
    {
        float segEnd = fminf(y + dashLen, rect.y + rect.height);
        DrawLineEx({ rect.x, y }, { rect.x, segEnd }, thickness, color);
        DrawLineEx({ rect.x + rect.width, y }, { rect.x + rect.width, segEnd }, thickness, color);
    }
}

void CardViewWindow::DrawBlurredBackground(const RenderTexture2D& backgroundTexture) const{
    const int screenW = GetScreenWidth();
    const int screenH = GetScreenHeight();

    if (blurShaderLoaded)
    {
        BeginShaderMode(blurShader);
        DrawTextureRec(
            backgroundTexture.texture,
            { 0, 0, (float)backgroundTexture.texture.width, -(float)backgroundTexture.texture.height },
            { 0, 0 },
            WHITE
        );
        EndShaderMode();
    }
    else
    {
        DrawTextureRec(
            backgroundTexture.texture,
            { 0, 0, (float)backgroundTexture.texture.width, -(float)backgroundTexture.texture.height },
            { 0, 0 },
            WHITE
        );
    }

    // dark overlay: improves window contrast and blocks clicks on the page behind it
    DrawRectangle(0, 0, screenW, screenH, CardWindowTheme::Overlay);
}

void CardViewWindow::Draw(const RenderTexture2D& backgroundTexture){
    if (!isOpen) return;

    DrawBlurredBackground(backgroundTexture);


    DrawRectangleRounded(windowBounds, 0.04f, 8, CardWindowTheme::WindowBg);
    DrawDashedRectangle(windowBounds, 10.0f, 6.0f, 2.0f, CardWindowTheme::WindowBorder);


    Rectangle frameRect = {
        cardBounds.x - 6, cardBounds.y - 6,
        cardBounds.width + 12, cardBounds.height + 12
    };
    DrawRectangleRec(frameRect, CardWindowTheme::CardFrame);

    if (hasCardTexture)
    {
        DrawTexturePro(
            cardTexture,
            { 0, 0, (float)cardTexture.width, (float)cardTexture.height },
            cardBounds,
            { 0, 0 }, 0.0f, WHITE
        );
    }
    else
    {
        DrawRectangleRec(cardBounds, DARKGRAY);

        // no card art shipped with this project: draw the name + stat line
        // centered inside the card silhouette instead of a picture
        float pad = cardBounds.width * 0.08f;
        Rectangle textArea{ cardBounds.x + pad, cardBounds.y + pad, cardBounds.width - pad * 2, cardBounds.height - pad * 2 };
        float nameFontSize = cardBounds.width * 0.11f;

        std::string remaining = cardLabel;
        float lineY = textArea.y + textArea.height * 0.35f;
        while(!remaining.empty()){
            size_t fit = remaining.size();
            while(fit > 0 && MeasureTextEx(customFont, remaining.substr(0, fit).c_str(), nameFontSize, 1.0f).x > textArea.width)
                fit--;
            if(fit < remaining.size()){
                size_t breakAt = remaining.rfind(' ', fit);
                if(breakAt != std::string::npos && breakAt > 0)
                    fit = breakAt;
            }
            std::string line = remaining.substr(0, fit);
            Vector2 lineSize = MeasureTextEx(customFont, line.c_str(), nameFontSize, 1.0f);
            DrawTextEx(customFont, line.c_str(), { textArea.x + textArea.width / 2 - lineSize.x / 2, lineY }, nameFontSize, 1.0f, RAYWHITE);
            lineY += nameFontSize * 1.2f;
            remaining = (fit < remaining.size()) ? remaining.substr(remaining[fit] == ' ' ? fit + 1 : fit) : "";
        }

        if(!cardStatLine.empty()){
            float statFontSize = cardBounds.width * 0.08f;
            Vector2 statSize = MeasureTextEx(customFont, cardStatLine.c_str(), statFontSize, 1.0f);
            DrawTextEx(customFont, cardStatLine.c_str(), { textArea.x + textArea.width / 2 - statSize.x / 2, lineY + 10.0f }, statFontSize, 1.0f, Color{ 225, 220, 210, 255 });
        }
    }

    DrawRectangleLinesEx(cardBounds, 2.0f, CardWindowTheme::WindowBorder);

    const char* title = cardLabel.empty() ? "Card" : cardLabel.c_str();
    float fSize = (float)fontBaseSize * 0.6f;
    Vector2 textSize = MeasureTextEx(customFont, title, fSize, 1.0f);
    Vector2 textPos = {
        cardBounds.x + (cardBounds.width - textSize.x) / 2.0f,
        cardBounds.y + cardBounds.height + 14.0f
    };
    DrawTextEx(customFont, title, textPos, fSize, 1.0f, CardWindowTheme::TitleText);

    Vector2 mouse = GetMousePosition();
    bool hovered = IsPointInCloseButton(mouse);

    DrawRectangleRounded(closeButtonBounds, 0.25f, 6,hovered ? CardWindowTheme::CloseBtnBgHov : CardWindowTheme::CloseBtnBg);
    DrawRectangleRoundedLinesEx(closeButtonBounds, 0.25f, 6, 1.5f, CardWindowTheme::CloseBtnBorder);

    const char* xLabel = "X";
    float xFSize = (float)fontBaseSize * 0.55f;
    Vector2 xSize = MeasureTextEx(customFont, xLabel, xFSize, 1.0f);
    Vector2 xPos = {
        closeButtonBounds.x + (closeButtonBounds.width - xSize.x) / 2.0f,
        closeButtonBounds.y + (closeButtonBounds.height - xSize.y) / 2.0f
    };
    DrawTextEx(customFont, xLabel, xPos, xFSize, 1.0f, CardWindowTheme::CloseBtnText);
}
