#include "pch.h"
#include "ProductMapper.h"

Product ProductMapper::Map(SQLiteStatement& statement)
{
    return Product
    {
        statement.GetInt(0),
        statement.GetString(1),
        statement.GetInt(2),
        statement.GetDouble(3),
        statement.GetString(4),
        statement.GetString(5)
    };
}