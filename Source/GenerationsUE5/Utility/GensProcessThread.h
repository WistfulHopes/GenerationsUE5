#pragma once

#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>

#include "CoreMinimal.h"

class FGensProcessThread : FRunnable
{
public:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static FGensProcessThread* Runnable;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;
	
	/** Handle to Sonic Generations process */
	HANDLE GensHandle;

public:
	explicit FGensProcessThread(HANDLE InHandle);
	virtual ~FGensProcessThread() override;

	virtual uint32 Run() override;
	
	static FGensProcessThread* GensProcessInit(HANDLE InHandle);
};

#include "Windows/HideWindowsPlatformTypes.h"
