#pragma once

#include <string>

class CStringConverter
{
public:
	static std::string UnicodeToUtf8(const wchar_t* unicode);
	static std::string MultibyteToUtf8(std::string strData);
	static std::string UnicodeToAnsi(const wchar_t* szStr);
};

