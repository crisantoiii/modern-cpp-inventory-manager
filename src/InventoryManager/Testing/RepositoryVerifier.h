#pragma once
#include "TestResult.h"
class IProductRepository;


class RepositoryVerifier
{
public:
    static TestResult Run(IProductRepository& repository);

private:
    static void Assert(
        TestResult& result,
        const CString& name,
        bool condition,
        const CString& message = _T(""));

    static void TestAdd(
        IProductRepository& repository,
        TestResult& result);

    static void TestGetById(
        IProductRepository& repository,
        TestResult& result);

    static void TestUpdate(
        IProductRepository& repository,
        TestResult& result);

    static void TestDelete(
        IProductRepository& repository,
        TestResult& result);

    static void TestRestore(
        IProductRepository& repository,
        TestResult& result);
};