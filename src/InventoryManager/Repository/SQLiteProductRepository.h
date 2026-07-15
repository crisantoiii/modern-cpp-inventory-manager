#pragma once

#include "IProductRepository.h"
#include "Database/SQLiteDatabase.h"
#include "Database/SQLiteStatement.h"
#include "Repository/ProductMapper.h"
#include "Logging/LogScope.h"
#include "Logging/LogCategory.h"

class SQLiteProductRepository :public IProductRepository
{
public:

    explicit SQLiteProductRepository(SQLiteDatabase& database);

    std::vector<Product> GetAll() const override;

    std::optional<Product> GetById(INT64 id) const override;

    INT64 Add(const Product& product) override;

    void Restore(const Product& product) override;

    void Update(const Product& product) override;

    void Delete(INT64 id) override;

private:

    SQLiteDatabase& m_database;
};