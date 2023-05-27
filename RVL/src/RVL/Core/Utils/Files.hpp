#ifndef RVL_FILES_HPP
#define RVL_FILES_HPP

#include "Core/Core.hpp"

namespace rvl {
namespace Utils
{
    std::vector<std::string> SplitStr(const std::string& str, char sep);

    std::string GetTextFromFile(const std::string& path);

    void SaveTextToFile(const char* path, const std::string& text);

    void DeleteLineFromFile(const std::string& path, int n);
}
}

#endif
