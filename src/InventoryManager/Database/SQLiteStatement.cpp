#include "pch.h"

#include "SQLiteStatement.h"
#include "SQLiteDatabase.h"

SQLiteStatement::SQLiteStatement(
    SQLiteDatabase& database,
    const std::string& sql)
{
    m_db = database.GetHandle();
    m_statement = database.Prepare(sql);
}

SQLiteStatement::~SQLiteStatement()
{
    if (m_statement)
    {
        sqlite3_finalize(m_statement);
    }
}

bool SQLiteStatement::Step()
{
    return sqlite3_step(m_statement) == SQLITE_ROW;
}

sqlite3_stmt* SQLiteStatement::GetHandle() const
{
    return m_statement;
}

int SQLiteStatement::GetInt(int column) const
{
    return sqlite3_column_int(
        m_statement,
        column);
}

double SQLiteStatement::GetDouble(
    int column) const
{
    return sqlite3_column_double(
        m_statement,
        column);
}

CString SQLiteStatement::GetString(
    int column) const
{
    auto text =
        reinterpret_cast<const char*>(
            sqlite3_column_text(
                m_statement,
                column));

    if (text == nullptr)
        return _T("");

    // Explicitly cast to character pointer and construct CString
    return CString(CA2WEX<128>(text, CP_UTF8));
}

void SQLiteStatement::Bind(
    int index,
    int value)
{
    sqlite3_bind_int(
        m_statement,
        index,
        value);
}

void SQLiteStatement::Bind(
    int index,
    INT64 value)
{
    sqlite3_bind_int64(
        m_statement,
        index,
        value);
}

void SQLiteStatement::Bind(
    int index,
    double value)
{
    sqlite3_bind_double(
        m_statement,
        index,
        value);
}

void SQLiteStatement::Bind(
    int index,
    const CString& value)
{
    CT2A utf8(value);

    sqlite3_bind_text(
        m_statement,
        index,
        utf8,
        -1,
        SQLITE_TRANSIENT);
}

bool SQLiteStatement::Read()
{
    return sqlite3_step(m_statement) == SQLITE_ROW;
}

bool SQLiteStatement::Execute()
{
    int result = sqlite3_step(m_statement);

    if (result != SQLITE_DONE)
    {
        throw std::runtime_error(
            sqlite3_errmsg(
                sqlite3_db_handle(m_statement)));
    }

    return true;
}

INT64 SQLiteStatement::ExecuteInsert()
{
    if (Execute()) {
        return sqlite3_last_insert_rowid(m_db);
    }

    return -1;
}