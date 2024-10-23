// TowerDefense.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma region MY_HEADERS
#include "Logger.h"
#include "ConsoleWindow.h"

#include "ScreenSplash.h"
//#include "Screen_Menu.h"
#pragma endregion

using namespace std;


int main()
{
	CreateConsoleWindow(
		"hihi",								// Title of window
		kConsoleWindowWidth,				// Width of window
		kConsoleWindowHeight, 				// Height of window
		false,								// Fullscreen
		false,								// Console window resizable
		true, 								// Console window centered
		false,								// Show cursor or not
		false								// Show scrollbar or not
	);
    //std::cout << "Hello World!\n";
	splashScreen::Show();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
