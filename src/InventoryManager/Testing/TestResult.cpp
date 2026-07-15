#include "pch.h"
#include "TestResult.h"

void TestResult::Add(
    const CString& name,
    bool passed,
    const CString& message)
{
    items.push_back(
        {
            name,
            passed,
            message
        });
}