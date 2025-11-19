#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace theia {
class Logger {
public:
    static void init();
    static std::shared_ptr<spdlog::logger> &get_logger();
    static std::vector<spdlog::sink_ptr> &get_sinks();

private:
    static std::shared_ptr<spdlog::logger> s_logger;
};
} // namespace theia

#define THEIA_LOG_TRACE(...) SPDLOG_LOGGER_TRACE(theia::Logger::get_logger(), __VA_ARGS__)
#define THEIA_LOG_INFO(...) SPDLOG_LOGGER_INFO(theia::Logger::get_logger(), __VA_ARGS__)
#define THEIA_LOG_WARN(...) SPDLOG_LOGGER_WARN(theia::Logger::get_logger(), __VA_ARGS__)
#define THEIA_LOG_ERROR(...) SPDLOG_LOGGER_ERROR(theia::Logger::get_logger(), __VA_ARGS__)
#define THEIA_LOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(theia::Logger::get_logger(), __VA_ARGS__)
