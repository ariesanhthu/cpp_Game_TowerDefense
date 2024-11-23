#pragma once
#include <windows.h>
#include <string>
#include <functional>
#include "State.h"
#include <ScreenManager.h>

namespace towerdefense
{

	class Game
	{
	private:
		std::unique_ptr<GameState> currentState;
		std::unique_ptr<Screen> currentScreen;
		Graphic graphic;

	public:
		void setState(std::unique_ptr<GameState> newState) {
			currentState = std::move(newState);
		}

		void handleInput() { currentState->handleInput(); }
		void update(float delta) { currentState->update(delta); }
		void render(HDC hdc) { currentState->render(hdc); }

		//-----------------------------------------------------------
		friend LRESULT CALLBACK WindowCallback(
			HWND windowHandle,
			UINT message,
			WPARAM wParam,
			LPARAM lParam
		);

	private:
		HINSTANCE hInstance;
		HWND windowHandle = 0;
		bool running = false;
		std::wstring windowTitle;
		//std::function<void(float delta)> update;
		int windowWidth, windowHeight;
	
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator= (const Game&) = delete;
		~Game() {}
		
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

		void loadInitialScreen();

	private:
		void startWindow();
	};
}