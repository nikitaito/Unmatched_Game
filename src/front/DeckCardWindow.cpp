#include "DeckCardWindow.h"
#include "raymath.h"
#include <algorithm>
#include <cmath>

namespace DeckWindowTheme
{
    static const Color Overlay        = { 0, 0, 0, 140 };
    static const Color WindowBg       = { 28, 24, 22, 235 };
    static const Color WindowBorder   = { 198, 156, 84, 255 };
    static const Color CardFrame      = { 236, 224, 200, 255 };
    static const Color TitleText      = { 230, 214, 180, 255 };
    static const Color CloseBtnBg     = { 60, 48, 40, 255 };
    static const Color CloseBtnBgHov  = { 120, 40, 40, 255 };
    static const Color CloseBtnBorder = { 198, 156, 84, 255 };
    static const Color CloseBtnText   = { 236, 224, 200, 255 };
    static const Color ScrollTrackBg  = { 45, 38, 34, 255 };
    static const Color ScrollThumb    = { 198, 156, 84, 255 };
    static const Color ScrollThumbHov = { 220, 182, 110, 255 };
    static const Color ArrowBtnBg     = { 60, 48, 40, 255 };
    static const Color ArrowBtnBgHov  = { 90, 72, 56, 255 };
}

DeckCardWindow::DeckCardWindow(const std::string& fontPath, int fontBaseSize_)
    : fontBaseSize(fontBaseSize_)
{
    customFont = LoadFontEx(fontPath.c_str(), fontBaseSize, nullptr, 0);
    if (customFont.texture.id == 0)
    {
        customFont = GetFontDefault();
    }
    else
    {
        SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);
    }

    blurShader = LoadShader(0, "assets/src/blur.fs");
    blurShaderLoaded = (blurShader.id != 0);
}

DeckCardWindow::~DeckCardWindow()
{
    if (customFont.texture.id != GetFontDefault().texture.id)
        UnloadFont(customFont);

    if (blurShaderLoaded)
        UnloadShader(blurShader);
}

void DeckCardWindow::Open(const std::vector<Texture2D>& cards)
{
    cardTextures = cards;
    isOpen = true;
    scrollOffset = 0.0f;
    CalculateLayout();
}

void DeckCardWindow::Close()
{
    isOpen = false;
    if (onClose) onClose();
}

void DeckCardWindow::CalculateLayout()
{
    const float screenW = (float)GetScreenWidth();
    const float screenH = (float)GetScreenHeight();

    const float gridW = COLUMNS * CELL_WIDTH + (COLUMNS - 1) * CELL_GAP;
    const float gridVisibleH = VISIBLE_ROWS * CELL_HEIGHT + (VISIBLE_ROWS - 1) * CELL_GAP;

    const float windowW = PADDING * 2 + SCROLLBAR_W + CELL_GAP + gridW;
    const float windowH = TITLE_HEIGHT + gridVisibleH + PADDING * 2;

    windowBounds = {
        (screenW - windowW) / 2.0f,
        (screenH - windowH) / 2.0f,
        windowW,
        windowH
    };

    const float btnSize = 36.0f;
    const float btnMargin = 16.0f;
    closeButtonBounds = {
        windowBounds.x + windowBounds.width - btnSize - btnMargin,
        windowBounds.y + btnMargin,
        btnSize,
        btnSize
    };

    gridArea = {
        windowBounds.x + PADDING + SCROLLBAR_W + CELL_GAP,
        windowBounds.y + TITLE_HEIGHT,
        gridW,
        gridVisibleH
    };

    // scrollbar sits on the left side of the grid
    const float arrowBtnSize = SCROLLBAR_W;
    scrollUpButton = { windowBounds.x + PADDING, gridArea.y, arrowBtnSize, arrowBtnSize };
    scrollDownButton = { windowBounds.x + PADDING, gridArea.y + gridArea.height - arrowBtnSize,
                          arrowBtnSize, arrowBtnSize };
    scrollbarTrack = {
        windowBounds.x + PADDING,
        scrollUpButton.y + arrowBtnSize + 4.0f,
        arrowBtnSize,
        gridArea.height - (arrowBtnSize + 4.0f) * 2.0f
    };

    UpdateScrollBounds();
    UpdateScrollThumbRect();
}

void DeckCardWindow::UpdateScrollBounds()
{
    int rows = (int)std::ceil((float)cardTextures.size() / (float)COLUMNS);
    if (rows < VISIBLE_ROWS) rows = VISIBLE_ROWS;

    float totalContentH = rows * CELL_HEIGHT + (rows - 1) * CELL_GAP;
    maxScrollOffset = std::max(0.0f, totalContentH - gridArea.height);
    scrollOffset = std::clamp(scrollOffset, 0.0f, maxScrollOffset);
}

void DeckCardWindow::UpdateScrollThumbRect()
{
    if (maxScrollOffset <= 0.0f)
    {
        scrollThumb = scrollbarTrack;
        return;
    }

    int rows = (int)std::ceil((float)cardTextures.size() / (float)COLUMNS);
    if (rows < VISIBLE_ROWS) rows = VISIBLE_ROWS;
    float totalContentH = rows * CELL_HEIGHT + (rows - 1) * CELL_GAP;

    float thumbRatio = gridArea.height / totalContentH;
    float thumbH = std::max(20.0f, scrollbarTrack.height * thumbRatio);

    float scrollRatio = scrollOffset / maxScrollOffset;
    float thumbY = scrollbarTrack.y + scrollRatio * (scrollbarTrack.height - thumbH);

    scrollThumb = { scrollbarTrack.x, thumbY, scrollbarTrack.width, thumbH };
}

bool DeckCardWindow::IsPointInCloseButton(Vector2 point) const
{
    return CheckCollisionPointRec(point, closeButtonBounds);
}

void DeckCardWindow::Update()
{
    if (!isOpen) return;

    CalculateLayout();

    Vector2 mouse = GetMousePosition();

    if (IsKeyPressed(KEY_ESCAPE))
    {
        Close();
        return;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (IsPointInCloseButton(mouse))
        {
            Close();
            return;
        }

        if (CheckCollisionPointRec(mouse, scrollUpButton))
        {
            scrollOffset -= CELL_HEIGHT * 0.5f;
        }
        else if (CheckCollisionPointRec(mouse, scrollDownButton))
        {
            scrollOffset += CELL_HEIGHT * 0.5f;
        }
        else if (CheckCollisionPointRec(mouse, scrollThumb))
        {
            draggingThumb = true;
            dragStartMouseY = mouse.y;
            dragStartOffset = scrollOffset;
        }
        else if (CheckCollisionPointRec(mouse, gridArea))
        {
            float localX = mouse.x - gridArea.x;
            float localY = (mouse.y - gridArea.y) + scrollOffset;

            int col = (int)(localX / (CELL_WIDTH + CELL_GAP));
            int row = (int)(localY / (CELL_HEIGHT + CELL_GAP));

            float cellLocalX = localX - col * (CELL_WIDTH + CELL_GAP);
            float cellLocalY = localY - row * (CELL_HEIGHT + CELL_GAP);

            if (col >= 0 && col < COLUMNS &&
                cellLocalX >= 0 && cellLocalX <= CELL_WIDTH &&
                cellLocalY >= 0 && cellLocalY <= CELL_HEIGHT)
            {
                size_t index = (size_t)(row * COLUMNS + col);
                if (index < cardTextures.size() && onCardClicked)
                {
                    onCardClicked(index);
                }
            }
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && draggingThumb)
    {
        float deltaY = mouse.y - dragStartMouseY;
        float trackRange = scrollbarTrack.height - scrollThumb.height;
        if (trackRange > 0.0f)
        {
            float scrollDelta = (deltaY / trackRange) * maxScrollOffset;
            scrollOffset = dragStartOffset + scrollDelta;
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        draggingThumb = false;
    }

    float wheel = GetMouseWheelMove();
    if (wheel != 0.0f &&
        (CheckCollisionPointRec(mouse, gridArea) || CheckCollisionPointRec(mouse, scrollbarTrack)))
    {
        scrollOffset -= wheel * CELL_HEIGHT * 0.6f;
    }

    scrollOffset = std::clamp(scrollOffset, 0.0f, maxScrollOffset);
    UpdateScrollThumbRect();
}

void DeckCardWindow::DrawDashedRectangle(Rectangle rect, float dashLen, float gapLen,float thickness, Color color) const{
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

void DeckCardWindow::DrawBlurredBackground(const RenderTexture2D& backgroundTexture) const{
    const int screenW = GetScreenWidth();
    const int screenH = GetScreenHeight();

    if (blurShaderLoaded) BeginShaderMode(blurShader);

    DrawTextureRec(
        backgroundTexture.texture,
        { 0, 0, (float)backgroundTexture.texture.width, -(float)backgroundTexture.texture.height },
        { 0, 0 },
        WHITE
    );

    if (blurShaderLoaded) EndShaderMode();

    DrawRectangle(0, 0, screenW, screenH, DeckWindowTheme::Overlay);
}

void DeckCardWindow::Draw(const RenderTexture2D& backgroundTexture)
{
    if (!isOpen) return;

    DrawBlurredBackground(backgroundTexture);
    DrawRectangleRounded(windowBounds, 0.03f, 8, DeckWindowTheme::WindowBg);
    DrawDashedRectangle(windowBounds, 10.0f, 6.0f, 2.0f, DeckWindowTheme::WindowBorder);

    const char* title = "Deck Card";
    float titleFSize = (float)fontBaseSize * 0.7f;
    Vector2 titleSize = MeasureTextEx(customFont, title, titleFSize, 1.0f);
    Vector2 titlePos = {
        windowBounds.x + (windowBounds.width - titleSize.x) / 2.0f,
        windowBounds.y + (TITLE_HEIGHT - titleSize.y) / 2.0f
    };
    DrawTextEx(customFont, title, titlePos, titleFSize, 1.0f, DeckWindowTheme::TitleText);

    BeginScissorMode((int)gridArea.x, (int)gridArea.y, (int)gridArea.width, (int)gridArea.height);

    int rows = (int)std::ceil((float)cardTextures.size() / (float)COLUMNS);
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < COLUMNS; col++)
        {
            size_t index = (size_t)(row * COLUMNS + col);
            if (index >= cardTextures.size()) continue;

            float cellX = gridArea.x + col * (CELL_WIDTH + CELL_GAP);
            float cellY = gridArea.y + row * (CELL_HEIGHT + CELL_GAP) - scrollOffset;

            if (cellY + CELL_HEIGHT < gridArea.y || cellY > gridArea.y + gridArea.height)
                continue;

            Rectangle cellRect = { cellX, cellY, CELL_WIDTH, CELL_HEIGHT };

            DrawRectangleRec(cellRect, DeckWindowTheme::CardFrame);

            Texture2D tex = cardTextures[index];
            if (tex.id != 0)
            {
                DrawTexturePro(
                    tex,
                    { 0, 0, (float)tex.width, (float)tex.height },
                    cellRect,
                    { 0, 0 }, 0.0f, WHITE
                );
            }

            DrawRectangleLinesEx(cellRect, 2.0f, DeckWindowTheme::WindowBorder);
        }
    }

    EndScissorMode();

    Vector2 mouse = GetMousePosition();

    DrawRectangleRounded(scrollUpButton, 0.2f, 4,
        CheckCollisionPointRec(mouse, scrollUpButton) ? DeckWindowTheme::ArrowBtnBgHov : DeckWindowTheme::ArrowBtnBg);
    DrawRectangleRounded(scrollDownButton, 0.2f, 4,
        CheckCollisionPointRec(mouse, scrollDownButton) ? DeckWindowTheme::ArrowBtnBgHov : DeckWindowTheme::ArrowBtnBg);

    float arrowFSize = (float)fontBaseSize * 0.5f;
    const char* upLabel = "^";
    const char* downLabel = "v";
    Vector2 upSize = MeasureTextEx(customFont, upLabel, arrowFSize, 1.0f);
    Vector2 downSize = MeasureTextEx(customFont, downLabel, arrowFSize, 1.0f);
    DrawTextEx(customFont, upLabel,
        { scrollUpButton.x + (scrollUpButton.width - upSize.x) / 2.0f,
          scrollUpButton.y + (scrollUpButton.height - upSize.y) / 2.0f },
        arrowFSize, 1.0f, DeckWindowTheme::CloseBtnText);
    DrawTextEx(customFont, downLabel,
        { scrollDownButton.x + (scrollDownButton.width - downSize.x) / 2.0f,
          scrollDownButton.y + (scrollDownButton.height - downSize.y) / 2.0f },
        arrowFSize, 1.0f, DeckWindowTheme::CloseBtnText);

    DrawRectangleRounded(scrollbarTrack, 0.3f, 4, DeckWindowTheme::ScrollTrackBg);
    DrawRectangleRounded(scrollThumb, 0.4f, 6,
        (draggingThumb || CheckCollisionPointRec(mouse, scrollThumb))
            ? DeckWindowTheme::ScrollThumbHov : DeckWindowTheme::ScrollThumb);

    bool hovered = IsPointInCloseButton(mouse);
    DrawRectangleRounded(closeButtonBounds, 0.25f, 6,
        hovered ? DeckWindowTheme::CloseBtnBgHov : DeckWindowTheme::CloseBtnBg);
    DrawRectangleRoundedLinesEx(closeButtonBounds, 0.25f, 6, 1.5f, DeckWindowTheme::CloseBtnBorder);

    const char* xLabel = "X";
    float xFSize = (float)fontBaseSize * 0.55f;
    Vector2 xSize = MeasureTextEx(customFont, xLabel, xFSize, 1.0f);
    Vector2 xPos = {
        closeButtonBounds.x + (closeButtonBounds.width - xSize.x) / 2.0f,
        closeButtonBounds.y + (closeButtonBounds.height - xSize.y) / 2.0f
    };
    DrawTextEx(customFont, xLabel, xPos, xFSize, 1.0f, DeckWindowTheme::CloseBtnText);
}
