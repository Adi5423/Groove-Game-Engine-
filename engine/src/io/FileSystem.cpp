// engine/src/io/FileSystem.cpp
#include "io/FileSystem.hpp"

#include <cstdio>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <cstring>

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <dirent.h>
    #include <unistd.h>
#endif
#include <stdexcept>

// Use C++98/99 namespace syntax
namespace Groove {
namespace IO {

    std::string ReadFile(const std::string& filepath) {
        FILE* file = fopen(filepath.c_str(), "rb");
        if (!file) throw std::runtime_error("Cannot open file: " + filepath);

        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        std::string result(size, '\0');
        fread(&result[0], 1, size, file); // Use result's data directly
        fclose(file);
        return result;
    }

    bool WriteFile(const std::string& filepath, const std::string& content) {
        FILE* file = fopen(filepath.c_str(), "wb");
        if (!file) return false;

        fwrite(content.data(), 1, content.size(), file);
        fclose(file);
        return true;
    }

    bool FileExists(const std::string& filepath) {
        struct stat buffer;
        return (stat(filepath.c_str(), &buffer) == 0);
    }

    bool EnsureDirectory(const std::string& path) {
    #if defined(_WIN32)
        return CreateDirectoryA(path.c_str(), nullptr) || GetLastError() == ERROR_ALREADY_EXISTS;
    #else
        return mkdir(path.c_str(), 0755) == 0 || errno == EEXIST;
    #endif
    }

    std::vector<std::string> ListFiles(const std::string& folder) {
        std::vector<std::string> result;

    #if defined(_WIN32)
        std::string searchPath = folder + "\\*.*";
        WIN32_FIND_DATAA fd;
        HANDLE hFind = FindFirstFileA(searchPath.c_str(), &fd);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    result.push_back(fd.cFileName);
                }
            } while (FindNextFileA(hFind, &fd));
            FindClose(hFind);
        }
    #else
        DIR* dir = opendir(folder.c_str());
        if (dir) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_type == DT_REG) {
                    result.push_back(entry->d_name);
                }
            }
            closedir(dir);
        }
    #endif
        return result;
    }

} // namespace IO
} // namespace Groove
