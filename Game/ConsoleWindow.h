#pragma once
#include "ExternalData.h"
#include "Logger.h"
extern std::ofstream logFile;
//
//#include "Console_Sound.h"
//#include "Console_Input.h"
//#include "Console_Timer.h"

#include <Windows.h>

// DECLARE EXTENAL VARIABLES
static DWORD previousConsoleMode = 0; // Previous console mode

static const RGBTRIPLE kDefaultColorPalette[16] = {
	{12, 12, 12},		// Black
	{0, 55, 218},		// Dark Blue
	{19, 161, 14},		// Dark Green
	{58, 150, 221},		// Dark Cyan
	{197, 15, 31},		// Dark Red
	{136, 23, 152},		// Dark Magenta
	{193, 156, 0},		// Dark Yellow
	{204, 204, 204},	// Light Gray
	{118, 118, 118},	// Dark Gray
	{59, 120, 255},		// Blue
	{22, 198, 12},		// Green
	{97, 214, 214},		// Cyan
	{231, 72, 86},		// Red
	{180, 0, 158},		// Magenta
	{249, 241, 165},	// Yellow
	{242, 242, 242}		// White
};

//VANILA MILKSHAKE
static const RGBTRIPLE kVanillaColorPalette[16] = {
	{40, 40, 46},		// Jaguar
	{108, 86, 113},		// Fedora
	{217, 200, 191},	// Pearl Bush
	{249, 130, 132},	// Salmon
	{176, 169, 228},	// Perano
	{172, 204, 228},	// French Pass
	{179, 227, 218},	// Ice Cold
	{254, 170, 228},	// Lavender Rose
	{135, 168, 137},	// Envy
	{176, 235, 147},	// Sulu
	{233, 245, 157},	// Portafino
	{255, 230, 198},	// Bisque
	{222, 163, 139},	// Tumbleweed
	{255, 247, 160},	// Canary
	{255, 247, 228},	// Corn silk
	{242, 242, 242}		// White smoke
};

/// <summary>
/// Set the console window to full screen
/// </summary>
/// <param name="hWnd">: The console window handle</param>
static void SetConsoleFullScreen(HWND hWnd);

/// <summary>
/// Set the console font size
/// </summary>
/// <param name="hConsoleOutput">: The console output handle</param>
/// <param name="kDesiredFontSizeX">: The desired font size x</param>
/// <param name="kDesireFontSizeY">: The desired font size y</param>
static void SetConsoleFontSize(HANDLE hConsoleOutput, const int& kDesiredFontSizeX, const int& kDesireFontSizeY);

/// <summary>
/// <para>Set the console window size</para>
/// <para>NOTE: The console window size is the size of the window that contains the console buffer</para>
/// <para>NOTE: The console buffer size is the size of the buffer that contains the console data</para>
/// </summary>
/// <param name="hWnd">: The console window handle</param>
/// <param name="kDesiredWindowWidth">: The desired window width</param>
/// <param name="kDesiredWindowHeight">: The desired window height</param>
static void SetConsoleWindowSize(HWND hWnd, const int& kDesiredWindowWidth, const int& kDesiredWindowHeight);

/// <summary>
/// <para>Set the console buffer size</para>
/// <para>NOTE: The console window size is the size of the window that contains the console buffer</para>
/// <para>NOTE: The console buffer size is the size of the buffer that contains the console data</para>
/// </summary>
/// <param name="hConsoleOutput">: The console output handle</param>
/// <param name="kBufferWidth">: The buffer width</param>
/// <param name="kBufferHeight">: The buffer height</param>
static void SetConsoleBufferSize(HANDLE hConsoleOutput, const int& kBufferWidth, const int& kBufferHeight);

/// <summary>
/// Disable quick edit mode
/// </summary>
/// <param name="hConsoleInput">: The console input handle</param>
static void DisableQuickEditMode(HANDLE hConsoleInput);

/// <summary>
/// Enable Virtual Terminal Processing (ANSI Escape Code)
/// </summary>
/// <param name="hConsoleOutput">: The console output handle</param>
static void EnableANSIEscapeCode(HANDLE hConsoleOutput);

/// <summary>
/// Center the console window
/// </summary>
/// <param name="hWnd">: The console window handle</param>
/// 
static void CenterConsoleWindow(HWND hWnd);

/// <summary>
/// Fix the console window
/// </summary>
/// <param name="hWnd">: The console window handle</param>
static void FixConsoleWindow(HWND hWnd);

/// <summary>
/// Console control handler
/// </summary>
/// <param name="fdwCtrlType">: The control type</param>
/// <returns>TRUE if the control type is CTRL_CLOSE_EVENT, otherwise FALSE</returns>
static BOOL CtrlHandler(DWORD fdwCtrlType);

// Get the console buffer size
POINT GetConsoleBufferSize();

// Get the console window size
POINT GetConsoleWindowSize();

// Get the console font size
POINT GetConsoleFontSize();

// Get the console window rect
POINT GetWindowSize();

/// <summary>
/// Set the console cursor visibility
/// </summary>
/// <param name="hConsoleOutput">: The console output handle</param>
/// <param name="isVisible">: The visibility of the cursor</param>
void SetConsoleCursorVisibility(HANDLE hConsoleOutput, bool isVisible);

/// <summary>
/// Set the console text color
/// </summary>
/// <param name="forecolor">: The foreground color</param>
/// <param name="backcolor">: The background color</param>
void SetColor(int forecolor, int backcolor);

/// <summary>
/// Goto the console cursor position (x, y)
/// </summary>
/// <param name="x">: The x position</param>
/// <param name="y">: The y position</param>
void GotoXY(int x, int y);

/// <summary>
/// Goto the console cursor position by COORD
/// </summary>
/// <param name="coord">: The console cursor position</param>
void GotoXY(const COORD& coord);

/// <summary>
/// Set new color palette for the console - 16 colors
/// </summary>
/// <param name="hConsoleOutput">: The console output handle</param>
/// <param name="tableColor">: The new color palette</param>
void SetTableColor(HANDLE hConsoleOutput, const RGBTRIPLE tableColor[16]);

/// <summary>
/// Create the console window
/// </summary>
/// <param name="kWindowTitle">: The window title</param>
/// <param name="kWindowWidth">: The window width</param>
/// <param name="kWindowHeight">: The window height</param>
/// <param name="fullScreen">: The full screen mode</param>
/// <param name="resizable">: The resizable mode</param>
/// <param name="centered">: The centered mode</param>
/// <param name="visibleCursor">: The visible cursor mode</param>
/// <param name="visibleScrollBars">: The visible scroll bars mode</param>
void CreateConsoleWindow(
	const std::string& kWindowTitle,
	const int& kWindowWidth, const int& kWindowHeight,
	bool fullScreen,
	bool resizable, bool centered, bool visibleCursor,
	BOOL visibleScrollBars);

/// <summary>
/// Close the console window
/// </summary>
/// <param name="code">: The exit code</param>
void CloseConsoleWindow(UINT32 code);
