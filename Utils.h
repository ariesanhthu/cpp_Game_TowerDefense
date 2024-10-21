#pragma once
#include "Logger.h"
#include <random>

typedef struct Image
{
	std::vector<RGBQUAD> pixelsData;
	UINT32 width;
	UINT32 height;
	UINT32 sizeImage;
	UINT32 bitCount;
} Image;

typedef struct Sprite
{
	std::vector<UINT8> pixels; // Index of ConsoleColorTable
	UINT32 width;
	UINT32 height;
	UINT32 size;
} Sprite;

typedef struct SpriteSheet
{
	std::vector<Sprite> sprites;
	UINT32 widthSheet;
	UINT32 heightSheet;
	UINT64 sizeSheet;
	UINT32 widthSprite;
	UINT32 heightSprite;
	UINT64 sizeSprite;
	UINT16 numSpritesX;
	UINT16 numSpritesY;
} SpriteSheet;

typedef struct SpriteBuffer
{
	std::vector<CHAR_INFO> buffer;
	UINT32 width;
	UINT32 height;
	UINT64 size;
} SpriteBuffer;

typedef struct SpriteBufferSheet
{
	std::vector<SpriteBuffer> spriteBuffers;
	UINT16 countSpriteBuffer;
	UINT32 widthSpriteBuffer;
	UINT32 heightSpriteBuffer;
	UINT64 sizeSpriteBufer;
} SpriteBufferSheet;

static const RGBTRIPLE kDefaultColorTable[16] = {
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
static const RGBTRIPLE kVanillaColorTable[16] = {
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

namespace utils
{
	namespace time
	{
		// Get current date and time
		std::string GetCurrentDateAndTime();
	}

	namespace math
	{
		/// <summary>
		/// Clamp integer value
		/// </summary>
		/// <param name="value">: Value</param>
		/// <param name="min">: Min value</param>
		/// <param name="max">: Max value</param>
		/// <returns>Clamped value</returns>
		int ClampInt(int value, int min, int max);

		/// <summary>
		/// Get random integer value
		/// </summary>
		/// <param name="min">: Min value</param>
		/// <param name="max">: Max value</param>
		/// <returns>Random integer value</returns>
		int GetRandomInt(int min, int max);

		/// <summary>
		/// Clamp float value
		/// </summary>
		/// <param name="value">: Value</param>
		/// <param name="min">: Min value</param>
		/// <param name="max">: Max value</param>
		/// <returns>Clamped value</returns>
		float ClampFloat(float value, float min, float max);

		/// <summary>
		/// Get random float value
		/// </summary>
		/// <param name="min">: Min value</param>
		/// <param name="max">: Max value</param>
		/// <returns>Random float value</returns>
		float GetRandomFloat(float min, float max);

		/// <summary>
		/// Get digit of number
		/// </summary>
		/// <param name="number">: Number</param>
		/// <param name="digits">: Vector to store digits</param>
		/// <return>Count of digits</return>
		int GetDigitOfNumber(const int& number, std::vector<int>& digits);

		/// <summary>
		/// Count digits of number
		/// </summary>
		/// <param name="number">: Number</param>
		/// <returns>Count of digits</returns>	
		int CountDigits(int number);
	}

	namespace basic_converter
	{
		/// <summary>
		/// Convert char to wchar
		/// </summary>
		/// <param name="_Char">: Char*</param>
		/// <returns>Wchar_t*</returns>
		wchar_t* CharToWchar(const char* _Char);

		/// <summary>
		/// Convert wchar to char
		/// </summary>
		/// <param name="_wChar">: Wchar_t*</param>
		/// <returns>Char*</returns>
		char* WcharToChar(const wchar_t* _wChar);

		/// <summary>
		/// Convert string to wstring
		/// </summary>
		/// <param name="str">: String</param>
		/// <returns>Wstring</returns>
		std::string WStrToStr(const std::wstring& wstr);

		/// <summary>
		/// Convert wstring to string
		/// </summary>
		/// <param name="wstr">: Wstring</param>
		/// <returns>String</returns>
		std::wstring StrToWStr(const std::string& str);

		// Convert a lower case character to upper case
		char ToUpper(char c);

		// Convert an upper case character to lower case
		char ToLower(char c);

		// Convert a string to lower case
		std::string ToLower(const std::string& str);

		// Convert a string to upper case
		std::string ToUpper(const std::string& str);
	}

	namespace color
	{
		/// <summary>
		/// Get color distance between two colors using Euclidean distance
		/// </summary>
		/// <param name="color1">: Color 1</param>
		/// <param name="color2">: Color 2</param>
		/// <returns>Color distance</returns>
		static float ColorDistance(const RGBTRIPLE& color1, const RGBTRIPLE& color2);

		/// <summary>
		/// Get nearest color index in ConsoleColorTable
		/// </summary>
		/// <param name="color">: Color</param>
		/// <returns>Nearest color index</returns>
		static int GetNearestColorIndex(const RGBTRIPLE& color);
	}

	namespace bitmap_converter
	{
		/// <summary>
		/// Convert bitmap to image
		/// </summary>
		/// <param name="inFilePath">: Input file path</param>
		/// <returns>Image</returns>
		Image BitmaptoImage(const char* inFilePath);

		/// <summary>
		/// Convert Bitmap to ANSI Escape Sequence
		/// </summary>
		/// <param name="inFilePath">: Input file path</param>
		/// <param name="outFilePath">: Output file path</param>
		/// <returns>True: Success, False: Failed and Output File .ans</returns>
		BOOL Bitmap32ToANSI(const char* inFilePath, const char* outFilePath);

		/// <summary>
		/// Convert Image to Sprite
		/// </summary>
		/// <param name="img">: Image</param>
		/// <returns>Sprite</returns>
		Sprite ImageToSprite(const Image& img);

		/// <summary>
		/// Convert Image to SpriteSheet
		/// </summary>
		/// <param name="img">: Image</param>
		/// <param name="widthEachSprite">: Width of each sprite</param>
		/// <param name="heightEachSprite">: Height of each sprite</param>
		/// <returns>SpriteSheet</returns>
		SpriteSheet ImageToSpriteSheet(const Image& img, int widthEachSprite, int heightEachSprite);

		/// <summary>
		/// Convert Sprite to SpriteBuffer
		/// </summary>
		/// <param name="sprite">: Sprite</param>
		/// <returns>SpriteBuffer</returns>
		SpriteBuffer SpriteToFrame(const Sprite& sprite);

		/// <summary>
		/// Convert SpriteSheet to SpriteBufferSheet
		/// </summary>
		/// <param name="spriteSheet">: SpriteSheet</param>
		/// <returns>SpriteBufferSheet</returns>
		SpriteBufferSheet SpriteSheetToFrameSheet(const SpriteSheet& spriteSheet);
	}

	namespace file
	{
		/// <summary>
		/// Make directory
		/// </summary>
		/// <param name="directoryPath">: Directory path</param>
		/// <returns>0: Success, 1: Directory already exists, -1: Failed to create directory</returns>
		int MakeDirectory(const std::string& directoryPath);

		/// <summary>
		/// Check if file exists
		/// </summary>
		/// <param name="filePath">: File path</param>
		/// <returns>True: File exists, False: File does not exist</returns>
		bool IsFileExists(const std::string& filePath);

		/// <summary>
		/// Get file name from file path
		/// </summary>
		/// <param name="filePath">: File path</param>
		/// <returns>File name</returns>
		std::string GetFileName(const std::string& filePath);

		/// <summary>
		/// Get file extension from directory path
		/// </summary>
		/// <param name="directoryPath">: Directory path</param>
		/// <returns>File extension</returns>
		std::vector<std::wstring> GetListFilesInDirectory(const std::string& directoryPath);
	}
} // namespace utils
