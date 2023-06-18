#pragma once
#include <Windows.h>
#include <unordered_map>
#include <string>

class WindowsMessageMap
{
public:
	WindowsMessageMap();
	const wchar_t* operator()(DWORD msg, LPARAM lp, WPARAM wp) const;
private:
	std::unordered_map<DWORD, std::string> map;
};