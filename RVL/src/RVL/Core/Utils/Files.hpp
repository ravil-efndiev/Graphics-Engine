#pragma once

#include "Core/Core.hpp"

namespace Rvl {
namespace Utils
{
    std::vector<std::string> SplitStr(const std::string& str, char sep);

    std::string GetTextFromFile(const std::string& path);

    void SaveTextToFile(const char* path, const std::string& text);

    void DeleteLineFromFile(const std::string& path, int n);
}
}

