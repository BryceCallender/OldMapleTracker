#include "logger.h"

std::shared_ptr<spdlog::logger> Logger::logger;

void Logger::init()
{
    logger = spdlog::basic_logger_mt("trackerlogger", "logs/tracker-log.txt");
}
