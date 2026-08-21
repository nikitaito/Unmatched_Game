
#ifndef COMBAT_PAGE
#define COMBAT_PAGE


#include "handmenu.h"
#include <vector>



class CombatPage {
    private:
        void DrawLabel(const char *text, Vector2 pos, float size, Color color) const;
        
    public:
        Rectangle area{};

        Rectangle defenceSlot{}; 
        Rectangle attackSlot{};  

        CPHandMenu defenceHand; 
        CPHandMenu attackHand;  

        Rectangle skipButton{};
        Rectangle chooseButton{};

        Font font = GetFontDefault();

        Texture2D centerIcon{};
        float centerIconSize = 70.0f;

        Texture2D backgroundImage{};
        float backgroundOverlayAlpha = 0.55f;

        bool skipPressed = false;
        bool choosePressed = false;
        bool skipHovered = false;
        bool chooseHovered = false;
        int  defenceCardClicked = -1; 
        int  attackCardClicked  = -1; 

        void Init(Rectangle newArea);

        void Update();

        void Draw() const;


};
#endif