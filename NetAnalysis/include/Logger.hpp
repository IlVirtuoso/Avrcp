#pragma once
#include <fstream>
#include <memory>
#include <ostream>
#include <string>

namespace NetAnalysis
{
    class Logger
    {
      private:
        std::ofstream &_logFile;

        Logger(std::string fileName);

      public:
        static Logger &Instance();
        void TraceInformation(std::string message);
        Logger &operator<<(std::string message);
        Logger &operator<<(const char *message);
        template <typename T> Logger &operator<<(const T &elem)
        {
            TraceInformation(std::to_string(elem));
            return *this;
        }

        void endl();
    };

    static Logger &log = Logger::Instance();
} // namespace NetAnalysis