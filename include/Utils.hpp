#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include "config_debug.hpp"

class NumUtil
{
    public:
        [[nodiscard]] auto intINPUT(const std::string& message) const -> int;
        [[nodiscard]] auto dblINPUT(const std::string& message) const -> double;
        auto isNum(const std::string& input) -> void;
    
    protected:
        static DEBUG_log report;

};

class StrUtil : public NumUtil
{
    public:
        //returns a lowerd character
        [[nodiscard]] auto tolower(char& input) -> char;
        //trims whitespaces
        [[nodiscard]] auto trim(std::string& input) -> std::string;
        //tokenize words and store in a vector
        [[nodiscard]] auto tokenize(const std::string& input) -> std::vector<std::string>;

        //return a cleaned string(punctuations removed)
        [[nodiscard]] auto normalizeword(std::string& input) -> std::string;
        //log a invalid token to debug_log.txt
        [[nodiscard]] auto isValidToken(std::vector<std::string>& tokens) const -> bool;
};

class DF_Util : public StrUtil
{
    public:
        [[nodiscard]] auto datafileExits() const -> std::string;
        auto validateDataFolder() -> void;
        auto scanDataFolder(std::vector<std::string>& filename,
        std::vector<std::string>& filepath) -> void;

};

class Utilities : public DF_Util{
    public:
        [[nodiscard]] auto current_time() -> std::string;
        Utilities();
        ~Utilities();

};

#endif