#include "PlayScreen2.h"

using namespace std;
namespace towerdefense
{
    /*
    ======================================

    ======================================
    */

    void PlayScreen2::loadSpecificContent(int width, int height) {
    //void PlayScreen2::loadContent(int width, int height) {
        float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
        float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
        float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh

        _background = std::make_shared<Item>(L"Assets/background/map2.bmp", scale, 0, 0);
        _instructionboard = std::make_shared<Item>(L"Assets/game/info/board2.png", 1.0f, instructionPos);
    }

    /*
    ======================================
            KHỞI TẠO CÁC GIÁ TRỊ
    ======================================
    */
    PlayScreen2::PlayScreen2() {
        // setup game 
        // setup path
        // khởi tạo random path (nếu có)
        path =
        {
            {
            {-100, 115},
            {435, 115},
            {435, 330},
            {265, 330},
            {265, 515},
            {1200, 515},
            } //, Thêm path vào sau đây
        };

        mapSetup = { 3,5,4,1 };
        

        GamePlaySetup();
        //Turretinit = { 50, 565 };

    }
  
    /*
    ======================================
                  DESTRUCTOR
    ======================================
    */
    PlayScreen2::~PlayScreen2() {

        path.clear();
        mapSetup.clear();

        OutputDebugStringA("~PlayScreen2\n");
    }

    /*
    ======================================
                BẮT SỰ KIỆN
    ======================================
    */

    //void PlayScreen2::handleSpecificInput(HWND hwnd) {
   /* void PlayScreen2::handleInput(HWND hwnd) {
            
    }*/

    /*
    ======================================
            UPDATE NHỮNG THAY ĐỔI
    ======================================
    */
    // ??? 1. CÓ TÁCH CODE
    // ??? 2. tách như thế nào cho mịn (À TẤT CẢ ĐỀU DÙNG CHUNG???
    // 3. PAUSE GAME NÈ
    //void PlayScreen2::updateSpecific(float delta) {
    //void PlayScreen2::update(float delta) {
    //    

    //    //manager.update(delta);

    //    // UPDATE CONTENT RIÊNG
    //    //OutputDebugStringA("updateSpecific2\n");
    //}

    /*
    ======================================
                  DISPLAY
    ======================================
    */

    //void PlayScreen2::renderSpecific(HDC hdc) {
    //void PlayScreen2::render(HDC hdc) {

    //    // LOAD CONTENT RIÊNG
    //    //OutputDebugStringA("renderSpecific2\n");



    //}

}

