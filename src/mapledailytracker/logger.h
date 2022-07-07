#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

class Logger
{
public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& getLogger() { return logger; }
private:
    static std::shared_ptr<spdlog::logger> logger;
};

#endif // LOGGER_H
