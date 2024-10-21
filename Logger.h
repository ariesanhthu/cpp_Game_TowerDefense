#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

static const std::string kLogFolderPath = "Logs/";
static std::string logFileName;
extern std::ofstream logFile;

inline static std::string GetLogDate();
inline static std::string GetLogTime();

static UINT GetCountLines(const std::string& file);
static bool IsFileExists(const std::string& file);

std::string GetError(const std::string& message, const std::string& file, const std::string& line);
void ThrowOnError(const std::string& message, const std::string& file, const std::string& line);

void InitLogFile(); // create log file
void Log(const std::string& message); // for ascii strings
void Log(const std::wstring& wMessage); // for unicode strings
void ClearLogFile(); // clear log file
void DeleteLogFile(); // delete log file
