#include "pch.h"
#include "FormatHelper.h"

CString FormatHelper::ToString(int value)
{
	CString str;
	str.Format(_T("%d"), value);

	return str;
}

CString FormatHelper::ToString(INT64 value)
{
	CString str;
	str.Format(_T("%I64d"), value);

	return str;
}

CString FormatHelper::ToCurrency(double value)
{
	CString str;
	str.Format(_T("%.2f"), value);

	return str;
}