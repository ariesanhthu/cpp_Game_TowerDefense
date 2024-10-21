#include "Logger.h"

std::ofstream logFile; // Define log file

// Get current date
inline static std::string GetLogDate()
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	char date[26];
	sprintf_s(date, "%02d_%02d_%02d", time.wYear, time.wMonth, time.wDay);

	return date;
}

// Get current time
inline static std::string GetLogTime()
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	char timeString[26];
	sprintf_s(timeString, "%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);

	return timeString;
}

//	Get count line of file
static UINT GetCountLines(const std::string& file)
{
	std::ifstream fileStream(file);
	UINT count = 0;
	std::string line;

	while (std::getline(fileStream, line))
	{
		count++;
	}

	return count;
}

// Check if file exists
static bool IsFileExists(const std::string& file)
{
	std::ifstream fileStream(file);
	return fileStream.good();
}

// Get error message
std::string GetError(const std::string& message, const std::string& file, const std::string& line)
{
	return "Error: " + message + " in file " + file + " at line " + line;
}

// Throw error
void ThrowOnError(const std::string& message, const std::string& file, const std::string& line)
{
	throw std::runtime_error("Error: " + message + " in file " + file + " at line " + line);
}

// Initialize log file
void InitLogFile()
{
	try {
		// Create log folder directory
		bool result = CreateDirectoryA(kLogFolderPath.c_str(), NULL);

		// Check if log folder directory created successfully, 0 - not created, 1 - created
		if (result == 0)
		{
			if (GetLastError() == ERROR_PATH_NOT_FOUND)
			{
				OutputDebugStringA("Log folder directory not found!\n");
			}
			else if (GetLastError() == ERROR_ALREADY_EXISTS)
			{
				OutputDebugStringA("Log folder directory already exists!\n");
			}
		}
		else if (result == 1)
		{
			OutputDebugStringA("Log folder directory created successfully!\n");
		}

		// Delete log files older than 3 days
		WIN32_FIND_DATAA findData{};
		HANDLE hFind = FindFirstFileA((kLogFolderPath + "*").c_str(), &findData);

		if (hFind != INVALID_HANDLE_VALUE)
		{
			do {
				if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				{
					std::string filePath = kLogFolderPath + findData.cFileName;
					OutputDebugStringA(("File Path: " + filePath + "\n").c_str());

					FILETIME lastWriteTime = findData.ftLastWriteTime;
					SYSTEMTIME st;
					FileTimeToSystemTime(&lastWriteTime, &st); // Convert file time to system time

					std::tm tm;
					tm.tm_sec = st.wSecond;
					tm.tm_min = st.wMinute;
					tm.tm_hour = st.wHour;
					tm.tm_mday = st.wDay;
					tm.tm_mon = st.wMonth - 1;
					tm.tm_year = st.wYear - 1900;
					std::time_t fileTime = std::mktime(&tm); // Convert system time to time_t

					// Get current time
					std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

					// Calculate difference between current time and last write time
					std::time_t diff = currentTime - fileTime;

					if (diff > 3 * 24 * 60 * 60)
					{
						DeleteFileA(filePath.c_str());

						OutputDebugStringA(("File deleted: " + filePath + "\n").c_str());
					}
				}
			} while (FindNextFileA(hFind, &findData) != 0);
		}

		FindClose(hFind); // Close handle

		// Set log file name
		logFileName = "Log_" + GetLogDate() + ".txt";

		// Variable to store count lines of log file
		UINT count = 0;

		// Maximum 10000 log files
		for (UINT i = 1; i < 10000; ++i)
		{
			// Get count lines of log file
			count = GetCountLines(kLogFolderPath + logFileName);

			OutputDebugStringA(("File Name: " + logFileName + "\n").c_str());
			OutputDebugStringA(("Count: " + std::to_string(count) + "\n").c_str());

			// If log file exists and has more than 1000 lines, create new log file
			if (IsFileExists(kLogFolderPath + logFileName) && count > 1000)
			{
				logFileName = "Log_" + GetLogDate() + "-" + std::to_string(i) + ".txt";
			}
			else
			{
				break;
			}
		}

		OutputDebugStringA(("Dir: " + kLogFolderPath + logFileName + "\n").c_str());

		// Create new log file mode append
		logFile.open(kLogFolderPath + logFileName, std::ios::app);

		if (logFile.is_open())
		{
			logFile << "========================================" << std::endl;
			logFile << "Log file created on " << GetLogTime() << std::endl;
			logFile << "========================================" << std::endl;
		}
		else
		{
			OutputDebugStringA("Log file is not open!\n");
		}
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		OutputDebugStringA("\n");
		MessageBoxA(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
	}
}

// Log message
void Log(const std::string& message)
{
	try {
		if (logFile.is_open())
		{
			logFile << GetLogTime() << " | " << message << std::endl;
		}
		else
		{
			OutputDebugStringA("Log file is not open!\n");
		}
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		OutputDebugStringA("\n");
	}
}

void Log(const std::wstring& wMessage)
{
	try {
		if (logFile.is_open())
		{
			logFile << GetLogTime() << " | " << std::string(wMessage.begin(), wMessage.end()) << std::endl;
		}
		else
		{
			OutputDebugStringA("Log file is not open!\n");
		}
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		OutputDebugStringA("\n");
	}

}

// Clear log file
void ClearLogFile()
{
	try {
		logFile.open(kLogFolderPath + logFileName, std::ios::trunc);

		if (logFile.is_open())
		{
			logFile.clear();
		}
		else
		{
			OutputDebugStringA("Log file is not open!\n");
		}
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		OutputDebugStringA("\n");
	}
}

// Delete log file
void DeleteLogFile()
{
	try {
		if (DeleteFileA((kLogFolderPath + logFileName).c_str()))
		{
			OutputDebugStringA("Log file deleted successfully!\n");
		}
		else
		{
			OutputDebugStringA("Log file not deleted!\n");
		}
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		OutputDebugStringA("\n");
	}
}
