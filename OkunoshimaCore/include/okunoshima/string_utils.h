#ifndef string_utils_h
#define string_utils_h

#include <string>
#include <algorithm>
#include <functional>
#include <locale>

namespace okunoshima
{
    static inline void clean(std::string &str)
    {
        str.erase(std::remove_if(str.begin(), str.end(), [](char c) {
            return c == '\r' || c == '\n';
        }));
    }
    
    static inline std::string cleaned(std::string str)
    {
        clean(str);
        return str;
    }
    
    static inline void ltrim(std::string &s, const char &c) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::bind(std::not_equal_to<char>(), c,  std::placeholders::_1)));
    }
    
    static inline void rtrim(std::string &s, const char &c) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::bind(std::not_equal_to<char>(), c, std::placeholders::_1)).base(), s.end());
    }
    
    static inline void trim(std::string &s, const char &c) {
        ltrim(s, c);
        rtrim(s, c);
    }
    
    static inline std::string ltrimmed(std::string s, const char &c) {
        ltrim(s, c);
        return s;
    }
    
    static inline std::string rtrimmed(std::string s, const char &c) {
        rtrim(s, c);
        return s;
    }
    
    static inline std::string trimmed(std::string s, const char &c) {
        trim(s, c);
        return s;
    }
}

#endif
