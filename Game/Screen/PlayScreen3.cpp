//#include "PlayScreen3.h"
//
//namespace towerdefense
//{
//	void PlayScreen3::loadSpecificContent(int width, int height) {
//		//void PlayScreen2::loadContent(int width, int height) {
//		float scaleX = static_cast<float>(width) / 395.0f;  // 1280 là kích thước gốc của ảnh
//		float scaleY = static_cast<float>(height) / 213.0f; // 720 là kích thước gốc của ảnh
//		float scale = min(scaleX, scaleY);                  // Lấy tỉ lệ nhỏ hơn để tránh méo ảnh
//
//		_background = std::make_shared<Item>(L"Assets/background/map3.bmp", scale, 0, 0);
//		_instructionboard = std::make_shared<Item>(L"Assets/game/info/board3.png", 1.0f, instructionPos);
//	}
//	//========================================================================================================================//
//
//	PlayScreen3::PlayScreen3() {
//		path =
//		{
//			{
//				{-100, 170},
//				{460, 170},
//				{460, 450},
//				{1200, 450}
//			},
//			{
//				{ 280, 800 },
//				{ 280, 450 },
//				{ 1200, 450 }
//			}
//		};
//		mapSetup = { 3,5,4,1 };
//
//		GamePlaySetup();
//	}
//
//	PlayScreen3::~PlayScreen3() {
//
//		path.clear();
//		mapSetup.clear();
//
//		OutputDebugStringA("~PlayScreen2\n");
//	}
//}