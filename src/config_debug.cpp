#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
#include "config_debug.hpp"
#include "Utils.hpp"

using std::endl;
using std::unordered_map;
using std::ofstream;

#if DEBUG_MODE
DEBUG_log::LEVEL DEBUG_log::current_level = DEBUG_log::INFO;
std::unordered_map<std::string, bool> DEBUG_log::module_flags;
std::ofstream DEBUG_log::log_file;
#endif

auto DEBUG_log::set_level(LEVEL level) -> void
{
    current_level = level;
}

[[nodiscard]] auto DEBUG_log::get_level() -> LEVEL
{
#if DEBUG_MODE
    return current_level;
#else
    return ERROR;
#endif
}


auto DEBUG_log::enable_module(const std::string& module) -> void
{
    module_flags[module] = true;
}

auto DEBUG_log::disable_module(const std::string& module) -> void
{
    module_flags[module] = false;
}

[[nodiscard]] constexpr auto DEBUG_log::level_to_string(LEVEL level) noexcept -> const char*
{
    switch (level) {
        case LEVEL::ERROR:   return "ERROR";
        case LEVEL::WARNING: return "WARNING";
        case LEVEL::INFO:    return "INFO";
        case LEVEL::DEBUG:   return "DEBUG";
    }
    return "UNKNOWN"; 
}


[[nodiscard]] auto DEBUG_log::format_message(const std::string& module,
LEVEL level, const std::string& message) -> std::string
{
    std::time_t now = std::time(nullptr);
    std::string time = std::ctime(&now);
    time.pop_back();
    std::string formatted_msg = "[" + time +"], " + "[" + module + "], " +
    " [ " + level_to_string(level) + " ] " + "[-" + message + "-]";
    return formatted_msg;
}

auto DEBUG_log::open_log_file() -> void
{
 if (!DEBUG_log::log_file.is_open())
    {
        DEBUG_log::log_file.open("log/debug_log.txt", std::ios::app);
        if (!DEBUG_log::log_file.is_open())
        {
            std::cerr << "Failed to open debug log file!" << std::endl;
            return;
        }
    }
}

auto DEBUG_log::close_log_file() -> void
{
    if (log_file.is_open()) [[likely]]
    {
        log_file.close();
    }
}

auto DEBUG_log::log(const std::string& module,
LEVEL level, const std::string& message) -> void 
{
    #if !DEBUG_MODE
        return;
    #endif

    if (level > current_level) 
    {
        [[unlikely]] return;
    }

    auto it = module_flags.find(module);
    if (it != module_flags.end() && !it->second) [[unlikely]] return;

    open_log_file();
    log_file << format_message(module, level, message) << endl <<endl;
    close_log_file();
}