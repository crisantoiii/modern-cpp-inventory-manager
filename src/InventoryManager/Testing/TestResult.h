#pragma once
#include "Models/TestItem.h"
#include <vector>

struct TestResult
{
    std::vector<TestItem> items;

    void Add(
        const CString& name,
        bool passed,
        const CString& message = _T(""));
};