#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class DXGIDebugInfo {
public:
	DXGIDebugInfo();
	~DXGIDebugInfo();

	void SetNextMessage() noexcept;
	std::vector<std::string> GetErrorStrings() const;
private:
	unsigned long long m_next;
	struct IDXGIInfoQueue* m_pInfoQueue;
};