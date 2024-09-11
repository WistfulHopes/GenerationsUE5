#pragma once

#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>

struct FGensEvent
{
protected:
	HANDLE m_handle = nullptr;

public:
	static constexpr TCHAR s_cpuEventName[] = TEXT("GenerationsUE5CPUEvent");
	static constexpr TCHAR s_gpuEventName[] = TEXT("GenerationsUE5GPUEvent");

	FGensEvent(LPCTSTR name, BOOL initialState);
	FGensEvent(LPCTSTR name);
	~FGensEvent();

	void wait() const;
	bool waitImm() const;

	void set() const;
	void reset() const;
};

#include "Event.inl"

#include "Windows/HideWindowsPlatformTypes.h"