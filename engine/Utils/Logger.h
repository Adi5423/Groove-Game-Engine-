#pragma once

#include <string>

namespace Groove {

    enum class LogLevel {
        Info,
        Warning,
        Error,
        Debug
    };

    class Logger {
    public:
        static void Init(const std::string& logFilePath = "");

        static void Info(const std::string& message);
        static void Warning(const std::string& message);
        static void Error(const std::string& message);
        static void Debug(const std::string& message);

        static void Shutdown();

    private:
        static void Log(const std::string& message, LogLevel level);
    };
}
