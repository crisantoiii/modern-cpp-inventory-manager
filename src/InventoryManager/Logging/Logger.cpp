#include "pch.h"
#include "Logger.h"

Logger::Logger(const CString& fileName)
{
    CT2A path(fileName);

    m_file.open(
        path,
        std::ios::app);
}

Logger::~Logger()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

CString Logger::GetTimestamp() const
{
    CTime now = CTime::GetCurrentTime();

    return now.Format(
        _T("%Y-%m-%d %H:%M:%S"));
}

CString Logger::LevelToString(
    LogLevel level) const
{
    switch (level)
    {
    case LogLevel::Info:
        return _T("INFO");

    case LogLevel::Warning:
        return _T("WARNING");

    case LogLevel::Error:
        return _T("ERROR");
    }

    return _T("UNKNOWN");
}

CString Logger::CategoryToString(
    LogCategory category) const
{
    switch (category)
    {
    case LogCategory::General:
        return _T("General");

    case LogCategory::UI:
        return _T("UI");

    case LogCategory::Service:
        return _T("Service");

    case LogCategory::Repository:
        return _T("Repository");

    case LogCategory::Database:
        return _T("Database");

    case LogCategory::Testing:
        return _T("Testing");

    case LogCategory::Command:
        return _T("Command");

    case LogCategory::Undo:
        return _T("Undo");

    case LogCategory::Settings:
        return _T("Settings");

    case LogCategory::Import:
        return _T("Import");

    case LogCategory::Export:
        return _T("Export");
    }

    return _T("Unknown");
}

void Logger::Log(
    LogLevel level,
    LogCategory category,
    const CString& message)
{
    std::lock_guard<std::mutex> guard(
        m_mutex);

    CT2A text(message);

    CString entry;

    entry += _T("------------------------------------------------------------\r\n");

    entry += GetTimestamp();

    entry += _T("\r\n\r\n");

    CString line;

    line.Format(
        _T("Level      : %s\r\n"),
        (LPCTSTR)(LevelToString(level)));

    entry += line;

    line.Format(
        _T("Category   : %s\r\n"),
        (LPCTSTR)(CategoryToString(category)));

    entry += line;

    line.Format(
        _T("Message    : %s\r\n"),
        message.GetString());

    entry += line;

    entry += _T("------------------------------------------------------------\r\n");

    CT2A output(entry);

    m_file << output;

    m_file.flush();
}

void Logger::Info(LogCategory category, const CString& message)
{
    Log(LogLevel::Info, category, message);
}

void Logger::Warning(LogCategory category, const CString& message)
{
    Log(LogLevel::Warning, category, message);
}

void Logger::Error(LogCategory category, const CString& message)
{
    Log(LogLevel::Error, category, message);
}