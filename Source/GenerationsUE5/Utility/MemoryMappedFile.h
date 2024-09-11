#pragma once

#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>

class FMemoryMappedFile
{
protected:
	HANDLE m_handle = nullptr;
#if UE_BUILD_SHIPPING == 0
	mutable bool m_mapped = false;
#endif

public:
	static constexpr size_t s_size = 64 * 1024 * 1024;
	static constexpr TCHAR s_name[] = TEXT("GenerationsUE5MemoryMappedFile");

	FMemoryMappedFile();
	~FMemoryMappedFile();

	void* map() const;
	void flush(void* buffer, size_t size) const;
	void unmap(void* buffer) const;
};

#include "MemoryMappedFile.inl"

#include "Windows/HideWindowsPlatformTypes.h"