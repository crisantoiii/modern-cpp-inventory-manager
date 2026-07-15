#include "pch.h"
#include "ProductService.h"

ProductService::ProductService(IProductRepository& repository): m_repository(repository)
{
}

std::optional<Product> ProductService::GetProductById(INT64 product_id)
{
    return m_repository.GetById(product_id);
}

std::vector<Product>ProductService::GetProducts(const ProductQuery& query) const
{
    auto products = m_repository.GetAll();

    auto filtered = FilterProducts(products, query);

    SortProducts(filtered, query);

    return filtered;
}

INT64 ProductService::AddProduct(Product product)
{
    ValidateProduct(product);
    product.id = GetNextProductId();

    return m_repository.Add(product);
}

void ProductService::Restore(const Product& product)
{
    m_repository.Restore(product);
}

void ProductService::UpdateProduct(const Product& product)
{
    ValidateProduct(product);

    m_repository.Update(product);
}

void ProductService::DeleteProduct(INT64 product_id)
{
    m_repository.Delete(product_id);
}

INT64 ProductService::GetNextProductId()
{
    auto products = m_repository.GetAll();

    if (products.empty())
        return 1;

    INT64 maxId = 0;

    for (const auto& product : products)
    {
        maxId = (std::max)(maxId, product.id);
    }

    return maxId + 1;
}

void ProductService::ValidateProduct(
    const Product& product)
{
    if (product.name.IsEmpty())
        throw std::runtime_error("Product name is required.");

    if (product.quantity <= 0)
        throw std::runtime_error("Quantity must be greater than zero.");

    if (product.price <= 0)
        throw std::runtime_error("Price must be greater than zero.");
}

std::vector<Product> ProductService::FilterProducts(const std::vector<Product>& products, const ProductQuery& query) const
{
    std::vector<Product> filtered = products;
    if (!query.searchText.IsEmpty())
    {
        CString keyword = query.searchText;
        keyword.MakeLower();
        filtered.clear();

        for (const auto& product : products)
        {
            if (MatchesSearch(product,keyword))
            {
                filtered.push_back(product);
            }
        }
    }

    return filtered;
}

void ProductService::SortProducts(std::vector<Product>& products, const ProductQuery& query) const
{
    std::sort(
        products.begin(),
        products.end(),
        [&](const Product& left,
            const Product& right)
        {
            switch (query.sortColumn)
            {
            case ProductSortColumn::Id:
                if (query.ascending)
                    return left.id < right.id;

                return left.id > right.id;

            case ProductSortColumn::Name:
                if (query.ascending)
                    return left.name < right.name;

                return left.name > right.name;

            case ProductSortColumn::Quantity:
                if (query.ascending)
                    return left.quantity < right.quantity;

                return left.quantity > right.quantity;

            case ProductSortColumn::Price:
                if (query.ascending)
                    return left.price < right.price;

                return left.price > right.price;

            case ProductSortColumn::Category:
                if (query.ascending)
                    return left.category < right.category;

                return left.category > right.category;

            case ProductSortColumn::Supplier:
                if (query.ascending)
                    return left.supplier < right.supplier;

                return left.supplier > right.supplier;

            default:
                return false;
            }
        });
}

bool ProductService::MatchesSearch(const Product& product, const CString& keyword) const
{
    CString name = product.name;
    name.MakeLower();

    CString category = product.category;
    category.MakeLower();

    CString supplier = product.supplier;
    supplier.MakeLower();

    return name.Find(keyword) != -1 ||
        category.Find(keyword) != -1 ||
        supplier.Find(keyword) != -1;
}