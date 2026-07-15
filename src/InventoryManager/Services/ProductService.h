#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Models/Product.h"
#include "Models/ProductQuery.h"
#include "Repository/IProductRepository.h"

class ProductService
{
public:

    ProductService(IProductRepository& repository);
    std::vector<Product>GetProducts(const ProductQuery& query) const;
    INT64 AddProduct(Product product);
    void UpdateProduct(const Product& product);
    void DeleteProduct(INT64 product_id);
    std::optional<Product> GetProductById(INT64 product_id);
    INT64 GetNextProductId();
    void Restore(const Product& product);
    void ValidateProduct(const Product& product);

private:

    IProductRepository& m_repository;
    std::vector<Product> FilterProducts(const std::vector<Product>& products, const ProductQuery& query) const;
    void SortProducts(std::vector<Product>& products, const ProductQuery& query) const;
    bool MatchesSearch( const Product& product, const CString& keyword) const;
};