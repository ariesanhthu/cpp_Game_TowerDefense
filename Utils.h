#pragma once

#include <string>
#include <iostream>	
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <cstring>

class Utils {
public: 

	static std::string wstringToString(std::wstring wstr);
	static std::wstring stringToWstring(std::string str);
	static char* stringToChar(std::string str);

	static void createFile(std::string path);
	static void createFolder(std::string path);
};

