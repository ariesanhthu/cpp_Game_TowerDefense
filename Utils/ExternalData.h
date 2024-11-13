#pragma once
#include <Windows.h>
#include <string>

// Saved Game Directionary
extern const std::string savedGamesDir;

// Assets Path
extern const std::string kAssetsPath;

// Sounds Directioneries
extern const std::string kSFXPath;
extern const std::string kMusicPath;

// Music Paths
extern const std::string kMusicSplash;

// Sound effects Paths
extern const std::string kSoundButtonSelected;
extern const std::string kSoundButtonPressed;
extern const std::string kMusic;
extern const std::string kSnakeEatFood;
extern const std::string kFoodSpawn;
extern const std::string kGameOver;
extern const std::string kCountDown;
extern const std::string kLowLive;
extern const std::string kTransition;
extern const std::string kDamage;
extern const std::string kBomb;
extern const std::string KMedal;

// Console handle
extern HWND consoleWindow;
extern HANDLE hConsoleIn;
extern HANDLE hConsoleOut;

// Console Window
extern const int kConsoleWindowWidth;
extern const int kConsoleWindowHeight;

// Console Buffer
extern int consoleBufferWidth;
extern int consoleBufferHeight;

// Console Full Screen
extern bool isConsoleFullScreen;
