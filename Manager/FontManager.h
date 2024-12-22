#pragma once

#include <string>
#include <map>
#include <windows.h>
#include <memory>

class FontManager
{
private:
    /*
		Các font hiện tại được sử dụng trong game
        - normal
		- bold
		- title
    
    */
    static std::map<std::string, HFONT> fonts;
    //std::map<std::string, HFONT> fonts; // Lưu trữ các font
    std::wstring fontFilePath;          // Đường dẫn tới file .ttf

    FontManager();
    ~FontManager();

    HFONT loadFont(const std::wstring& fontName, int fontSize, int fontWeight);

public:
    // Singleton instance
    static FontManager& getInstance();

    // Không cho phép copy hoặc gán đối tượng
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    // Tải và lưu font
    void loadFontForGame(const std::wstring& fontPath);
    HFONT getFont(const std::string& fontKey) const;

    // Dọn dẹp tài nguyên
    void cleanupFonts();
};
