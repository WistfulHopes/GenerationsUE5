#include "GensProcessThread.h"

FGensProcessThread* FGensProcessThread::Runnable = nullptr;

FGensProcessThread::FGensProcessThread(HANDLE InHandle) : GensHandle(InHandle)
{
	Thread = FRunnableThread::Create(this, TEXT("FGensProcessThread"), 0, TPri_Normal);
}

FGensProcessThread::~FGensProcessThread()
{
	delete Thread;
	Thread = nullptr;
	Runnable = nullptr;
}

uint32 FGensProcessThread::Run()
{
	WaitForSingleObject(GensHandle, INFINITE);

#if UE_BUILD_SHIPPING
	FGenericPlatformMisc::RequestExit(false);
#endif
	
	return 0;
}

FGensProcessThread* FGensProcessThread::GensProcessInit(HANDLE InHandle)
{
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new FGensProcessThread(InHandle);
	}

	return Runnable;
}
