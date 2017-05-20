#pragma once
#include <string>

namespace StringUtils {

    std::string RemoveExtraSpaces(const std::string &sentence);

    std::string ToUpper(const std::string& s);

    std::string Trim(const std::string& s);
}