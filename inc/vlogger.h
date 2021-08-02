//
// Created by vlad on 02.08.2021.
//

#ifndef LOGGER_LOGGER_H
#define LOGGER_LOGGER_H

#include <filesystem>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

namespace vlogger
{

    enum class LogLevel : int
    {
        INFO,
        WANR,
        ERROR
    };

    enum class LogType : int
    {
        STANDARD_OUTPUT,
        TO_FILE
    };

    class VLogger
    {
    public:
        VLogger();
        VLogger(std::filesystem::path logFile);

        void setLogType(LogType logType);
        void setLogFile(std::filesystem::path logFile);

        void info(std::string message);

    private:

        std::vector<std::string> tokenize(std::string s, std::string del = " ");


        template<typename... Types>
        void log(LogLevel logLevel, std::string message, Types... args);

        std::vector<std::string> toString();

        template<typename T>
        std::string toStringImpl(const T& t);

        template<typename P1, typename ... Param>
        std::vector<std::string> toString(const P1& p1, const Param& ... param);



        std::string getHeaderLogLevel(LogLevel logLevel);

        LogType mLogType;
        std::filesystem::path mLogFile;

    };

}


#endif //LOGGER_LOGGER_H
