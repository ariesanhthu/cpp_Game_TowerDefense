#include "ConsoleWindow.h"

static void SetConsoleFullScreen(HWND hWnd)
{
	if (hWnd == NULL)
	{
		ThrowOnError("Failed to get console window", __FILE__, std::to_string(__LINE__));
	}

	DWORD style = GetWindowLong(hWnd, GWL_STYLE);
	style &= ~(WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL);
	SetWindowLong(hWnd, GWL_STYLE, style);
	SendMessage(hWnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
}

static void SetConsoleFontSize(HANDLE hConsoleOutput, const int& kDesiredFontSizeX, const int& kDesireFontSizeY)
{
	// Get the console output handle
	if (hConsoleOutput == INVALID_HANDLE_VALUE)
	{
		ThrowOnError("Failed to get console output handle", __FILE__, std::to_string(__LINE__));
	}

	// Set the console font size
	CONSOLE_FONT_INFOEX cfi{};
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;							// Index of the font in the system
	cfi.dwFontSize.X = kDesiredFontSizeX;   // Width of each character in the font
	cfi.dwFontSize.Y = kDesireFontSizeY;    // Height of each character in the font
	cfi.FontFamily = FF_DONTCARE;			// Font family
	cfi.FontWeight = FW_NORMAL;				// Font weight

	// Set the console font size
	if (!SetCurrentConsoleFontEx(hConsoleOutput, isConsoleFullScreen, &cfi))
	{
		ThrowOnError("Failed to set console font size", __FILE__, std::to_string(__LINE__));
	}
}

static void SetConsoleWindowSize(HWND hWnd, const int& kDesiredWindowWidth, const int& kDesiredWindowHeight)
{
	if (hWnd == NULL)
	{
		ThrowOnError("Failed to get console window", __FILE__, std::to_string(__LINE__));
	}

	RECT consoleRect;
	if (!GetWindowRect(hWnd, &consoleRect))
	{
		ThrowOnError("Failed to get window rect", __FILE__, std::to_string(__LINE__));
	}

	float dpi = GetDpiForWindow(hWnd) / 96.0f; // Get DPI scale factor

	int desiredWindowWidth = float(kDesiredWindowWidth) / dpi; // Desired window width
	int desiredWindowHeight = float(kDesiredWindowHeight) / dpi; // Desired window height

	OutputDebugStringA(("Desired Window Width: " + std::to_string(desiredWindowWidth) + "\n").c_str());
	OutputDebugStringA(("Desired Window Height: " + std::to_string(desiredWindowHeight) + "\n").c_str());

	// Set the console window size
	if (!MoveWindow(hWnd, consoleRect.left, consoleRect.top, desiredWindowWidth, desiredWindowHeight, TRUE))
	{
		ThrowOnError("Failed to move window", __FILE__, std::to_string(__LINE__));
	}
}

static void SetConsoleBufferSize(HANDLE hConsoleOutput, const int& kBufferWidth, const int& kBufferHeight)
{
	if (hConsoleOutput == INVALID_HANDLE_VALUE)
	{
		ThrowOnError("Failed to get console handle", __FILE__, std::to_string(__LINE__));
	}

	COORD bufferSize = { (SHORT)kBufferWidth, (SHORT)kBufferHeight };

	// Set the screen buffer size
	consoleBufferWidth = kBufferWidth;
	consoleBufferHeight = kBufferHeight;

	if (!SetConsoleScreenBufferSize(hConsoleOutput, bufferSize))
	{
		ThrowOnError("Failed to set console screen buffer size", __FILE__, std::to_string(__LINE__));
	}
}

static void DisableQuickEditMode(HANDLE hConsoleInput)
{
	if (hConsoleInput == INVALID_HANDLE_VALUE)
	{
		ThrowOnError("Failed to get console handle", __FILE__, std::to_string(__LINE__));
	}

	if (!GetConsoleMode(hConsoleInput, &previousConsoleMode))
	{
		ThrowOnError("Failed to get console mode", __FILE__, std::to_string(__LINE__));
	}

	if (!SetConsoleMode(hConsoleInput, previousConsoleMode & ~ENABLE_QUICK_EDIT_MODE))
	{
		ThrowOnError("Failed to set console mode", __FILE__, std::to_string(__LINE__));
	}
}

void EnableANSIEscapeCode(HANDLE hConsoleOutput)
{
	DWORD dwMode = 0;
	if (!GetConsoleMode(hConsoleOutput, &dwMode))
	{
		ThrowOnError("Failed to get console mode", __FILE__, std::to_string(__LINE__));
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if (!SetConsoleMode(hConsoleOutput, dwMode))
	{
		ThrowOnError("Failed to set console mode", __FILE__, std::to_string(__LINE__));
	}
}

static void CenterConsoleWindow(HWND hWnd)
{
	RECT windowRect;
	if (!GetWindowRect(hWnd, &windowRect))
	{
		ThrowOnError("Failed to get desktop window", __FILE__, std::to_string(__LINE__));
	}

	int consoleX = (GetSystemMetrics(SM_CXSCREEN) - (windowRect.right - windowRect.left)) / 2;
	int consoleY = (GetSystemMetrics(SM_CYSCREEN) - (windowRect.bottom - windowRect.top)) / 2;

	int currentWindowWidth = windowRect.right - windowRect.left;
	int currentWindowHeight = windowRect.bottom - windowRect.top;

	if (!MoveWindow(hWnd, consoleX, consoleY, currentWindowWidth, currentWindowHeight, TRUE))
	{
		ThrowOnError("Failed to move console window", __FILE__, std::to_string(__LINE__));
	}
}

static void FixConsoleWindow(HWND hWnd)
{
	if (hWnd == NULL)
	{
		ThrowOnError("Failed to get console window", __FILE__, std::to_string(__LINE__));
	}

	LONG style = GetWindowLong(hWnd, GWL_STYLE); // Get the window style
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME) & ~(WS_HSCROLL) & ~(WS_VSCROLL); // Remove the maximize box and thick frame and scroll bars

	if (!SetWindowLong(hWnd, GWL_STYLE, style))
	{
		ThrowOnError("Failed to set window long", __FILE__, std::to_string(__LINE__));
	}
}

static BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
	case CTRL_CLOSE_EVENT:
	{
		CloseConsoleWindow(0);
		return TRUE;
	}
	default:
		return FALSE;
	}
}

// Get the console window size
POINT GetConsoleBufferSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		ThrowOnError("Failed to get console screen buffer info", __FILE__, std::to_string(__LINE__));
	}

	POINT bufferSize = { csbi.dwSize.X, csbi.dwSize.Y };

	return bufferSize;
}

// Get the console window size
POINT GetConsoleWindowSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		ThrowOnError("Failed to get console screen buffer info", __FILE__, std::to_string(__LINE__));
	}

	POINT consoleSize = { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };

	return consoleSize;
}

// Get the console font size
POINT GetConsoleFontSize()
{
	CONSOLE_FONT_INFO cfi;

	if (!GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi))
	{
		ThrowOnError("Failed to get current console font", __FILE__, std::to_string(__LINE__));
	}

	POINT fontSize = { cfi.dwFontSize.X, cfi.dwFontSize.Y };

	return fontSize;
}

// Get the console window size
POINT GetWindowSize()
{
	RECT consoleRect;

	if (!GetWindowRect(GetConsoleWindow(), &consoleRect))
	{
		ThrowOnError("Failed to get window rect", __FILE__, std::to_string(__LINE__));
	}

	POINT windowSize = { consoleRect.right - consoleRect.left, consoleRect.bottom - consoleRect.top };

	return windowSize;
}

void SetConsoleCursorVisibility(HANDLE hConsoleOutput, bool isVisible)
{
	if (hConsoleOutput == INVALID_HANDLE_VALUE)
	{
		ThrowOnError("Failed to get console handle", __FILE__, std::to_string(__LINE__));
	}

	CONSOLE_CURSOR_INFO cursorInfo;

	if (GetConsoleCursorInfo(hConsoleOutput, &cursorInfo) == 0)
	{
		ThrowOnError("Failed to get console cursor info", __FILE__, std::to_string(__LINE__));
	}

	cursorInfo.bVisible = isVisible;

	if (SetConsoleCursorInfo(hConsoleOutput, &cursorInfo) == 0)
	{
		ThrowOnError("Failed to set console cursor info", __FILE__, std::to_string(__LINE__));
	}
}

void SetColor(int forecolor, int backcolor)
{
	try {
		if (SetConsoleTextAttribute(hConsoleOut, forecolor | (backcolor << 4)) == 0)
		{
			ThrowOnError(std::to_string(GetLastError()), __FILE__, std::to_string(__LINE__));
		}
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		Log(e.what());
	}
}

void GotoXY(int x, int y)
{
	COORD coord = { (SHORT)x, (SHORT)y };
	try {
		if (!SetConsoleCursorPosition(hConsoleOut, coord))
		{
			ThrowOnError(std::to_string(GetLastError()), __FILE__, std::to_string(__LINE__));
		}
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		Log(e.what());
	}
}

void GotoXY(const COORD& coord)
{
	try {
		if (!SetConsoleCursorPosition(hConsoleOut, coord))
		{
			ThrowOnError(std::to_string(GetLastError()), __FILE__, std::to_string(__LINE__));
		}
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		Log(e.what());
	}
}

void SetTableColor(HANDLE hConsoleOutput, const RGBTRIPLE tableColor[16])
{
	CONSOLE_SCREEN_BUFFER_INFOEX csbi;
	csbi.cbSize = sizeof(csbi);

	if (!GetConsoleScreenBufferInfoEx(hConsoleOutput, &csbi))
	{
		ThrowOnError("Failed to get console screen buffer info", __FILE__, std::to_string(__LINE__));
	}

	for (int i = 0; i < 16; i++)
	{
		csbi.ColorTable[i] = RGB(tableColor[i].rgbtBlue, tableColor[i].rgbtGreen, tableColor[i].rgbtRed);
	}

	if (!SetConsoleScreenBufferInfoEx(hConsoleOutput, &csbi))
	{
		ThrowOnError("Failed to set console screen buffer info", __FILE__, std::to_string(__LINE__));
	}
}

void CreateConsoleWindow(
	const std::string& kWindowTitle,
	const int& kWindowWidth, const int& kWindowHeight,
	bool fullScreen,
	bool resizable, bool centered, bool visibleCursor,
	BOOL visibleScrollBars)
{
	try {
		// Hide the console window
		ShowWindow(GetConsoleWindow(), SW_HIDE);

		// Get the console window handle
		consoleWindow = GetConsoleWindow();
		hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

		// Set color pallette
		SetTableColor(hConsoleOut, kVanillaColorPalette);

		// Set the console window title
		SetConsoleTitleA(kWindowTitle.c_str());

		// Set console font size
		SetConsoleFontSize(hConsoleOut, 2, 2);

		if (fullScreen)
		{
			isConsoleFullScreen = true;

			// Set the console full screen
			SetConsoleFullScreen(consoleWindow);

			// Get the vertical scroll bar width
			int vertialScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL);
			OutputDebugStringA(("Vertical Scroll Bar Width: " + std::to_string(vertialScrollBarWidth) + "\n").c_str());

			// Set the screen buffer size
			// Set the screen buffer size
			POINT consoleSize = GetConsoleWindowSize();
			OutputDebugStringA(("Console Size: " + std::to_string(consoleSize.x) + " " + std::to_string(consoleSize.y) + "\n").c_str());
			POINT bufferSize = GetConsoleBufferSize();
			OutputDebugStringA(("Buffer Size: " + std::to_string(bufferSize.x) + " " + std::to_string(bufferSize.y) + "\n").c_str());

			SetConsoleBufferSize(hConsoleOut, bufferSize.x, consoleSize.y);

			// Send F11 key to maximize the console window
			keybd_event(VK_F11, 0, 0, 0);
			keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

			//timer::PreciseSleep(0.1); // Wait for the console window to maximize

			// Send F11 key to maximize the console window
			keybd_event(VK_F11, 0, 0, 0);
			keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

			//timer::PreciseSleep(0.1); // Wait for the console window to maximize

			// Send F11 key to maximize the console window
			keybd_event(VK_F11, 0, 0, 0);
			keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
		}
		else
		{
			// Set the console window size
			SetConsoleWindowSize(consoleWindow, kWindowWidth, kWindowHeight);

			// Set the screen buffer size
			POINT consoleSize = GetConsoleWindowSize();
			OutputDebugStringA(("Console Size: " + std::to_string(consoleSize.x) + " " + std::to_string(consoleSize.y) + "\n").c_str());
			POINT bufferSize = GetConsoleBufferSize();
			OutputDebugStringA(("Buffer Size: " + std::to_string(bufferSize.x) + " " + std::to_string(bufferSize.y) + "\n").c_str());

			SetConsoleBufferSize(hConsoleOut, bufferSize.x, consoleSize.y);

			// Set the console window size
			float dpiScaleFactor = GetDpiForWindow(consoleWindow) / 96.0f; // Get DPI scale factor
			int vertialScrollBarWidth = GetSystemMetrics(SM_CXVSCROLL); // Get the vertical scroll bar width
			OutputDebugStringA(("Vertical Scroll Bar Width: " + std::to_string(vertialScrollBarWidth) + "\n").c_str());
			SetConsoleWindowSize(consoleWindow, kWindowWidth - vertialScrollBarWidth * dpiScaleFactor, kWindowHeight);

			// Center the console window
			if (centered)
			{
				CenterConsoleWindow(consoleWindow);
			}

			// Fix the console window
			if (resizable == false)
			{
				FixConsoleWindow(consoleWindow);
			}
		}

		// Disable quick edit mode
		DisableQuickEditMode(hConsoleOut);

		// Enable ANSI escape code
		EnableANSIEscapeCode(hConsoleOut);

		// Set the console cursor visibility
		SetConsoleCursorVisibility(hConsoleOut, visibleCursor);

		// Register the console control handler
		if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE))
		{
			ThrowOnError("Failed to set console control handler", __FILE__, std::to_string(__LINE__));
		}

		// Get real console window size
		POINT consoleWindowSize = GetWindowSize();

		// Get real console buffer size
		POINT consoleBufferSize = GetConsoleBufferSize();

		// Log all info
		Log("[Info] Console window title: " + kWindowTitle);
		Log("[Info] Console window width: " + std::to_string(consoleWindowSize.x));
		Log("[Info] Console window height: " + std::to_string(consoleWindowSize.y));
		Log("[Info] Console buffer width: " + std::to_string(consoleBufferSize.x));
		Log("[Info] Console buffer height: " + std::to_string(consoleBufferSize.y));
		Log("[Info] Console window full screen: " + std::to_string(fullScreen));
		Log("[Info] Console window resizable: " + std::to_string(resizable));
		Log("[Info] Console window centered: " + std::to_string(centered));
		Log("[Info] Console cursor visible: " + std::to_string(visibleCursor));
		Log("[Info] Console scroll bars visible: " + std::to_string(visibleScrollBars));
		Log("[Info] Console window created successfully!");

		// Show the console window
		ShowWindow(consoleWindow, SW_SHOW);
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		MessageBoxA(NULL, "Failed to create the console window!", "Error", MB_ICONERROR);
		Log("[Error]:" + static_cast<std::string>(e.what()));
		Log("[Error Code | Message]: " + std::to_string(GetLastError()));
	}
}

void CloseConsoleWindow(UINT32 code)
{
	try {
		// Restore console mode
		if (!SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), previousConsoleMode))
		{
			ThrowOnError("Failed to restore console mode", __FILE__, std::to_string(__LINE__));
		}

		// Log all info
		Log("[Info] Console window closed successfully!");

		// Close log file
		logFile.close();

		SendMessage(GetConsoleWindow(), WM_CLOSE, 0, 0); // Close the console window

		ExitProcess(code);
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		Log(e.what());
	}
}
