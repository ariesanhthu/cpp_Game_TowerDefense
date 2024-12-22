#include "FontManager.h"

#include "FontManager.h"
#include <stdexcept>
#include <iostream>

std::map<std::string, HFONT> FontManager::fonts;
// Constructor
FontManager::FontManager()
{
}

// Destructor
FontManager::~FontManager()
{
    //cleanupFonts();
}

// Singleton instance
FontManager& FontManager::getInstance()
{
    static FontManager instance;
    return instance;
}

// Load a font
HFONT FontManager::loadFont(const std::wstring& fontName, int fontSize, int fontWeight)
{
    HFONT hFont = CreateFontW(
        fontSize,                // Font height
        0,                       // Width
        0,                       // Escapement
        0,                       // Orientation
        fontWeight,              // Weight
        FALSE,                   // Italic
        FALSE,                   // Underline
        FALSE,                   // Strikeout
        DEFAULT_CHARSET,         // Charset
        OUT_DEFAULT_PRECIS,      // Output precision
        CLIP_DEFAULT_PRECIS,     // Clipping precision
        DEFAULT_QUALITY,         // Quality
        DEFAULT_PITCH | FF_SWISS, // Pitch and family
        fontName.c_str()         // Font name
    );

    if (!hFont)
    {
        OutputDebugStringA("Failed to create font\n");
        //std::cerr << "Failed to create font: " << std::wstring(fontName) << std::endl;
    }

    return hFont;
}

// Load fonts for the entire game
void FontManager::loadFontForGame(const std::wstring& fontPath)
{
    // Add font to system memory
    if (AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, NULL) == 0)
    {
        //throw std::runtime_error("Failed to load font file.");
        return;
    }

    fontFilePath = fontPath;

    // Add fonts to the map
    fonts["normal"] = loadFont(L"pixelFont-7-8x14-sproutLands", 24, FW_NORMAL);
    fonts["bold"] = loadFont(L"pixelFont-7-8x14-sproutLands", 24, FW_BOLD);
    fonts["title"] = loadFont(L"pixelFont-7-8x14-sproutLands", 72, FW_BOLD);
}

// Retrieve a font by key
HFONT FontManager::getFont(const std::string& fontKey) const
{
    auto it = fonts.find(fontKey);
    if (it != fonts.end())
    {
        return it->second;
    }
    OutputDebugStringA("Failed to get font\n");
}

// Cleanup loaded fonts
void FontManager::cleanupFonts()
{
    for (auto& font : fonts)
    {
		if (font.second)
            DeleteObject(font.second);
    }
    fonts.clear();

    if (!fontFilePath.empty())
    {
        RemoveFontResourceEx(fontFilePath.c_str(), FR_PRIVATE, NULL);
    }
}
