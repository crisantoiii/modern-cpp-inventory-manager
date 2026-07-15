#include "pch.h"

#include "RepositoryVerifier.h"

#include "Repository/IProductRepository.h"

#include "Models/Product.h"
#include "TestResult.h"

#include <afxwin.h>

void RepositoryVerifier::Assert(
    TestResult& result,
    const CString& name,
    bool condition,
    const CString& message)
{
    result.Add(
        name,
        condition,
        message);
}

TestResult RepositoryVerifier::Run(
    IProductRepository& repository)
{
    TestResult result;

    TestAdd(repository, result);
    TestGetById(repository, result);
    TestUpdate(repository, result);
    TestDelete(repository, result);
    TestRestore(repository, result);

    return result;
}

void RepositoryVerifier::TestAdd(IProductRepository& repository,TestResult& result)
{
    auto before = repository.GetAll().size();

    Product test(
        0,
        _T("Repository Test"),
        1,
        1.0,
        _T("Test"),
        _T("Verifier"));

    INT64 id = repository.Add(test);

    auto after = repository.GetAll().size();

    result.Add(
        _T("Add()"),
        after == before + 1);

    repository.Delete(id);
}

void RepositoryVerifier::TestRestore(IProductRepository& repository, TestResult& result)
{
    Product product(
        999,
        _T("Restore Test"),
        5,
        10.0,
        _T("Test"),
        _T("Verifier"));

    repository.Restore(product);

    auto loaded = repository.GetById(999);

    Assert(
        result,
        _T("Restore()"),
        loaded.has_value() &&
        loaded->id == 999);

    repository.Delete(999);
}

void RepositoryVerifier::TestGetById(
    IProductRepository& repository,
    TestResult& result)
{
    Product product(
        0,
        _T("Verifier"),
        5,
        99.0,
        _T("Test"),
        _T("Verifier"));

    INT64 id = repository.Add(product);

    auto loaded = repository.GetById(id);

    Assert(
        result,
        _T("GetById()"),
        loaded.has_value() &&
        loaded->id == id &&
        loaded->name == product.name);

    repository.Delete(id);
}

void RepositoryVerifier::TestUpdate(
    IProductRepository& repository,
    TestResult& result)
{
    Product product(
        0,
        _T("Original"),
        1,
        100,
        _T("Test"),
        _T("Verifier"));

    INT64 id = repository.Add(product);

    auto loaded = repository.GetById(id);

    loaded->name = _T("Updated");
    loaded->quantity = 99;
    loaded->price = 1234.5;

    repository.Update(*loaded);

    auto updated = repository.GetById(id);

    Assert(
        result,
        _T("Update()"),
        updated.has_value() &&
        updated->name == _T("Updated") &&
        updated->quantity == 99 &&
        updated->price == 1234.5);

    repository.Delete(id);
}

void RepositoryVerifier::TestDelete(
    IProductRepository& repository,
    TestResult& result)
{
    INT64 id = repository.Add(Product(
        0,
        _T("Delete Test"),
        1,
        1,
        _T("Test"),
        _T("Verifier")));

    repository.Delete(id);

    auto deleted = repository.GetById(id);

    Assert(
        result,
        _T("Delete()"),
        !deleted.has_value());
}