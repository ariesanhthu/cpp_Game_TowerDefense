#include "ScreenSplash.h"
#include "Utils.h"

SPLASH_SCREEN_DATA* _splash_data = nullptr;

void splashScreen::Show()
{
	OutputDebugStringA("Splash screen is showing...\n");
	OutputDebugStringA(("Console buffer width: " + std::to_string(consoleBufferWidth) + "\n").c_str());
	OutputDebugStringA(("Console buffer height: " + std::to_string(consoleBufferHeight) + "\n").c_str());

	// Initialize the splash screen
	if (_splash_data == nullptr)
	{
		_splash_data = new SPLASH_SCREEN_DATA();

		if (_splash_data == nullptr)
		{
			OutputDebugStringA("Failed to initialize splash screen data!\n");
			Log(GetError("Failed to initialize splash screen data!", __FILE__, std::to_string(__LINE__)));

			MessageBoxA(NULL, "The game is missing something. Please reinstall the game!", "Error", MB_ICONERROR | MB_OK);

			return;
		}

		_splash_data->bufferWidth = consoleBufferWidth;
		_splash_data->bufferHeight = consoleBufferHeight;
		_splash_data->bufferSize = _splash_data->bufferWidth * _splash_data->bufferHeight;
		_splash_data->bufferSizeCoord = { static_cast<SHORT>(_splash_data->bufferWidth), static_cast<SHORT>(_splash_data->bufferHeight) };
		_splash_data->writeRegion = { 0, 0, static_cast<SHORT>(_splash_data->bufferWidth), static_cast<SHORT>(_splash_data->bufferHeight) };
		_splash_data->buffer.resize(_splash_data->bufferSize, { 0, 0x00 });
	}

	// Load splash logo from file
	LoadSplashLogoFromMemory(_splash_data->kSplashLogoAnsiPath, _splash_data->splashLogo);
	// LoadSplashLogoFromResource(IDR_ANSI_ESCAPE_CODE1, _splash_data->splashLogo);

	// Draw splash logo
	DrawSplashLogo(_splash_data->splashLogo);
}

static void splashScreen::LoadSplashLogoFromMemory(const char* filePath, std::vector<std::wstring>& logo)
{
	// Check if file is existed?
	if (!utils::file::IsFileExists(filePath))
	{
		OutputDebugStringA("Splash logo file is not existed!\n");
		Log(GetError("Splash logo file is not existed!", __FILE__, std::to_string(__LINE__)));

		// Revert to the default splash logo
		utils::bitmap_converter::Bitmap32ToANSI(_splash_data->kSplashLogoPath, filePath);

		// Check if file is existed?
		if (!utils::file::IsFileExists(filePath))
		{
			OutputDebugStringA("Failed to convert splash logo to ANSI!\n");
			Log(GetError("Failed to convert splash logo to ANSI!", __FILE__, std::to_string(__LINE__)));
			MessageBoxA(NULL, "The game is missing something. Please reinstall the game!", "Error", MB_ICONERROR | MB_OK);

			// Close the console window
			CloseConsoleWindow(-1);
		}

		// Reload the splash logo
		LoadSplashLogoFromMemory(filePath, logo);

		return;
	}

	FILE* file = nullptr;
	errno_t err = fopen_s(&file, filePath, "rb");

	if (err != 0)
	{
		OutputDebugStringA("Failed to load splash logo from file!\n");
		Log(GetError("Failed to load splash logo from file!", __FILE__, std::to_string(__LINE__)));
		return;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);

	if (fileSize == -1)
	{
		OutputDebugStringA("Failed to get file size!\n");
		Log(GetError("Failed to get file size!", __FILE__, std::to_string(__LINE__)));
		fclose(file);
		return;
	}

	fseek(file, 0, SEEK_SET);

	std::vector<char> buffer(fileSize + 1, 0);
	size_t bytesRead = fread(buffer.data(), 1, fileSize, file);

	if (bytesRead != static_cast<size_t>(fileSize))
	{
		OutputDebugStringA("Failed to read file!\n");
		Log(GetError("Failed to read file!", __FILE__, std::to_string(__LINE__)));
		fclose(file);
		return;
	}

	// Convert the buffer to a wide string
	std::wstring wBuffer(buffer.begin(), buffer.end());

	size_t pos = 0;
	size_t start = 0;
	size_t end = 0;

	while ((pos = wBuffer.find(L'\n', start)) != std::wstring::npos)
	{
		logo.push_back(wBuffer.substr(start, pos - start));

		start = pos + 1;
	}

	_splash_data->splashLogoWidth = logo[0].size() / (_splash_data->kBackColor.size() + 4);
	_splash_data->splashLogoHeight = logo.size();

	OutputDebugStringA(("Splash logo width: " + std::to_string(_splash_data->splashLogoWidth) + "\n").c_str());
	OutputDebugStringA(("Splash logo height: " + std::to_string(_splash_data->splashLogoHeight) + "\n").c_str());

	Log("[Splash Screen] Splash logo loaded successfully!");

	fclose(file);
}

void splashScreen::LoadSplashLogoFromResource(const int& resourceID, std::vector<std::wstring>& logo)
{
	HRSRC hResource = FindResourceW(NULL, MAKEINTRESOURCE(resourceID), L"ansi_escape_code");
	if (hResource == NULL)
	{
		OutputDebugStringA("Failed to find resource!\n");
		Log(GetError("Failed to find resource!", __FILE__, std::to_string(__LINE__)));
		return;
	}

	HGLOBAL hGlobal = LoadResource(NULL, hResource);
	if (hGlobal == NULL)
	{
		OutputDebugStringA("Failed to load resource!\n");
		Log(GetError("Failed to load resource!", __FILE__, std::to_string(__LINE__)));
		return;
	}

	DWORD dwSize = SizeofResource(NULL, hResource);
	if (dwSize == 0)
	{
		OutputDebugStringA("Failed to get resource size!\n");
		Log(GetError("Failed to get resource size!", __FILE__, std::to_string(__LINE__)));
		return;
	}

	LPVOID lpResource = LockResource(hGlobal);
	if (lpResource == NULL)
	{
		OutputDebugStringA("Failed to lock resource!\n");
		Log(GetError("Failed to lock resource!", __FILE__, std::to_string(__LINE__)));
		return;
	}

	std::string buffer(static_cast<char*>(lpResource), dwSize);
	std::wstring wBuffer(buffer.begin(), buffer.end());

	size_t pos = 0;
	size_t start = 0;
	size_t end = 0;

	while ((pos = wBuffer.find(L'\n', start)) != std::wstring::npos)
	{
		logo.push_back(wBuffer.substr(start, pos - start));

		start = pos + 1;
	}

	_splash_data->splashLogoWidth = logo[0].size() / (_splash_data->kBackColor.size() + 4);
	_splash_data->splashLogoHeight = logo.size();

	OutputDebugStringA(("Splash logo width: " + std::to_string(_splash_data->splashLogoWidth) + "\n").c_str());
	OutputDebugStringA(("Splash logo height: " + std::to_string(_splash_data->splashLogoHeight) + "\n").c_str());

	Log("[Splash Screen] Splash logo loaded successfully!");
}

void splashScreen::DrawSplashLogo(const std::vector<std::wstring>& logo)
{
	if (hConsoleOut == INVALID_HANDLE_VALUE)
	{
		OutputDebugStringA("Failed to get console handle!\n");
		Log(GetError("Failed to get console handle!", __FILE__, std::to_string(__LINE__)));
		return;
	}

	int x = (consoleBufferWidth - _splash_data->splashLogoWidth) / 2 + 1;
	int y = (consoleBufferHeight - _splash_data->splashLogoHeight) / 2 + 1;
	for (int i = 0; i < _splash_data->splashLogoHeight / 2 + 1; i++)
	{
		GotoXY(x, y + i);
		WriteConsoleW(hConsoleOut, logo[i].c_str(), logo[i].size(), NULL, NULL);

		GotoXY(x, y + _splash_data->splashLogoHeight - i);
		WriteConsoleW(hConsoleOut, logo[_splash_data->splashLogoHeight - i - 1].c_str(), logo[_splash_data->splashLogoHeight - i - 1].size(), NULL, NULL);
	}
}
