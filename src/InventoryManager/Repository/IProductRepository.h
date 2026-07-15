#pragma once

#include <vector>
#include <optional>
#include "Models/Product.h"

class IProductRepository
{
public:

    virtual std::vector<Product> GetAll() const = 0;

    virtual std::optional<Product> GetById(INT64 id) const = 0;

    virtual INT64 Add(const Product& product) = 0;

    virtual void Restore(const Product& product) = 0;

    virtual void Update(const Product& product) = 0;

    virtual void Delete(INT64 id) = 0;

    virtual ~IProductRepository() = default;
};