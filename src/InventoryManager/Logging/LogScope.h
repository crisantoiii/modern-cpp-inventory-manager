#pragma once
#include "LogCategory.h"
class Logger;

class LogScope
{
public:

    LogScope(
        Logger& logger,
        LogCategory category,
        const CString& scopeName);

    ~LogScope();

private:

    Logger& m_logger;
    LogCategory m_category;
    CString m_scopeName;
};