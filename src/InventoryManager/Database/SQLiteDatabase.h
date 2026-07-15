#pragma once

#include "ThirdParty/SQLite/sqlite3.h"
#include <string>
#include <stdexcept>

class SQLiteDatabase
{
public:

    explicit SQLiteDatabase(const std::string& fileName);
    ~SQLiteDatabase();

    void Initialize();
    bool Execute(const std::string& sql);
    sqlite3* GetHandle() const;
    sqlite3_stmt* Prepare(const std::string& sql);

private:

    sqlite3* m_database = nullptr;
};