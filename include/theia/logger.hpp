#pragma once

#if !defined(SPDLOG_ACTIVE_LEVEL)
#    if defined(NDEBUG)
#        define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#    else
#        define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#    endif
#endif

#include <memory>
#include <spdlog/spdlog.h>

namespace theia {
class Logger {
public:
    static std::shared_ptr<spdlog::logger> &instance();
    static std::vector<spdlog::sink_ptr> &sinks();

private:
    static std::shared_ptr<spdlog::logger> s_logger;

    static void init_();
};
} // namespace theia

#define THEIA_LOG_TRACE(...) SPDLOG_LOGGER_TRACE(theia::Logger::instance(), __VA_ARGS__)
#define THEIA_LOG_INFO(...) SPDLOG_LOGGER_INFO(theia::Logger::instance(), __VA_ARGS__)
#define THEIA_LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(theia::Logger::instance(), __VA_ARGS__)
#define THEIA_LOG_WARN(...) SPDLOG_LOGGER_WARN(theia::Logger::instance(), __VA_ARGS__)
#define THEIA_LOG_ERROR(...) SPDLOG_LOGGER_ERROR(theia::Logger::instance(), __VA_ARGS__)
#define THEIA_LOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(theia::Logger::instance(), __VA_ARGS__)
