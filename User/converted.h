#pragma once

#include <string>
#include <locale>
#include <codecvt>

namespace towerdefense {
    inline std::string wstringToString(const std::wstring& wstr) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.to_bytes(wstr);
    }
}