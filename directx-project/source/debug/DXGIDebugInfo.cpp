#pragma comment(lib, "dxguid.lib")

#include "DXGIDebugInfo.h"
#include "Exception.h"
#include <memory>
#include <dxgidebug.h>

DXGIDebugInfo::DXGIDebugInfo() : m_next(0) {
	const auto hModule = LoadLibraryW(L"dxgidebug.dll");
	if (hModule == nullptr) {
		THROW_NO_INFO;
	}

	typedef HRESULT(WINAPI* fPtr)(const IID&, void**);
	fPtr dxgiGetDebugInterface = reinterpret_cast<fPtr>(GetProcAddress(hModule, "DXGIGetDebugInterface"));
	if (dxgiGetDebugInterface == nullptr) {
		THROW_NO_INFO;
	}

	HRESULT hException;
	HR_CALL(dxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), reinterpret_cast<void**>(&m_pInfoQueue)));
	if (m_pInfoQueue == nullptr) {
		THROW_NO_INFO;
	}
}

DXGIDebugInfo::~DXGIDebugInfo() {
	if (m_pInfoQueue != nullptr) {
		m_pInfoQueue->Release();
	}
}

void DXGIDebugInfo::SetNextMessage() noexcept {
	m_next = m_pInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DXGIDebugInfo::GetErrorStrings() const {
	std::vector<std::string> messages;
	const auto end = m_pInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (SIZE_T i = m_next; i < end; i++) {
		HRESULT hException;
		SIZE_T msgLen;

		HR_CALL(m_pInfoQueue->GetMessageW(DXGI_DEBUG_ALL, i, nullptr, &msgLen));

		auto buffer = std::make_unique<byte[]>(msgLen);
		DXGI_INFO_QUEUE_MESSAGE* pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(buffer.get());

		HR_CALL(m_pInfoQueue->GetMessageW(DXGI_DEBUG_ALL, i, pMessage, &msgLen));

		messages.push_back(pMessage->pDescription);
	}
	return messages;
}