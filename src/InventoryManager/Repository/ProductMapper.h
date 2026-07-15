#pragma once

#include "Models/Product.h"
#include "Database/SQLiteStatement.h"

class ProductMapper
{
public:

    static Product Map(SQLiteStatement& statement);
};