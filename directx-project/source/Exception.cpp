#include "Exception.h"
#include <sstream>

// Exception

Exception::Exception(const char* file, int line, PCWSTR additionalInfo) noexcept : m_FileAndLine(ReturnFileAndLine(file, line)), m_AdditionalInfo(additionalInfo) {}

Exception::~Exception() {}

PCWSTR Exception::what() const
{
	std::wostringstream woss;
	woss << GetExceptionType() << L"\n\n" << GetFileAndLine() << L"\n\n";
	if (!GetAdditionalInfo().empty()) {
		woss << GetAdditionalInfo();
	}
	
	m_WhatBuffer = woss.str();
	return m_WhatBuffer.c_str();
}

std::wstring Exception::ReturnFileAndLine(const char* file, int line) const noexcept {
	std::wostringstream woss;
	woss << L"File: " << file << L"\nLine: " << line;
	return woss.str();
}


// HRException

HRException::HRException(const char* file, int line, HRESULT hr, PCWSTR additionalInfo) : Exception(file, line, additionalInfo), m_HR(hr) {}

HRException::~HRException() {}

PCWSTR HRException::what() const {
	std::wostringstream woss;
	woss << GetExceptionType() << L"\n\n" << GetFileAndLine() << L"\n\n";

	PWSTR buf = NULL;

	FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		m_HR,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(PWSTR)&buf,
		0,
		NULL
	);

	if (buf != NULL) {
		woss << buf << L"\n\n";
	}
	LocalFree(buf);

	if (!GetAdditionalInfo().empty()) {
		woss << GetAdditionalInfo();
	}
	
	m_WhatBuffer = woss.str();
	return m_WhatBuffer.c_str();
}