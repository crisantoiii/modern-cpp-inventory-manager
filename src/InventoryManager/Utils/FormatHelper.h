#pragma once

class FormatHelper
{
public:
	FormatHelper() = delete;

	static CString ToString(int value);
	static CString ToString(INT64 value);
	static CString ToCurrency(double value);
};
