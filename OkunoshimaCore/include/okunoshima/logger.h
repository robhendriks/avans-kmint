#ifndef logger_h
#define logger_h

#include <string>
#include <chrono>
#include <iomanip>
#include <ctime>

namespace okunoshima
{
    namespace logger
    {
        enum log_level
        {
            INFO,
            WARNING,
            ERROR
        };
        
        inline std::string from(log_level level)
        {
            switch (level) {
                case INFO:
                    return "INFO";
                case WARNING:
                    return "WARNING";
                case ERROR:
                    return "ERROR";
            }
        }
        
        inline void log(log_level level, const std::string& message)
        {
            auto now = std::chrono::system_clock::now();
            auto now_c = std::chrono::system_clock::to_time_t(now);
            
            std::cout << std::put_time(std::localtime(&now_c), "%T") << " [" << from(level) << "] " << message << std::endl;
        }
        
        inline void info(const std::string& message)
        {
            log(INFO, message);
        }
        
        inline void warn(const std::string& message)
        {
            log(WARNING, message);
        }
        
        inline void error(const std::string& message)
        {
            log(ERROR, message);
        }
    }
}

#endif
