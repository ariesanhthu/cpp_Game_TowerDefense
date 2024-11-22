#pragma once
#include <vector>
#include <memory>
#include "Graphic.h"
#include <vector>

using namespace std;
namespace towerdefense
{
    class Screen {
    public:
        virtual ~Screen() = default;
        virtual void loadContent(Graphic& graphic, int width, int height) = 0;
        virtual void handleInput() = 0;
        virtual void update(float delta) = 0;
        virtual void render(HDC hdc) = 0;
        //virtual void resizeContent(int windowWidth, int windowHeight);
    };

    class MainScreen : public Screen {
    private:
        HBITMAP background;             // Hình nền
        vector<HBITMAP> buttons;        // Danh sách các nút bấm
        vector<POINT> buttonPositions;  // Vị trí các nút bấm

    public:
        MainScreen();
        ~MainScreen();

        void loadContent(Graphic& graphic, int width, int height) override;
        void handleInput() override; 
        void update(float delta) override;
        void render(HDC hdc) override;
        //void resizeContent(int windowWidth, int windowHeight) override;
    };

}