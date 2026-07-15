#pragma once

#include "Logging/Logger.h"
#include "Database/SQLiteDatabase.h"
#include "Repository/SQLiteProductRepository.h"
#include "Services/ProductService.h"

class ApplicationContext
{
public:

    ApplicationContext();

    Logger& GetLogger();

    ProductService& GetProductService();

    SQLiteProductRepository& GetRepository();

private:

    Logger m_logger;

    SQLiteDatabase m_database;

    SQLiteProductRepository m_repository;

    ProductService m_productService;
};