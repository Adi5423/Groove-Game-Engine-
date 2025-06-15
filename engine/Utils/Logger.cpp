#include "Logger.h"
#include <iostream>
#include <fstream>
#include <windows.h>

namespace Groove {

    static std::ofstream s_LogFile;
    static bool s_LogToFile = false;

    void Logger::Init(const std::string& logFilePath) {
        if (!logFilePath.empty()) {
            s_LogFile.open(logFilePath, std::ios::out | std::ios::trunc);
            s_LogToFile = s_LogFile.is_open();
        }
    }

    void Logger::Shutdown() {
        if (s_LogToFile) {
            s_LogFile.close();
        }
    }

    void Logger::Info(const std::string& message)    { Log(message, LogLevel::Info); }
    void Logger::Warning(const std::string& message) { Log(message, LogLevel::Warning); }
    void Logger::Error(const std::string& message)   { Log(message, LogLevel::Error); }
    void Logger::Debug(const std::string& message)   { Log(message, LogLevel::Debug); }

    void Logger::Log(const std::string& message, LogLevel level) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        switch (level) {
            case LogLevel::Info:
                SetConsoleTextAttribute(hConsole, 7); // Light gray
                std::cout << "[INFO] ";
                break;
            case LogLevel::Warning:
                SetConsoleTextAttribute(hConsole, 6); // Yellow
                std::cout << "[WARNING] ";
                break;
            case LogLevel::Error:
                SetConsoleTextAttribute(hConsole, 12); // Red
                std::cout << "[ERROR] ";
                break;
            case LogLevel::Debug:
                SetConsoleTextAttribute(hConsole, 9); // Blue
                std::cout << "[DEBUG] ";
                break;
        }

        std::cout << message << std::endl;
        SetConsoleTextAttribute(hConsole, 7); // Reset

        if (s_LogToFile) {
            switch (level) {
                case LogLevel::Info:    s_LogFile << "[INFO] "; break;
                case LogLevel::Warning: s_LogFile << "[WARNING] "; break;
                case LogLevel::Error:   s_LogFile << "[ERROR] "; break;
                case LogLevel::Debug:   s_LogFile << "[DEBUG] "; break;
            }
            s_LogFile << message << std::endl;
        }
    }
}
