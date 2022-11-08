#include "Utilities.h"
#include <algorithm>

namespace cool 
{
    std::string ToLower(const std::string& str)
    {
        std::string lower = str;

        std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {return std::tolower(c); });

        return lower;
    }

    std::string ToUpper(const std::string& str)
    {
        std::string upper = str;

        std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) {return std::toupper(c); });

        return upper;
    }

    bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
    {
        if (str1.length() != str1.length())
        {
            return false;
        }
        if (!std::equal(str1.begin(), str1.end(), str2.begin(), str2.end()))
        {
            return false;
        }
    }
    
}

