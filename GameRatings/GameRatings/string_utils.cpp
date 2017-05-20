#include "string_utils.h"
#include <sstream>
#include <algorithm>
using namespace std;

string StringUtils::RemoveExtraSpaces(const string &sentence) {
    stringstream sstream;
    string str, newoutput;
    sstream << sentence;
    while (sstream >> str) {
        newoutput += (str + ' ');
    }
    return newoutput.substr(0, newoutput.length() - 1);
}

string StringUtils::ToUpper(const string& s) {
    string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

string StringUtils::Trim(const string& s) {
    string result = s;
    size_t p = result.find_first_not_of(" \t");
    if (string::npos != p) {
        result.erase(0, p);
    }
    p = result.find_last_not_of(" \t");
    if (string::npos != p) {
        result.erase(p + 1);
    }
    return result;
}