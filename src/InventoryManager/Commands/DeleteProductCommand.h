#pragma once

#include "ICommand.h"

#include "../Models/Product.h"

class ProductService;

class DeleteProductCommand : public ICommandx
{
public:

    DeleteProductCommand(
        ProductService& service,
        int productId);

    void Execute() override;

    void Undo() override;

private:

    ProductService& m_service;

    int m_productId;

    Product m_deletedProduct;

    bool m_hasBackup = false;
};