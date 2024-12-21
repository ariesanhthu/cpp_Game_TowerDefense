#pragma once

#include <string>
#include <iostream>	
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <cstring>

class Utils {
private: 
	static std::shared_ptr<Utils> instance;

public: 
	static std::shared_ptr<Utils> getInstance() {
		if (instance == nullptr) {
			instance = std::shared_ptr<Utils>(new Utils());
		}
		return instance;
	}

	std::string wstringToString(std::wstring wstr);
	std::wstring stringToWstring(std::string str);
	char* stringToChar(std::string str);

	void createFile(std::string path);
	void createFolder(std::string path);
};

