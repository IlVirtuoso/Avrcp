#include "Logger.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>

namespace NetAnalysis
{
    static std::unique_ptr<Logger> _instance;

    Logger::Logger(std::string filename) : _logFile{*new std::ofstream("./log/" + filename)}
    {
    }

    Logger &Logger::operator<<(std::string message)
    {
        this->TraceInformation(message);
        return *this;
    }

    Logger &Logger::operator<<(const char *message)
    {
        TraceInformation(std::string(message));
        return *this;
    }

    void Logger::TraceInformation(std::string message)
    {
        _logFile.write(message.c_str(), message.size());
        std::cout << "[INFO]" << message << std::endl;
    }

    Logger &Logger::Instance()
    {
        if (_instance == nullptr)
        {
            Logger *instance = new Logger("./log.txt");
            _instance = std::unique_ptr<Logger>(instance);
        }
        return *_instance.get();
    }

    void Logger::endl()
    {
        _logFile << std::endl;
    }

} // namespace NetAnalysis