#pragma once
#include "ColorReferences.h"
#include "ExternalData.h"
#include "ConsoleWindow.h"
/*
#include "resource.h"
#include "Graphics.h"*/
#include <vector>
struct SPLASH_SCREEN_DATA
{
	// ************************************************************
	// *           SPLASH SCREEN CONSTANTS AND VARIABLES          *
	// ************************************************************
	const double kSplashScreenDuration = 8;
	const double kSplashLogoDrawDelay = 0.02;
	const std::wstring kBackColor = L"\033[48;2;255;255;255m\033[38;2;255;255;255m ";
	const char* kSplashLogoPath = "./Assets/ANSI/splash_art_156.bmp";
	const char* kSplashLogoAnsiPath = "./Assets/ANSI/splash_art_156.ans";
	int numberLinesToDraw = 4;
	int splashLogoWidth = 0;
	int splashLogoHeight = 0;
	std::wstring backgroundFull = L"";
	std::vector<std::wstring> splashLogo;

	// **********************************************
	// *          SCREEN VARIABLES                  *
	// **********************************************
	int bufferWidth = 0;
	int bufferHeight = 0;
	int bufferSize = 0;
	COORD bufferCoord = { 0, 0 };
	COORD bufferSizeCoord = { 0, 0 };
	SMALL_RECT writeRegion = { 0, 0, 0, 0 };
	std::vector<CHAR_INFO> buffer;

	// **********************************************
	// *          FIRST GUIDE TEXT		            *
	// **********************************************
	const std::string kGuidedMessage[6] = {
		"WELCOME TO THE GAME",
		"GAME WILL SAVE YOUR MATCH AUTOMATICALLY!",
		"ONLY CLASSIC MODE IS AVAILABLE.",
		"WE HOPE YOU HAVE A GREAT EXPERIENCE WITH OUR GAME :)",
		"- FROM THE TEAM 13 WTH LUV -",
		"PRESS SPACE TO CONTINUE..."
	};
};

namespace splashScreen
{
	void Show();

	static void InitializeBackground();

	static void LoadSplashLogoFromMemory(const char* filePath, std::vector<std::wstring>& logo);

	static void LoadSplashLogoFromResource(const int& resourceID, std::vector<std::wstring>& logo);

	static void DrawBackground();

	static void DrawSplashLogo(const std::vector<std::wstring>& logo);
}