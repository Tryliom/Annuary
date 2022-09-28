#include "StringUtility.h"
#include <regex>


namespace StringUtility
{
    std::string ltrim(const std::string& s) {
        return std::regex_replace(s, std::regex("^\\s+"), "");
    }

    std::string rtrim(const std::string& s) {
        return std::regex_replace(s, std::regex("\\s+$"), "");
    }

    std::string trim(const std::string& s) {
        return ltrim(rtrim(s));
    }
}
