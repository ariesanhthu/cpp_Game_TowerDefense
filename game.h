﻿#pragma once

#include <windows.h>
#include <string>
#include <functional>
#include <chrono>
#include <thread>
#include <memory>

//#include "State.h"
#include "Graphic.h"

// SCREEN HEADER
#include "Screen/ScreenManager.h"
#include "Screen/MainScreen.h"
#include "Screen/PlayScreen.h"
#include "Utils.h"

// ------------------------------
#include "AudioManager.h"
#include "FontManager.h"

//#include "ThreadManager.h"

//#include "EventManager.h"

#define WM_CUSTOM_LOAD_SCREEN (WM_USER + 1)
using namespace std;

namespace towerdefense
{
	class Game
	{
	private:
		//std::unique_ptr<GameState> currentState;
		shared_ptr<ScreenManager> screenManager;
		Utils utils;
		

	public:
		/*void setState(std::unique_ptr<GameState> newState) {
			currentState = std::move(newState);
		}*/

		/*void handleInput() { currentState->handleInput(); }
		void update(float delta) { currentState->update(delta); }
		void render(HDC hdc) { currentState->render(hdc); }*/

		//-----------------------------------------------------------
		friend LRESULT CALLBACK WindowCallback(
			HWND windowHandle,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);

	private:
		HINSTANCE hInstance;
		HCURSOR hCustomCursor;
		HWND windowHandle = 0;

		bool running = false;
		std::wstring windowTitle;
		int windowWidth, windowHeight;
	
	public:

		bool firstStart = false;

		Game();
		Game(const Game&) = delete;
		Game& operator= (const Game&) = delete;
		~Game() {
			// Cleanup FontManager sau cùng
			//// Đảm bảo các màn hình được hủy trước
			//screenManager.reset();
			//// Cleanup FontManager sau cùng
			FontManager::getInstance().cleanupFonts();

			OutputDebugStringA("~Game\n");
		}
		
		inline static Game& getInstance()
		{
			static Game game;
			return game;
		}
		
		inline static void start()
		{
			getInstance().startWindow();
		}

		inline static void setWindowProperties(const std::wstring& title, const int& width, const int& height)
		{
			getInstance().windowTitle = title;
			getInstance().windowWidth = width;
			getInstance().windowHeight = height;
		}

		//inline static void setGameUpdate(const std::function<void(float delta)>& update) { getInstance().update = update; }
		inline static std::wstring getWindowTitle() { return getInstance().windowTitle; }
		inline static int getWindowWidth() { return getInstance().windowWidth; }
		inline static int getWindowHeight() { return getInstance().windowHeight; }

		void loadInitialScreen(int);

	private:
		void startWindow();
	};
}