#include "PlayScreen.h"

using namespace std;
namespace towerdefense
{
    void PlayScreen1::loadSpecificContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh

        _background = std::make_shared<Item>(L"Assets/background/map1.bmp", scale, 0, 0);
        _instructionboard = std::make_shared<Item>(L"Assets/game/info/board1.png", 1.0f, instructionPos);
    }
    PlayScreen1::PlayScreen1()
    {
        path =
        {
            {
                {-100, 150},
                {390, 150},
                {390, 490},
                {1250, 490}, //, Thêm path vào sau đây
            }
        };

        mapSetup = { 3,5,4,1 };


        GamePlaySetup();
    }
    PlayScreen1::~PlayScreen1() {
        path.clear();
        mapSetup.clear();

        OutputDebugStringA("~PlayScreen1\n");
    }
    //========================================================================================================================//
    void PlayScreen2::loadSpecificContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh

        _background = std::make_shared<Item>(L"Assets/background/map2.bmp", scale, 0, 0);
        _instructionboard = std::make_shared<Item>(L"Assets/game/info/board2.png", 1.0f, instructionPos);
    }
    PlayScreen2::PlayScreen2() 
    {
        path =
        {
            {
                {-100, 115},
                {435, 115},
                {435, 330},
                {265, 330},
                {265, 515},
                {1250, 515},
            } //, Thêm path vào sau đây
        };

        mapSetup = { 3,5,4,1 };
        

        GamePlaySetup();
    }

    PlayScreen2::~PlayScreen2() {

        path.clear();
        mapSetup.clear();

        OutputDebugStringA("~PlayScreen2\n");
    }
    //========================================================================================================================//
    
    void PlayScreen3::loadSpecificContent(int width, int height) {
        //void PlayScreen2::loadContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh

        _background = std::make_shared<Item>(L"Assets/background/map3.bmp", scale, 0, 0);
        _instructionboard = std::make_shared<Item>(L"Assets/game/info/board3.png", 1.0f, instructionPos);
    }

    PlayScreen3::PlayScreen3() {
        vector<cpoint> 
            path1 = {
                {-100, 170},
                {460, 170},
                {460, 450},
                {1250, 450}
            },
            path2 = {
                { 280, 800 },
                { 280, 450 },
                { 1250, 450 }
            };

        path.push_back(path1);
        path.push_back(path2);

        /*path =
        {
            {
                {-100, 170},
                {460, 170},
                {460, 450},
                {1200, 450}
            },
            {
                { 280, 800 },
                { 280, 450 },
                { 1200, 450 }
            }
        };*/
        mapSetup = { 3,5,4,1 };

        GamePlaySetup();
    }

    PlayScreen3::~PlayScreen3() {

        path.clear();
        mapSetup.clear();

        OutputDebugStringA("~PlayScreen3\n");
    }
}

