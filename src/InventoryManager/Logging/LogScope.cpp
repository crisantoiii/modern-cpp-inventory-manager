#include "pch.h"

#include "LogScope.h"
#include "Logger.h"

LogScope::LogScope(
    Logger& logger,
    LogCategory category,
    const CString& scopeName)
    :
    m_logger(logger),
    m_category(category),
    m_scopeName(scopeName)
{
    CString message;

    message.Format(
        _T("ENTER %s"),
        m_scopeName);

    m_logger.Info(m_category, message);
}

LogScope::~LogScope()
{
    CString message;

    message.Format(
        _T("EXIT %s"),
        m_scopeName);

    m_logger.Info(m_category, message);
}