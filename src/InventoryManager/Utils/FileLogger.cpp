#include "pch.h"
#include "FileLogger.h"

FileLogger::FileLogger(const std::string& fileName)
{
    m_file.open(fileName, std::ios::app);
}

FileLogger::~FileLogger()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

void FileLogger::WriteLine(const std::string& text)
{
    m_file << text << std::endl;
}