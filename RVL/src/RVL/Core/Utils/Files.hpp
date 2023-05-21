#ifndef RVL_FILES_HPP
#define RVL_FILES_HPP

#include "Core/Core.hpp"

namespace rvl
{
    namespace utils
    {
        static std::string GetTextFromFile(const std::string& path)
        {
            std::ifstream file;
            file.open(path);
            
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
