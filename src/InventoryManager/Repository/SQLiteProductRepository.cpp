#include "pch.h"
#include "SQLiteProductRepository.h"
#include "Application/InventoryManager.h"

SQLiteProductRepository::SQLiteProductRepository(SQLiteDatabase& database)
    :
    m_database(database)
{
}

std::vector<Product>SQLiteProductRepository::GetAll() const
{
    SQLiteStatement statement(
        m_database,
        R"(
            SELECT
                Id,
                Name,
                Quantity,
                Price,
                Category,
                Supplier
            FROM Products
        )");

    std::vector<Product> products;

    while (statement.Read())
    {
        products.push_back(
            ProductMapper::Map(statement));
    }

    return products;
}

std::optional<Product>SQLiteProductRepository::GetById(INT64 id) const
{
    SQLiteStatement statement(
        m_database,
        R"(
            SELECT
                Id,
                Name,
                Quantity,
                Price,
                Category,
                Supplier
            FROM Products
            WHERE Id = ?
        )");

    statement.Bind(1, id);

    if (statement.Read())
    {
        return ProductMapper::Map(statement);
    }

    return std::nullopt;
}

INT64 SQLiteProductRepository::Add(const Product& product)
{
    LogScope scope(
        theApp.GetContext().GetLogger(),
        LogCategory::Repository,
        _T("SQLiteProductRepository::Add"));

    CString message;
    message.Format(
        _T("Adding product '%s'"),
        product.name.GetString());

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);

    SQLiteStatement statement(
        m_database,
        R"(
            INSERT INTO Products
            (
                Name,
                Quantity,
                Price,
                Category,
                Supplier
            )
            VALUES
            (
                ?,
                ?,
                ?,
                ?,
                ?
            )
        )");

    statement.Bind(1, product.name);
    statement.Bind(2, product.quantity);
    statement.Bind(3, product.price);
    statement.Bind(4, product.category);
    statement.Bind(5, product.supplier);

    INT64 newId = -1;
    
    try
    {
        newId = statement.ExecuteInsert();
    }
    catch (const std::exception&)
    {
        theApp.GetContext().GetLogger().Error(LogCategory::Repository,
            _T("Failed to execute INSERT statement."));

        throw;
    }
    
    if (newId > 0)
    {
        message.Format(
            _T("Product added successfully (ID=%d)"),
            newId);

        theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);
    }

    return newId;
}

void SQLiteProductRepository::Restore(const Product& product)
{
    LogScope scope(
        theApp.GetContext().GetLogger(),
        LogCategory::Repository,
        _T("SQLiteProductRepository::Restore"));

    CString message;

    message.Format(
        _T("Restoring product ID=%d"),
        product.id);

    theApp.GetContext()
        .GetLogger()
        .Info(
            LogCategory::Repository,
            message);

    SQLiteStatement statement(
        m_database,
        R"(
            INSERT INTO Products
            (
                Id,
                Name,
                Quantity,
                Price,
                Category,
                Supplier
            )
            VALUES
            (
                ?, ?, ?, ?, ?, ?
            )
        )");

    statement.Bind(1, product.id);
    statement.Bind(2, product.name);
    statement.Bind(3, product.quantity);
    statement.Bind(4, product.price);
    statement.Bind(5, product.category);
    statement.Bind(6, product.supplier);

    INT64 newId = -1;

    try
    {
        newId = statement.ExecuteInsert();
    }
    catch (const std::exception&)
    {
        theApp.GetContext().GetLogger().Error(LogCategory::Repository,
            _T("Failed to execute INSERT statement."));

        throw;
    }

    if (newId > 0)
    {
        message.Format(
            _T("Product restored successfully (ID=%d)"),
            product.id);
        
        theApp.GetContext()
            .GetLogger()
            .Info(
                LogCategory::Repository,
                message);
    }
}

void SQLiteProductRepository::Update(const Product& product)
{
    LogScope scope(
        theApp.GetContext().GetLogger(),
        LogCategory::Repository,
        _T("SQLiteProductRepository::Update"));

    CString message;

    message.Format(
        _T("Updating product ID=%d"),
        product.id);

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);

    SQLiteStatement statement(
        m_database,
        R"(
            UPDATE Products
            SET
                Name = ?,
                Quantity = ?,
                Price = ?,
                Category = ?,
                Supplier = ?
            WHERE
                Id = ?
        )");

    statement.Bind(1, product.name);
    statement.Bind(2, product.quantity);
    statement.Bind(3, product.price);
    statement.Bind(4, product.category);
    statement.Bind(5, product.supplier);
    statement.Bind(6, product.id);

    try
    {
        statement.Execute();
    }
    catch (const std::exception&)
    {
        theApp.GetContext().GetLogger().Error(LogCategory::Repository,
            _T("Failed to execute UPDATE statement."));

        throw;
    }

    message.Format(
        _T("Product updated successfully (ID=%d)"),
        product.id);

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);
}

void SQLiteProductRepository::Delete(INT64 id)
{
    LogScope scope(
        theApp.GetContext().GetLogger(),
        LogCategory::Repository,
        _T("SQLiteProductRepository::Delete"));

    CString message;
    message.Format(
        _T("Deleting product ID=%d"),
        id);

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);

    SQLiteStatement statement(
        m_database,
        R"(
            DELETE
            FROM Products
            WHERE Id = ?
        )");

    statement.Bind(1, id);

    try
    {
        statement.Execute();
    }
    catch (const std::exception&)
    {
        theApp.GetContext().GetLogger().Error(LogCategory::Repository,
            _T("Failed to execute UPDATE statement."));

        throw;
    }

    message.Format(
        _T("Product deleted successfully (ID=%d)"),
        id);

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);
}