// in src/core/FileWriter.cpp
#include "core/FileWriter.hpp"
#include "io/FileSystem.hpp"  // Reuse EnsureDirectory()

#include <cstdio>
#include <stdexcept>
#include <sstream>
#include <iomanip>

namespace Groove {
    namespace Core {

        bool FileWriter::WriteText(const std::string& filepath, const std::string& content) {
            FILE* file = fopen(filepath.c_str(), "w");
            if (!file) return false;
            fwrite(content.c_str(), 1, content.size(), file);
            fclose(file);
            return true;
        }

        bool FileWriter::AppendText(const std::string& filepath, const std::string& content) {
            FILE* file = fopen(filepath.c_str(), "a");
            if (!file) return false;
            fwrite(content.c_str(), 1, content.size(), file);
            fclose(file);
            return true;
        }

        bool FileWriter::EnsureFilePath(const std::string& filepath) {
            size_t lastSlash = filepath.find_last_of("/\\");
            if (lastSlash == std::string::npos) return true;
            std::string directory = filepath.substr(0, lastSlash);
            return Groove::IO::EnsureDirectory(directory);
        }

        //std::string FileWriter::GenerateTimestampedFilename(const std::string& prefix, const std::string& ext) {
        //    std::time_t now = std::time(nullptr);
        //    std::tm* t = std::localtime(&now);

        //    std::ostringstream oss;
        //    oss << prefix << "_"
        //        << std::put_time(t, "%Y-%m-%d_%H-%M-%S")
        //        << "." << ext;
        //    return oss.str();

    } // namespace Core
} // namespace Groove
