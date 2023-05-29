#pragma once
#include <Windows.h>
#include <string>

class Exception {
public:
	Exception(const char* file, int line, PCWSTR additionalInfo = L"") noexcept;
	~Exception() noexcept;

	Exception() = delete;
	Exception(const Exception&) = delete;
	Exception& operator=(const Exception&) = delete;
	Exception& operator=(Exception&&) = delete;

	virtual PCWSTR what() const;
	inline virtual PCWSTR GetExceptionType() const noexcept { return L"Unknown Exception\n"; }
	inline const std::wstring& GetFileAndLine() const noexcept { return m_FileAndLine; }

private:
	std::wstring ReturnFileAndLine(const char* file, int line) const noexcept;

protected:
	mutable std::wstring m_WhatBuffer;

private:
	std::wstring m_AdditionalInfo;
	std::wstring m_FileAndLine;
};

#define CALLEXCEPT() Exception(__FILE__, __LINE__)
#define CALLEXCEPTPARAM(x) Exception(__FILE__, __LINE__, x)