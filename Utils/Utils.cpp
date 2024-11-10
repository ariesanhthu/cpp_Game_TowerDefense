#include "Utils.h"

namespace utils
{
	namespace time
	{
		std::string GetCurrentDateAndTime()
		{
			SYSTEMTIME time;
			GetLocalTime(&time);

			char dateTime[26];
			sprintf_s(dateTime, "%02d-%02d-%02d %02d:%02d:%02d",
				time.wYear, time.wMonth, time.wDay,
				time.wHour, time.wMinute, time.wSecond);

			return std::string(dateTime);
		}
	}

	namespace math
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());

		// Clamp integer value between min and max
		int ClampInt(int value, int min, int max)
		{
			if (value < min)
			{
				return min;
			}
			else if (value > max)
			{
				return max;
			}
			return value;
		}

		// Get random integer between min and max
		int GetRandomInt(int min, int max)
		{
			std::uniform_int_distribution<> dis(min, max);
			return dis(gen);
		}

		// Clamp float value between min and max
		float ClampFloat(float value, float min, float max)
		{
			if (value < min)
			{
				return min;
			}
			else if (value > max)
			{
				return max;
			}
			return value;
		}

		// Get random float between min and max
		float GetRandomFloat(float min, float max)
		{
			std::uniform_real_distribution<> dis(min, max);
			return dis(gen);
		}

		int GetDigitOfNumber(const int& number, std::vector<int>& digits)
		{
			int num = number;
			int digit = 0;

			// Check if that number is zero
			if (num == 0) {
				digits.push_back(0);
				return 1;
			}

			while (num > 0)
			{
				digit = num % 10;
				digits.push_back(digit);
				num /= 10;
			}

			std::reverse(digits.begin(), digits.end());

			return digits.size();
		}

		int CountDigits(int number)
		{
			int count = 0;

			while (number != 0)
			{
				number /= 10;
				++count;
			}

			return count;
		}
	} // namespace math

	namespace basic_converter
	{
		// Convert char* to wchar_t*
		wchar_t* CharToWchar(const char* _Char)
		{
			wchar_t* wcharStr = new wchar_t[strlen(_Char)] { 0 };
			swprintf_s(wcharStr, strlen(_Char), L"%hs", _Char);
			return wcharStr;
		}

		// Convert wchar_t* to char*
		char* WcharToChar(const wchar_t* _wChar)
		{
			char* charStr = new char[wcslen(_wChar)] { 0 };
			sprintf_s(charStr, wcslen(_wChar), "%ls", _wChar);
			return charStr;
		}

		// Convert char* to std::string
		std::string WStrToStr(const std::wstring& wstr)
		{
			int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
			std::string strTo(size_needed, 0);
			WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
			return strTo;
		}

		// Convert std::string to wchar_t*
		std::wstring StrToWStr(const std::string& str)
		{
			int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
			std::wstring wstrTo(size_needed, 0);
			MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
			return wstrTo;
		}

		char ToUpper(char c)
		{
			if (c >= 'a' && c <= 'z')
			{
				return c - 32;
			}
			return c;
		}

		char ToLower(char c)
		{
			if (c >= 'A' && c <= 'Z')
			{
				return c + 32;
			}
			return c;
		}

		std::string ToLower(const std::string& str)
		{
			std::string lowerStr = str;

			for (size_t i = 0; i < lowerStr.size(); ++i)
			{
				lowerStr[i] = ToLower(lowerStr[i]);
			}

			return lowerStr;
		}

		std::string ToUpper(const std::string& str)
		{
			std::string upperStr = str;

			for (size_t i = 0; i < upperStr.size(); ++i)
			{
				upperStr[i] = ToUpper(upperStr[i]);
			}

			return upperStr;
		}
	} // namespace basic_converter

	namespace color
	{
		static float ColorDistance(const RGBTRIPLE& color1, const RGBTRIPLE& color2)
		{
			float dR = color1.rgbtRed - color2.rgbtRed;
			float dG = color1.rgbtGreen - color2.rgbtGreen;
			float dB = color1.rgbtBlue - color2.rgbtBlue;

			return sqrtf(dR * dR + dG * dG + dB * dB);
		}

		static int GetNearestColorIndex(const RGBTRIPLE& color)
		{
			int nearestColorIndex = 0;
			float nearestDistance = ColorDistance(color, kVanillaColorTable[0]);
			float distance = 0;

			for (int i = 1; i < 16; ++i)
			{
				distance = ColorDistance(color, kVanillaColorTable[i]);

				if (distance < nearestDistance)
				{
					nearestDistance = distance;
					nearestColorIndex = i;
				}
			}

			return nearestColorIndex;
		}
	} // namespace color

	namespace bitmap_converter
	{
		Image BitmaptoImage(const char* inFilePath)
		{
			FILE* f; // File pointer

			if (fopen_s(&f, inFilePath, "rb") != 0 || !f) {
				Log((std::string("[Converter] File not found: ") + inFilePath).c_str());
				OutputDebugStringA((std::string("[Converter] File not found: ") + inFilePath).c_str());
				return Image();
			}

			// Read BMP file
			BITMAPFILEHEADER fileHeader; // 14 bytes
			BITMAPINFOHEADER infoHeader; // 40 bytes
			fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, f); // Read file header
			fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, f); // Read info header

			// Check if file is BMP
			if (fileHeader.bfType != 0x4D42)
			{
				Log((std::string("[Converter] File is not BMP: ") + inFilePath).c_str());
				return Image();
			}

			// Check if file is 32-bit
			if (infoHeader.biBitCount != 32)
			{
				Log((std::string("[Converter] Unsupported format: ") + inFilePath).c_str());
				Log((std::string("[Converter] Only 32-bit BMP files are supported! Please convert color depth to 32bit and try again!").c_str()));
				Log((std::string("[Converter] File format: ") + std::to_string(infoHeader.biBitCount) + "-bit").c_str());
				return Image();
			}

			// Check if file is compressed
			if (infoHeader.biCompression != 0 && infoHeader.biCompression != 3)
			{
				Log((std::string("[Converter] Compressed BMP file is not supported: ") + inFilePath).c_str());
				return Image();
			}

			// Log all properties of BITMAPFILEHEADER and BITMAPINFOHEADER
			Log((std::string("[Converter] File: ") + inFilePath).c_str());
			Log("[Converter] BITMAPFILEHEADER:");
			Log((std::string("[Converter] bfType: ") + std::to_string(fileHeader.bfType)).c_str());
			Log((std::string("[Converter] bfSize: ") + std::to_string(fileHeader.bfSize)).c_str());
			Log((std::string("[Converter] bfReserved1: ") + std::to_string(fileHeader.bfReserved1)).c_str());
			Log((std::string("[Converter] bfReserved2: ") + std::to_string(fileHeader.bfReserved2)).c_str());
			Log((std::string("[Converter] bfOffBits: ") + std::to_string(fileHeader.bfOffBits)).c_str());
			Log("[Converter] BITMAPINFOHEADER:");
			Log((std::string("[Converter] biSize: ") + std::to_string(infoHeader.biSize)).c_str());
			Log((std::string("[Converter] biWidth: ") + std::to_string(infoHeader.biWidth)).c_str());
			Log((std::string("[Converter] biHeight: ") + std::to_string(infoHeader.biHeight)).c_str());
			Log((std::string("[Converter] biPlanes: ") + std::to_string(infoHeader.biPlanes)).c_str());
			Log((std::string("[Converter] biBitCount: ") + std::to_string(infoHeader.biBitCount)).c_str());
			Log((std::string("[Converter] biCompression: ") + std::to_string(infoHeader.biCompression)).c_str());
			Log((std::string("[Converter] biSizeImage: ") + std::to_string(infoHeader.biSizeImage)).c_str());
			Log((std::string("[Converter] biXPelsPerMeter: ") + std::to_string(infoHeader.biXPelsPerMeter)).c_str());
			Log((std::string("[Converter] biYPelsPerMeter: ") + std::to_string(infoHeader.biYPelsPerMeter)).c_str());
			Log((std::string("[Converter] biClrUsed: ") + std::to_string(infoHeader.biClrUsed)).c_str());
			Log((std::string("[Converter] biClrImportant: ") + std::to_string(infoHeader.biClrImportant)).c_str());

			// Offset to pixel data
			fseek(f, fileHeader.bfOffBits, SEEK_SET);

			// Read pixel data
			Image img;
			img.width = infoHeader.biWidth; // Image width
			img.height = infoHeader.biHeight < 0 ? -infoHeader.biHeight : infoHeader.biHeight; // Image height
			img.sizeImage = infoHeader.biSizeImage / sizeof(RGBQUAD); // Image size
			img.bitCount = infoHeader.biBitCount;
			img.pixelsData.resize(img.sizeImage); // 4 bytes per pixel

			fread(img.pixelsData.data(), sizeof(RGBQUAD), img.sizeImage, f); // Read pixel data

			// Check if pixel data is empty
			if (img.pixelsData.empty())
			{
				Log((std::string("[Converter] Failed to read pixel data: ") + inFilePath).c_str());
				return Image();
			}

			// Check if image is written from bottom to top
			if (infoHeader.biHeight > 0)
			{
				// Reverse image
				std::reverse(img.pixelsData.begin(), img.pixelsData.end());
			}

			fclose(f); // Close file

			return img; // Return image object
		}

		BOOL Bitmap32ToANSI(const char* inFilePath, const char* outFilePath)
		{
			FILE* out;
			_wfopen_s(&out, utils::basic_converter::StrToWStr(outFilePath).c_str(), L"w");

			if (!out) {
				Log((std::string("[Converter] File not found: ") + outFilePath).c_str());
				return false;
			}

			// Get Image struct from bitmap file
			Image img = BitmaptoImage(inFilePath);

			if (img.pixelsData.empty())
			{
				Log((std::string("[Converter] Failed to convert to ANSI: ") + inFilePath).c_str());
				return false;
			}

			// Get pixel data
			int width = img.width;
			int height = img.height;
			int pixelSize = img.pixelsData.size();
			std::vector<RGBQUAD> pixels = img.pixelsData; // 4 bytes per pixel

			std::wstring ansiCode = L"\033[48;2;%d;%d;%dm\033[38;2;%d;%d;%dm "; // ANSI color code

			for (size_t i = 0; i < pixelSize; i++)
			{
				// Convert RGB to ANSI color
				int r = pixels[i].rgbRed;
				int g = pixels[i].rgbGreen;
				int b = pixels[i].rgbBlue;

				fwprintf(out, ansiCode.c_str(), r, g, b, r, g, b); // Write ANSI color code to file

				if (i % width == width - 1)
				{
					fwprintf(out, L"\033[0m\n"); // Reset color and new line
				}
			}

			fclose(out); // Close file

			Log((std::string("[Converter] Converted to ANSI: ") + outFilePath).c_str());
			return true;
		}

		Sprite ImageToSprite(const Image& img)
		{
			// Check if image is empty
			if (img.pixelsData.empty())
			{
				Log("[Converter] Image is empty!");
				OutputDebugStringW(L"[Converter] Image is empty!");
				return Sprite();
			}

			// Get pixel data
			std::vector<RGBQUAD> pixels = img.pixelsData; // 4 bytes per pixel

			// Create sprite
			Sprite sprite;
			sprite.width = img.width;
			sprite.height = img.height;
			sprite.size = img.width * img.height;
			sprite.pixels.reserve(sprite.size); // Reserve sprite size

			// Loop through each pixel
			for (size_t i = 0; i < sprite.size; ++i)
			{
				// Get nearest color index
				sprite.pixels.push_back(color::GetNearestColorIndex({
					pixels[i].rgbRed,
					pixels[i].rgbGreen,
					pixels[i].rgbBlue
					})
				);
			}

			return sprite;
		}

		SpriteSheet ImageToSpriteSheet(const Image& img, int widthEachSprite, int heightEachSprite)
		{
			// Check if image is empty
			if (img.pixelsData.empty())
			{
				Log("[Converter] Image is empty!");
				OutputDebugStringW(L"[Converter] Image is empty!");
				return SpriteSheet();
			}

			// Get Image properties
			int imgWidth = img.width;
			int imgHeight = img.height;
			int pixelSize = img.pixelsData.size();
			int bitCount = img.bitCount;
			std::vector<RGBQUAD> pixels = img.pixelsData; // 4 bytes per pixel

			// Calculate number of sprites
			int numSpritesX = imgWidth / widthEachSprite; // Number of sprites in X axis
			int numSpritesY = imgHeight / heightEachSprite;	// Number of sprites in Y axis

			OutputDebugStringA((std::string("[Converter] Number of sprites in X axis: ") + std::to_string(numSpritesX) + "\n").c_str());
			OutputDebugStringA((std::string("[Converter] Number of sprites in Y axis: ") + std::to_string(numSpritesY) + "\n").c_str());

			// Check if image is not divisible by sprite size
			if (imgWidth % widthEachSprite != 0 || imgHeight % heightEachSprite != 0)
			{
				Log("[Converter] Image is not divisible by sprite size!");
				OutputDebugStringW(L"[Converter] Image is not divisible by sprite size!");
				return SpriteSheet();
			}

			// Create sprite sheet
			SpriteSheet spriteSheet;
			spriteSheet.sprites.reserve(numSpritesX * numSpritesY); // Reserve sprite size

			// Create sprite
			Sprite sprite;
			sprite.width = widthEachSprite;
			sprite.height = heightEachSprite;
			sprite.size = widthEachSprite * heightEachSprite;
			sprite.pixels.reserve(sprite.size); // Reserve sprite size

			// Create RGBQUAD color
			int pixelIndex = 0;

			// Loop through each sprite
			for (int y = 0; y < numSpritesY; y++)
			{
				for (int x = 0; x < numSpritesX; x++)
				{
					int baseIndex = y * heightEachSprite * imgWidth + x * widthEachSprite;

					// Loop through each pixel in sprite
					for (int j = 0; j < heightEachSprite; j++)
					{
						for (int i = 0; i < widthEachSprite; i++)
						{
							// Get pixel index of this sprite
							pixelIndex = baseIndex + j * imgWidth + i;

							sprite.pixels.push_back(color::GetNearestColorIndex({
								pixels[pixelIndex].rgbRed,
								pixels[pixelIndex].rgbGreen,
								pixels[pixelIndex].rgbBlue
								})
							);
						}
					}

					// Add sprite to sprite sheet
					spriteSheet.sprites.push_back(sprite);

					// Clear sprite pixels
					sprite.pixels.clear();
				}
			}

			// Set sprite sheet properties
			spriteSheet.widthSheet = imgWidth;
			spriteSheet.heightSheet = imgHeight;
			spriteSheet.widthSprite = widthEachSprite;
			spriteSheet.heightSprite = heightEachSprite;
			spriteSheet.sizeSheet = imgWidth * imgHeight;
			spriteSheet.sizeSprite = widthEachSprite * heightEachSprite;
			spriteSheet.numSpritesX = numSpritesX;
			spriteSheet.numSpritesY = numSpritesY;

			return spriteSheet;
		}

		SpriteBuffer SpriteToFrame(const Sprite& sprite)
		{
			// Check if sprite is empty
			if (sprite.pixels.empty())
			{
				Log("[Converter] Sprite is empty!");
				OutputDebugStringW(L"[Converter] Sprite is empty!");
				return SpriteBuffer();
			}

			// Create frame
			SpriteBuffer frame;
			frame.width = sprite.width;
			frame.height = sprite.height;
			frame.size = sprite.width * sprite.height;
			frame.buffer.resize(sprite.size); // Reserve frame size

			// Create CHAR_INFO
			CHAR_INFO charInfo;

			// Loop through each pixel
			for (size_t i = 0; i < frame.size; ++i)
			{
				charInfo.Char.UnicodeChar = L'\x2588'; // Set character to full block
				charInfo.Attributes = sprite.pixels[i] | (sprite.pixels[i] << 4); // Set color to color index

				frame.buffer[i] = charInfo;
			}

			return frame;
		}

		SpriteBufferSheet SpriteSheetToFrameSheet(const SpriteSheet& spriteSheet)
		{
			// Check if sprite sheet is empty
			if (spriteSheet.sprites.empty())
			{
				Log("[Converter] Sprite sheet is empty!");
				OutputDebugStringW(L"[Converter] Sprite sheet is empty!");
				return SpriteBufferSheet();
			}

			// Create frame sheet
			SpriteBufferSheet frameSheet;
			frameSheet.spriteBuffers.reserve(spriteSheet.sprites.size()); // Reserve frame size
			frameSheet.countSpriteBuffer = spriteSheet.sprites.size();

			// Loop through each sprite
			for (int i = 0; i < frameSheet.countSpriteBuffer; ++i)
			{
				// Convert sprite to frame
				SpriteBuffer frame = SpriteToFrame(spriteSheet.sprites[i]);

				// Add frame to frame sheet
				frameSheet.spriteBuffers.push_back(frame);
			}

			// Set frame sheet properties
			frameSheet.widthSpriteBuffer = spriteSheet.widthSprite;
			frameSheet.heightSpriteBuffer = spriteSheet.heightSprite;
			frameSheet.sizeSpriteBufer = spriteSheet.widthSprite * spriteSheet.heightSprite;

			return frameSheet;
		}
	} // namespace bitmap_converter

	namespace file
	{
		int MakeDirectory(const std::string& directoryPath)
		{
			bool hr = CreateDirectoryA(directoryPath.c_str(), NULL);

			if (hr == 0)
			{
				if (GetLastError() == ERROR_ALREADY_EXISTS)
				{
					Log((std::string("[MakeDirectory] Directory already exists: ") + directoryPath).c_str());
					return 1;
				}
				else if (GetLastError() == ERROR_PATH_NOT_FOUND)
				{
					Log((std::string("[MakeDirectory] Failed to create directory: ") + directoryPath).c_str());
					return -1;
				}
			}
			else {
				Log((std::string("[MakeDirectory] Created directory: ") + directoryPath).c_str());
				return 0;
			}
		}

		// Check if file exists
		bool IsFileExists(const std::string& filePath)
		{
			std::ifstream file(filePath);
			return file.good();
		}

		// Get file name from file path
		std::string GetFileName(const std::string& filePath)
		{
			std::string fileName = filePath;
			size_t pos = fileName.find_last_of("\\/");

			if (pos != std::string::npos)
			{
				fileName = fileName.substr(pos + 1);
			}

			return fileName;
		}

		// Get file extension from file path
		std::vector<std::wstring> GetListFilesInDirectory(const std::string& directoryPath)
		{
			std::vector<std::wstring> files; // List of files
			WIN32_FIND_DATAW findFileData; // File data
			HANDLE hFind = FindFirstFileW(utils::basic_converter::StrToWStr(directoryPath + "/*").c_str(), &findFileData); // Find files in directory

			// Check if directory is empty
			if (hFind == INVALID_HANDLE_VALUE)
			{
				Log((std::string("[GetListFilesInDirectory] Failed to find files in directory: ") + directoryPath).c_str());
				return files;
			}

			do
			{
				// Skip directories
				if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					continue;
				}

				files.push_back(findFileData.cFileName); // Add file name to list
			} while (FindNextFileW(hFind, &findFileData) != 0);

			FindClose(hFind); // Close handle

			return files; // Return list of files
		} // GetListFilesInDirectory
	} // End of namespace file
} // End of namespace utils