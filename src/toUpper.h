#ifndef TOUPPER_H
#define TOUPPER_H

#include <string>
#include <algorithm>

inline std::string toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

#endif
