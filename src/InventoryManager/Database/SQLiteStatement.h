#pragma once
#include <afxstr.h>
#include "ThirdParty/SQLite/sqlite3.h"
#include <string>

class SQLiteDatabase;

class SQLiteStatement
{
public:

    SQLiteStatement(
        SQLiteDatabase& database,
        const std::string& sql);

    ~SQLiteStatement();

    bool Step();

    sqlite3_stmt* GetHandle() const;

    int GetInt(int column) const;

    double GetDouble(int column) const;

    CString GetString(int column) const;


    void Bind(int index, int value);

    void Bind(int index, INT64 value);

    void Bind(int index, double value);

    void Bind(int index, const CString& value);

    bool Read();

    bool Execute();
    INT64 ExecuteInsert();

private:
    sqlite3* m_db;
    sqlite3_stmt* m_statement = nullptr;
};