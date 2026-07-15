#pragma once

#include <fstream>
#include <string>

class FileLogger
{
public:
    explicit FileLogger(const std::string& fileName);
    ~FileLogger();

    void WriteLine(const std::string& text);

private:
    std::ofstream m_file;
};