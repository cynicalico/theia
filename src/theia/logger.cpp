#include "theia/logger.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> theia::Logger::s_logger{nullptr};

std::shared_ptr<spdlog::logger> &theia::Logger::instance() {
    if (!s_logger) {
        init_();
    }
    return s_logger;
}

std::vector<spdlog::sink_ptr> &theia::Logger::sinks() { return s_logger->sinks(); }

void theia::Logger::init_() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("theia.log", true);

    s_logger = std::make_shared<spdlog::logger>("theia", spdlog::sinks_init_list{console_sink, file_sink});
    s_logger->set_level(spdlog::level::trace);
}
