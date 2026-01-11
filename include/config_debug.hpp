#ifndef CONFIG_DEBUG_HPP
#define CONFIG_DEBUG_HPP

#include <unordered_map>
#include <string>
#include <fstream>

#define DEBUG_MODE  1

class DEBUG_log
{
    public:
        enum LEVEL {
            ERROR = 0,
            WARNING = 1,
            INFO = 2,
            DEBUG = 3 
        };

        static auto set_level(LEVEL level) -> void;
        [[nodiscard]] static auto get_level() -> LEVEL;
        static auto enable_module(const std::string& module) -> void;
        static auto disable_module(const std::string& module) -> void;
        static auto log(const std::string& module,
        LEVEL level, const std::string& message) -> void;

    private:
        #if DEBUG_MODE
            static LEVEL current_level;
            static std::unordered_map<std::string, bool> module_flags;
            static std::ofstream log_file;
        #endif

        static auto open_log_file() -> void;
        static auto close_log_file() -> void;

        [[nodiscard]] static auto format_message(const std::string& module,
        LEVEL level, const std::string& message) -> std::string;
        [[nodiscard]] static constexpr auto level_to_string(LEVEL level)
        noexcept -> const char*; 
        
};

#endif
