#pragma once

#include <string>

namespace Groove {
    namespace Core {

        class FileWriter {
        public:
            // Create a file and write content into it
            static bool WriteText(const std::string& filepath, const std::string& content);

            // Append text at the end of an existing file
            static bool AppendText(const std::string& filepath, const std::string& content);

            // Create directories leading up to a file path
            static bool EnsureFilePath(const std::string& filepath);

            //std::string GenerateTimestampedFilename(const std::string& prefix, const std::string& ext);

        };

    } // namespace Core
} // namespace Groove
