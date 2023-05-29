#include "Exception.h"
#include <sstream>

Exception::Exception(const char* file, int line, PCWSTR additionalInfo) noexcept : m_FileAndLine(ReturnFileAndLine(file, line)), m_AdditionalInfo(additionalInfo) {}

Exception::~Exception() {}

PCWSTR Exception::what() const
{
	std::wostringstream woss;
	woss << GetExceptionType() << GetFileAndLine();
	if (!m_AdditionalInfo.empty()) {
		woss << m_AdditionalInfo;
	}
	
	m_WhatBuffer = woss.str();
	return m_WhatBuffer.c_str();
}

std::wstring Exception::ReturnFileAndLine(const char* file, int line) const noexcept {
	std::wostringstream woss;
	woss << L"File: " << file << L"\nLine: " << line << L"\n";
	return woss.str();
}
