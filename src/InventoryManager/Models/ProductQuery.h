#pragma once

#include <afxstr.h>

enum class ProductSortColumn
{
    Id = 0,
    Name,
    Quantity,
    Price,
    Category,
    Supplier
};

struct ProductQuery
{
    CString searchText;

    ProductSortColumn sortColumn = ProductSortColumn::Id;

    bool ascending = true;

    bool lowStockOnly = false;

    CString supplier;

    CString category;
};