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
}

uint32 FGensProcessThread::Run()
{
	WaitForSingleObject(GensHandle, INFINITE);

	//FGenericPlatformMisc::RequestExit(false);
	
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
