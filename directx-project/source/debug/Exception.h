#pragma once
#include <Windows.h>
#include <string>
#include "DXGIDebugInfo.h"

class Exception {
public:
	Exception(const char* file, int line) noexcept;
	~Exception() noexcept;

	Exception() = delete;
	Exception(const Exception&) = delete;
	Exception& operator=(const Exception&) = delete;
	Exception& operator=(Exception&&) = delete;

	virtual PCWSTR what() const;
	inline virtual PCWSTR GetExceptionType() const noexcept { return L"Exception"; }

	inline const std::wstring& GetFileAndLine() const noexcept { return m_FileAndLine; }

private:
	std::wstring ReturnFileAndLine(const char* file, int line) const noexcept;

protected:
	mutable std::wstring m_WhatBuffer;

private:
	std::wstring m_FileAndLine;
};

class DXGIException : public Exception {
public:
	DXGIException(const char* file, int line, std::vector<std::string> errorStrings);
	~DXGIException();

	DXGIException() = delete;
	DXGIException(const DXGIException&) = delete;
	DXGIException& operator=(const DXGIException&) = delete;
	DXGIException& operator=(DXGIException&&) = delete;

	PCWSTR what() const override;
	inline PCWSTR GetExceptionType() const noexcept override { return L"DXGI Exception"; }

private:
	std::vector<std::string> m_errorStrings;
};

class HRException : public Exception {
public:
	HRException(const char* file, int line, HRESULT hr);
	~HRException();

	HRException() = delete;
	HRException(const HRException&) = delete;
	HRException& operator=(const HRException&) = delete;
	HRException& operator=(HRException&&) = delete;

	PCWSTR what() const override;
	inline PCWSTR GetExceptionType() const noexcept override { return L"HRESULT Exception"; }

protected:
	HRESULT m_HR;
};

class DXGIHRException : public HRException {
public:
	DXGIHRException(const char* file, int line, HRESULT hr, DXGIDebugInfo debugInfo);
	~DXGIHRException();

	DXGIHRException() = delete;
	DXGIHRException(const DXGIHRException&) = delete;
	DXGIHRException& operator=(const DXGIHRException&) = delete;
	DXGIHRException& operator=(DXGIHRException&&) = delete;

	PCWSTR what() const override;
	inline PCWSTR GetExceptionType() const noexcept override { return L"DXGI HRESULT Exception"; }

private:
	const DXGIDebugInfo& m_debugInfo;
};

#define THROW_NO_INFO throw Exception(__FILE__, __LINE__)

#ifdef _DEBUG
#define DXGI_CALL(x) debugInfo.SetNextMessage(); x; errorStrings = debugInfo.GetErrorStrings(); if (!errorStrings.empty()) throw DXGIException(__FILE__, __LINE__, errorStrings)
#define HR_CALL(x) hException = x; if (FAILED(hException)) throw HRException(__FILE__, __LINE__, hException)
#define DXGI_HR_CALL(x) debugInfo.SetNextMessage(); hException = x; if (FAILED(hException)) throw DXGIHRException(__FILE__, __LINE__, hException, debugInfo)

#define TRY_THROW(x) try{ x; } catch (...) { throw; }

// If _DEBUG is not defined
#else
#define DXGI_CALL(x) x
#define HR_CALL(x) x
#define DXGI_HR_CALL(x) x

#define TRY_THROW(x) x
#endif