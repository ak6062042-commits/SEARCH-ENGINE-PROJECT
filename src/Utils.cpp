#include <cctype>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <limits>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "config_debug.hpp"
#include "Utils.hpp"


namespace fs = std::filesystem;
using std::endl;
using std::cout;
using std::cin;

DEBUG_log NumUtil::report;
Utilities::Utilities() = default;
Utilities::~Utilities() = default;

//===========================================================================================//

[[nodiscard]] auto NumUtil::intINPUT(const std::string& message) const -> int
{
    int input;
    cout << message;
    cin >> input;
    
    if(cin.fail()) [[unlikely]]
    {
    DEBUG_log::LEVEL input_level = DEBUG_log::WARNING;
    report.enable_module("INTEGER INPUT");
    report.log("INTEGER INPUT", input_level, " WRONG::DATA_TYPE->FOR INTEGER INPUT");
    report.disable_module("INTEGER INPUT");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return -1;
    } 

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

[[nodiscard]] auto NumUtil::dblINPUT(const std::string& message) const -> double
{
    double input;
    cout << message;
    cin >> input;
    
    if(cin.fail()) [[unlikely]]
    {
    DEBUG_log::LEVEL input_level = DEBUG_log::WARNING;
    report.enable_module("DOUBLE INPUT");
    report.log("DOUBLE INPUT", input_level, " WRONG::DATA_TYPE->FOR DOUBLE INPUT");
    report.disable_module("DOUBLE INPUT");
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return -1.0;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return input;
}

auto NumUtil::isNum(const std::string& input) -> void
{
    for(const auto& Digitchr:input)
    { 
        if(std::isdigit(static_cast<unsigned char>(Digitchr))) [[likely]]
        {
            DEBUG_log::LEVEL input_level = DEBUG_log::ERROR;
            report.enable_module("INT+STR");
            report.log("INT+STR", input_level, " ERROR::INTEGER_IN->EXPECTED PURE STRING");
            report.disable_module("INT+STR");
            break;
        }
    }
}

//===========================================================================================//

[[nodiscard]] auto DF_Util::datafileExits() const -> std::string
{
    std::string datafolder;
    if(fs::exists("data")) datafolder = "data";
    else if(fs::exists("../data")) datafolder = "../data";
    else return ("DATA NOT FOUND");
    return datafolder;
}

auto DF_Util::validateDataFolder() -> void 
{
    std::string datafolder = datafileExits();
    if( datafolder == "DATA NOT FOUND")
    {
        DEBUG_log::LEVEL input_level = DEBUG_log::ERROR;
        report.enable_module("DATA-FOLDER");
        report.log("DATA-FOLDER", input_level, " ERROR::DATA_FOLDER->!!!NOT FOUND!!!");
        report.disable_module("DATA-FOLDER");
        return;
    }
}

auto DF_Util::scanDataFolder(std::vector<std::string>& filename,
std::vector<std::string>& filepath) -> void
{
    std::string datafolder = datafileExits();
    validateDataFolder();
    for ( const auto& entry : fs::directory_iterator(datafolder))
    {
        if(entry.is_regular_file()){
            filepath.push_back(entry.path().string());
            filename.push_back(entry.path().filename().string());
        }
    }
}

//===========================================================================================//

[[nodiscard]] auto StrUtil::tolower(char& input) -> char
{
    return static_cast<char>(std::tolower(static_cast<unsigned char>(input)));
}


[[nodiscard]] auto StrUtil::trim(std::string& input) -> std::string
{
    if (input.empty()) return input;
    
    std::size_t start = 0;
    std::size_t end = input.length() - 1;

    while (start < input.length() && std::isspace(static_cast<unsigned char>(input[start]))) ++start;
    if (start == input.length()) [[unlikely]] return "";

    while (end > start && std::isspace(static_cast<unsigned char>(input[end])))--end;
    return input.substr(start, end - start + 1);
}

[[nodiscard]] auto StrUtil::tokenize(const std::string& input) -> std::vector<std::string>
{
    std::stringstream ss(input);
    std::string words;
    std::vector<std::string> tokens;

    while( ss >> words)
    {
        tokens.push_back(words);
    }
    return tokens;
}

[[nodiscard]] auto StrUtil::normalizeword(std::string& input) -> std::string
{
    std::string cleaned = "";
    for(char ch : input){
        ch = StrUtil::tolower(ch);
        if((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) [[likely]] cleaned += ch;
        else continue;
    }
    return cleaned;
}

[[nodiscard]] auto StrUtil::isValidToken(std::vector<std::string>& tokens ) const -> bool
{
    size_t tokens_size = tokens.size();
    for (size_t i = 0; i < tokens_size; i++)
    {
        for(const auto& ch : tokens[i]){
            if((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) [[likely]] continue;
            else{
                DEBUG_log::LEVEL input_level = DEBUG_log::WARNING;
                report.enable_module("TOKEN");
                report.log("TOKEN", input_level, " ERROR::TOKEN->!!!NOT CLEANED CORRECTLY!!!");
                report.disable_module("TOKEN");
                return false;
            }
        }
    }
    return true; 
}


//===========================================================================================//

[[nodiscard]] auto Utilities::current_time() -> std::string
{
    std::time_t now = std::time(nullptr);
    std::string time = std::ctime(&now);
    time.pop_back();
    return time;
}