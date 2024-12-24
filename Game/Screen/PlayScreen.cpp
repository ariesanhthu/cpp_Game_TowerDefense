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
    int PlayScreen1::getCurrentMap() {
		return 1;
    }
    
    PlayScreen1::PlayScreen1(bool _loadstatus)
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

        mapSetup = { 3, 5, 4, 1 };

        loadstatus = _loadstatus;

        //manager.enemyManager.setNOfPhase(3);

        GamePlaySetup();
    }

    PlayScreen1::~PlayScreen1() {
        path.clear();
        mapSetup.clear();

        OutputDebugStringA(to_string(manager.getPoint()).c_str());
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
    int PlayScreen2::getCurrentMap() {
        return 2;
    }
    PlayScreen2::PlayScreen2(bool _loadstatus) 
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

        
        mapSetup = { 3, 7, 7, 3 };

        manager.towerManager.setNOfTower(8);

        //manager.enemyManager.setNOfPhase(5);
                
        loadstatus = _loadstatus;

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
    int PlayScreen3::getCurrentMap() {
        return 3;
    }

    PlayScreen3::PlayScreen3(bool _loadstatus) {
        path =
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
        };
        mapSetup = { 3, 7, 3, 3 };

        manager.towerManager.setNOfTower(12);

        loadstatus = _loadstatus;

        GamePlaySetup();
    }

    PlayScreen3::~PlayScreen3() {

        path.clear();
        mapSetup.clear();

        OutputDebugStringA("~PlayScreen3\n");
    }
    //========================================================================================================================//

    void PlayScreen4::loadSpecificContent(int width, int height) {
        //void PlayScreen2::loadContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh

        _background = std::make_shared<Item>(L"Assets/background/map4.bmp", scale, 0, 0);
        _instructionboard = std::make_shared<Item>(L"Assets/game/info/board4.png", 1.0f, instructionPos);
    }
    int PlayScreen4::getCurrentMap() {
        return 4;
    }

    PlayScreen4::PlayScreen4(bool _loadstatus) {
        path =
        {
            {
	            { -100, 160 },
	            { 660, 160 },
	            { 660, 800 },
	        },
            {
	            { 290, -100 },
	            { 290, 400 },
	            { 1200, 400 }
	        }
        };

        mapSetup = {3, 15, 15, 15};

        manager.towerManager.setNOfTower(20);

        loadstatus = _loadstatus;

        GamePlaySetup();
    }

    PlayScreen4::~PlayScreen4() {

        path.clear();
        mapSetup.clear();

        OutputDebugStringA("~PlayScreen4\n");
    }
}

