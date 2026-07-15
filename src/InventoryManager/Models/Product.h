#pragma once

#include <afxstr.h>

struct Product
{
    INT64 id;
    CString name;
    int quantity;
    double price;
    CString supplier;
    CString category;

    Product(INT64 id, const CString name, int quantity, double price,
        const CString category, const CString supplier)
        : id(id), name(name), quantity(quantity), price(price),
        category(category), supplier(supplier) {
    }
};