#pragma once

#include <fstream>
#include <mutex>

#include "LogLevel.h"
#include "LogCategory.h"

class Logger
{
public:

    explicit Logger(const CString& fileName);

    ~Logger();

    void Log(
        LogLevel level,
        LogCategory category,
        const CString& message);

    Logger& GetLogger();

    void Info(
        LogCategory category,
        const CString& message);

    void Warning(
        LogCategory category,
        const CString& message);

    void Error(
        LogCategory category,
        const CString& message);

private:

    std::ofstream m_file;

    std::mutex m_mutex;

    CString GetTimestamp() const;

    CString LevelToString( LogLevel level) const;

    CString CategoryToString(
        LogCategory category) const;

};