#include "pch.h"
#include "MemoryProductRepository.h"
#include "Application/InventoryManager.h"

MemoryProductRepository::MemoryProductRepository()
{
    m_products.emplace_back(
        1,
        _T("Mouse"),
        10,
        500,
        _T("Peripheral"),
        _T("ABC Inc."));

    m_products.emplace_back(
        2,
        _T("SSD"),
        25,
        4500,
        _T("Storage"),
        _T("XXX Inc."));

    m_products.emplace_back(
        3,
        _T("GPU"),
        5,
        21500,
        _T("Graphics"),
        _T("MSI"));

    m_products.emplace_back(4, _T("i7 14th Gen."), 2, 5800.0, _T("CPU"), _T("BBC Inc."));
    m_products.emplace_back(5, _T("8GB DDR4"), 8, 1800.0, _T("Memory"), _T("BBC Inc."));
    m_products.emplace_back(6, _T("GPU"), 1, 21800.0, _T("VCard"), _T("BBC Inc."));
}

std::vector<Product> MemoryProductRepository::GetAll() const
{
    return m_products;
}

std::optional<Product> MemoryProductRepository::GetById(INT64 id) const
{
    auto it = std::find_if(
        m_products.begin(),
        m_products.end(),
        [id](const Product& p)
        {
            return p.id == id;
        });

    if (it == m_products.end())
        throw std::runtime_error("Product not found");

    return *it;
}

INT64 MemoryProductRepository::Add(const Product& product)
{
    LogScope scope(
        theApp.GetContext().GetLogger(),
        LogCategory::Repository,
        _T("MemoryProductRepository::Add"));

    CString message;
    message.Format(
        _T("Adding product '%s'"),
        product.name.GetString());

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);

    m_products.push_back(product);

    message.Format(
        _T("Product added successfully (ID=%dI64d)"),
        product.id);

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);

    return product.id;
}

void MemoryProductRepository::Restore(
    const Product& product)
{
    m_products.push_back(product);
}

void MemoryProductRepository::Update(const Product& product)
{
    LogScope scope(
        theApp.GetContext().GetLogger(),
        LogCategory::Repository,
        _T("MemoryProductRepository::Update"));

    CString message;

    message.Format(
        _T("Updating product ID=%dI64d"),
        product.id);

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);

    auto it = std::find_if(
        m_products.begin(),
        m_products.end(),
        [id = product.id](const Product& p) {
            return p.id == id;
        }
    );

    if (it != m_products.end()) {
        *it = product; 
    }
    else {
        theApp.GetContext().GetLogger().Error(LogCategory::Repository,
            _T("Product ID not found for update."));

        throw;
    }

    message.Format(
        _T("Product updated successfully (ID=%I64d)"),
        product.id);

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);
}

void MemoryProductRepository::Delete(INT64 id)
{
    LogScope scope(
        theApp.GetContext().GetLogger(),
        LogCategory::Repository,
        _T("MemoryProductRepository::Delete"));

    CString message;
    message.Format(
        _T("Deleting product ID=%I64d"),
        id);

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);

    m_products.erase(

        std::remove_if(

            m_products.begin(),
            m_products.end(),

            [id](const Product& p)
            {
                return p.id == id;
            }),

        m_products.end());

    message.Format(
        _T("Product deleted successfully (ID=%dI64d)"),
        id);

    theApp.GetContext().GetLogger().Info(LogCategory::Repository, message);
}