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
    }
    
} 


#endif
