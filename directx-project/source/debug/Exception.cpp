#include "Exception.h"
#include <sstream>

// Exception

Exception::Exception(const char* file, int line) noexcept : m_FileAndLine(ReturnFileAndLine(file, line)) {}

Exception::~Exception() {}

PCWSTR Exception::what() const
{
	std::wostringstream woss;
	woss << GetExceptionType() << L"\n\n" << GetFileAndLine() << L"\n\n";
	
	m_WhatBuffer = woss.str();
	return m_WhatBuffer.c_str();
}

std::wstring Exception::ReturnFileAndLine(const char* file, int line) const noexcept {
	std::wostringstream woss;
	woss << L"File: " << file << L"\nLine: " << line;
	return woss.str();
}


// DXGIException

DXGIException::DXGIException(const char* file, int line, std::vector<std::string> errorStrings)
	: Exception(file, line), m_errorStrings(errorStrings) {}

DXGIException::~DXGIException() {}

PCWSTR DXGIException::what() const {
	std::wostringstream woss;
	woss << GetExceptionType() << L"\n\n" << GetFileAndLine() << L"\n\n";

	woss << L"DXGI Errors:\n";
	for (auto x : m_errorStrings) {
		woss << std::wstring(x.begin(), x.end()) << L"\n";
	}

	m_WhatBuffer = woss.str();
	return m_WhatBuffer.c_str();
}


// HRException

HRException::HRException(const char* file, int line, HRESULT hr) : Exception(file, line), m_HR(hr) {}

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
		woss << L"HRESULT:\n" << buf << L"\n\n";
	}
	LocalFree(buf);
	
	m_WhatBuffer = woss.str();
	return m_WhatBuffer.c_str();
}


// DXGIHRException

DXGIHRException::DXGIHRException(const char* file, int line, HRESULT hr, DXGIDebugInfo debugInfo) :
	HRException(file, line, hr), m_debugInfo(debugInfo) {}

DXGIHRException::~DXGIHRException() {}

PCWSTR DXGIHRException::what() const {
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
		woss << L"HRESULT:\n" << buf << L"\n\n";
	}
	LocalFree(buf);

	woss << L"DXGI Errors:\n";
	auto strings = m_debugInfo.GetErrorStrings();
	for (auto x : strings) {
		woss << std::wstring(x.begin(), x.end()) << L"\n";
	}

	m_WhatBuffer = woss.str();
	return m_WhatBuffer.c_str();
}