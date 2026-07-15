#include "pch.h"
#include "SQLiteDatabase.h"

SQLiteDatabase::SQLiteDatabase(const std::string& fileName)
{
    if (sqlite3_open(fileName.c_str(), &m_database) != SQLITE_OK)
    {
        throw std::runtime_error(sqlite3_errmsg(m_database));
    }
}

SQLiteDatabase::~SQLiteDatabase()
{
    if (m_database)
    {
        sqlite3_close(m_database);
    }
}

void SQLiteDatabase::Initialize()
{
    Execute(R"(
        CREATE TABLE IF NOT EXISTS Products
        (
            Id INTEGER PRIMARY KEY AUTOINCREMENT,
            Name TEXT NOT NULL,
            Quantity INTEGER NOT NULL,
            Price REAL NOT NULL,
            Category TEXT NOT NULL,
            Supplier TEXT NOT NULL
        );
    )");
}

bool SQLiteDatabase::Execute(const std::string& sql)
{
    char* errorMessage = nullptr;

    int result =
        sqlite3_exec(
            m_database,
            sql.c_str(),
            nullptr,
            nullptr,
            &errorMessage);

    if (result != SQLITE_OK)
    {
        std::string message = errorMessage;

        sqlite3_free(errorMessage);

        throw std::runtime_error(message);
    }

    return true;
}

sqlite3* SQLiteDatabase::GetHandle() const
{
    return m_database;
}

sqlite3_stmt* SQLiteDatabase::Prepare(const std::string& sql)
{
    sqlite3_stmt* statement = nullptr;

    int result =
        sqlite3_prepare_v2(
            m_database,
            sql.c_str(),
            -1,
            &statement,
            nullptr);

    if (result != SQLITE_OK)
    {
        throw std::runtime_error(
            sqlite3_errmsg(m_database));
    }

    return statement;
}