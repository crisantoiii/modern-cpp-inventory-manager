#pragma once

#include "IProductRepository.h"
#include <stdexcept>
#include "Logging/LogScope.h"
#include "Logging/LogCategory.h"

class MemoryProductRepository
    : public IProductRepository
{
public:

    MemoryProductRepository();

    std::vector<Product> GetAll() const  override;

    std::optional<Product> GetById(INT64 id) const override;

    INT64 Add(const Product& product) override;

    void Restore(const Product& product) override;

    void Update(const Product& product) override;

    void Delete(INT64 id) override;

private:

    std::vector<Product> m_products;
};