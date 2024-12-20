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
	std::string wstringToString(std::wstring wstr);
	std::wstring stringToWstring(std::string str);
	char* stringToChar(std::string str);

	void createFile(std::string path);
	void createFolder(std::string path);
};

