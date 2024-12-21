#include "Utils.h"

std::shared_ptr<Utils> Utils::instance = nullptr;

std::string Utils::wstringToString(std::wstring wstr) {
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
	std::string str(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), &str[0], size_needed, NULL, NULL);
	return str;
}

std::wstring Utils::stringToWstring(std::string str) {
	std::wstring wstr(str.begin(), str.end());
	return wstr;
}

char* Utils::stringToChar(std::string str) {
	char* cstr = new char[str.length() + 1];
	strcpy_s(cstr, str.length() + 1, str.c_str());
	return cstr;
}

void Utils::createFile(std::string path) {
	std::ofstream file(path);
	file.close();
}

void Utils::createFolder(std::string path) {
	std::wstring wpath(path.begin(), path.end());

	if (CreateDirectory(wpath.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS) {
		std::cout << "Directory created or already exists." << std::endl;
	}
	else {
		std::cout << "Failed to create directory. Error code: " << GetLastError() << std::endl;
	}
}

