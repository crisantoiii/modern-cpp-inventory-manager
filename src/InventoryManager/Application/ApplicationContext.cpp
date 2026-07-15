#include "pch.h"
#include "ApplicationContext.h"


ApplicationContext::ApplicationContext()
    :
    m_logger(_T("inventory.log")),
    m_database("inventory.db"),
    m_repository(m_database),
    m_productService(m_repository)
{
}


ProductService& ApplicationContext::GetProductService()
{
    return m_productService;
}

Logger& ApplicationContext::GetLogger()
{
    return m_logger;
}

SQLiteProductRepository& ApplicationContext::GetRepository()
{
    return m_repository;
}