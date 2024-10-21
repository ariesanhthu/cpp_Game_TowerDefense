#include "ExternalData.h"

// DEFINE EXTENAL VARIABLES

// Saved Game Directionary
const std::string savedGamesDir = "Saved_games/";

// Assets Path
const std::string kAssetsPath = "./Assets/";

// Sounds Directioneries
const std::string kSFXPath = kAssetsPath + "Sounds/SFX/";
const std::string kMusicPath = kAssetsPath + "Sounds/Music/";

// Music Paths
const std::string kMusicSplash = kMusicPath + "Splash.wav";
const std::string kMusic = kMusicPath + "Music.wav";

// Sound effects Paths
const std::string kSoundButtonSelected = kSFXPath + "button_selected.wav";
const std::string kSoundButtonPressed = kSFXPath + "button_pressed.wav";
const std::string kSnakeEatFood = kSFXPath + "snake_eat_food.wav";
const std::string kFoodSpawn = kSFXPath + "food_spawn.wav";
const std::string kGameOver = kSFXPath + "end_game.wav";
const std::string kCountDown = kSFXPath + "timer.wav";
const std::string kLowLive = kSFXPath + "live_is_low.wav";
const std::string kTransition = kSFXPath + "transition.wav";
const std::string kDamage = kSFXPath + "damage.wav";
const std::string kBomb = kSFXPath + "bomb.wav";
const std::string KMedal = kSFXPath + "medal.wav";


// Console handle
HWND consoleWindow = NULL;
HANDLE hConsoleIn = NULL;
HANDLE hConsoleOut = NULL;

// Console Window
const int kConsoleWindowWidth = 1280;
const int kConsoleWindowHeight = 720;

// Console Buffer
int consoleBufferWidth = 0;
int consoleBufferHeight = 0;

// Console Full Screen
bool isConsoleFullScreen = false;