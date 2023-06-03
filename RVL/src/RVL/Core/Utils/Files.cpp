#include "Files.hpp"
#include "Core/Core.hpp"

namespace Rvl 
{
    std::vector<std::string> Utils::SplitStr(const std::string& str, char sep)
    {
        std::vector<std::string> strings;

        int startIndex = 0, endIndex = 0;
        
        for (int i = 0; i <= str.size(); i++) 
        {
            if (str[i] == sep || i == str.size()) 
            {
                endIndex = i;
                std::string temp;
                temp.append(str, startIndex, endIndex - startIndex);
                strings.push_back(temp);
                startIndex = endIndex + 1;
            }
        }
        
        return strings;
    }

    std::string Utils::GetTextFromFile(const std::string& path)
    {
        std::ifstream file (path, std::ios::in);
        
        if (!file.is_open())
            throw Error("failed to load file: " + path, RVL_INTERNAL_ERROR);

        std::string source;
        std::string line;

        while (std::getline(file, line))
        {
            line.push_back('\n');
            source.append(line);
        }

        file.close();

        return source;
    }

    void Utils::SaveTextToFile(const char* path, const std::string& text)
    {
        std::ofstream file (path, std::ios::out);

        if (!file.is_open())
            throw Error("problem occured while saving data to file", RVL_INTERNAL_ERROR);

        file << text;

        file.close();
    }

    void Utils::DeleteLineFromFile(const std::string& path, int n)
    {
        std::string text = GetTextFromFile(path);

        auto lines = SplitStr(text, '\n');

        std::fstream file (path, std::ios::out | std::ios::trunc);

        if (!file.is_open())
            throw Error("problem occured while deleting line from file: " + path, RVL_INTERNAL_ERROR);

        std::string source;

        for (int i = 0; i < lines.size(); i++)
        {
            if (i == n)
                continue;

            source.append(lines[i] + "\n");
        }

        source.pop_back();

        file << source;

        file.close();
    }
} 
