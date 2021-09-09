//
// Created by vlad on 02.08.2021.
//

#include "vlogger.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <sstream>

namespace vlogger
{

    static const std::string kDelimiter = "{}";

    VLogger::VLogger() :
        mLogType(LogType::STANDARD_OUTPUT)
    {
    }

    VLogger::VLogger(std::filesystem::path logFile) :
        mLogType(LogType::TO_FILE)
    {
    }

    void VLogger::setLogFile(std::filesystem::path logFile)
    {
        mLogFile = logFile;
    }

    void VLogger::setLogType(LogType logType)
    {
        mLogType = logType;
    }

    std::vector<std::string> VLogger::tokenize(std::string s, std::string del)
    {
        std::vector<std::string> tokenized;

        int start = 0;
        int end = s.find(del);
        while (end != -1) {
            tokenized.push_back(s.substr(start, end - start));
            start = end + del.size();
            end = s.find(del, start);
        }
        tokenized.push_back(s.substr(start, end - start));
        return tokenized;
    }

    std::string VLogger::getHeaderLogLevel(LogLevel logLevel)
    {
        switch (logLevel)
        {
            case LogLevel::INFO:
            {
                return "Info ";
            }
            case LogLevel::WANR:
            {
                return "Info ";
            }
            case LogLevel::ERROR:
            {
                return "Info ";
            }

            default:
            {
                throw std::invalid_argument("Unknown log level");
            }
        }
    }
    template<typename... Types>
    void VLogger::log(LogLevel logLevel, std::string message, Types... args)
    {
        std::string NowTime;
        std::time_t now;
        struct tm nowLocal;
        now = time(NULL); 
        nowLocal =* localtime(&now);
        std::stringstream ss;
        ss << nowLocal.tm_hour << ':' << nowLocal.tm_min << ':' << nowLocal.tm_sec << ' ';
        std::string messageToLog = "";
        messageToLog.append(ss.str());
        messageToLog.append(getHeaderLogLevel(logLevel));

        std::vector<std::string> tokenizedMessage = tokenize(message, kDelimiter);
        std::vector<std::string> argsAsString = toString(args...);

        if(argsAsString.size() == tokenizedMessage.size()-1)
        {
            for (int i = 0; i < tokenizedMessage.size()-1; i++)
            {
                messageToLog.append(tokenizedMessage[i]);
                messageToLog.append(argsAsString[i]);
            }
            messageToLog.append(tokenizedMessage[tokenizedMessage.size()-1]);
            std::cout << messageToLog << std::endl;
        }
        else
        {
            throw std::runtime_error(
                "Logger failed to tokenized the message, you may have entered to many/less format arguments");
        }

    }

    std::vector<std::string> VLogger::toString()
    {
        return {};
    }

    template<typename T>
    std::string VLogger::toStringImpl(const T& t)
    {
        std::stringstream ss;
        ss << t;
        return ss.str();
    }

    template<typename P1, typename ... Param>
    std::vector<std::string> VLogger::toString(const P1& p1, const Param& ... param)
    {
        std::vector<std::string> result;
        result.push_back(toStringImpl(p1));

        const auto remainder = toString(param...);
        result.insert(result.end(), remainder.begin(), remainder.end());
        return result;
    }

    void VLogger::info(std::string message)
    {
        log(LogLevel::INFO, "testing {}", "vlogger");
    }
}