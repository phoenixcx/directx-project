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
	inline virtual PCWSTR GetExceptionType() const noexcept { return L"Exception"; }

	inline const std::wstring& GetFileAndLine() const noexcept { return m_FileAndLine; }
	inline const std::wstring& GetAdditionalInfo() const noexcept { return m_AdditionalInfo; }

private:
	std::wstring ReturnFileAndLine(const char* file, int line) const noexcept;

protected:
	mutable std::wstring m_WhatBuffer;

private:
	std::wstring m_AdditionalInfo;
	std::wstring m_FileAndLine;
};

class HRException : public Exception {
public:
	HRException(const char* file, int line, HRESULT hr, PCWSTR additionalInfo = L"");
	~HRException();

	HRException() = delete;
	HRException(const Exception&) = delete;
	HRException& operator=(const HRException&) = delete;
	HRException& operator=(HRException&&) = delete;

	PCWSTR what() const override;
	inline PCWSTR GetExceptionType() const noexcept override { return L"HResult Exception"; }

private:
	HRESULT m_HR;
};

#define CALLEXCEPT() Exception(__FILE__, __LINE__)
#define CALLEXCEPTPARAM(x) Exception(__FILE__, __LINE__, x)
#define THROWHREXCEPT(x) throw HRException(__FILE__, __LINE__, x)