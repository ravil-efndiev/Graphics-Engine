#ifndef RVL_FILES_HPP
#define RVL_FILES_HPP

#include "Core/Core.hpp"

namespace rvl
{
    namespace utils
    {
        static std::string GetTextFromFile(const std::string& path)
        {
            std::ifstream file (path, std::ios::in);
            
            if (!file.is_open())
                throw Error("failed to load file", RVL_INTERNAL_ERROR);

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

        static void SaveTextToFile(const char* path, const std::string& text)
        {
            std::ofstream file (path, std::ios::out);

            if (!file.is_open())
                throw Error("problem occured while saving data to file", RVL_INTERNAL_ERROR);

            file << text;

            file.close();
        }

        static std::vector<std::string> SplitStr(const std::string& str, char sep)
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
    }
    
} 


#endif
