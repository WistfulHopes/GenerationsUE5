// Fill out your copyright notice in the Description page of Project Settings.


#include "GensCommon.h"
#include "GenerationsUE5/Actors/PlayerPawn.h"
#include "GenerationsUE5/Interop/GensUpdateThread.h"
#include "GenerationsUE5/Utility/ProcessUtil.h"
#include "Kismet/GameplayStatics.h"
#include "GenerationsUE5/Utility/GensProcessThread.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>

#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"

static constexpr LPCTSTR s_gensProcessName = TEXT("SonicGenerations.exe");

static void onProcessNotFound()
{
#if UE_BUILD_SHIPPING
	MessageBox(nullptr,
		TEXT("This executable file cannot run independently. "
			 "Please install and play Generations UE5 using HedgeModManager, just like any other Sonic Generations mod."),
		TEXT("Generations UE5"),
		MB_ICONERROR);
	
	FGenericPlatformMisc::RequestExit(false);
#endif
}

void UGensCommon::Init()
{
	Super::Init();
	
#if UE_BUILD_SHIPPING == 0
	if (!findProcess(s_gensProcessName))
	{
		STARTUPINFO startupInfo{};
		startupInfo.cb = sizeof(startupInfo);

		PROCESS_INFORMATION processInformation{};

		CreateProcess(
			TEXT("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Sonic Generations\\SonicGenerations.exe"),
			nullptr,
			nullptr,
			nullptr,
			TRUE,
			0,
			nullptr,
			TEXT("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Sonic Generations"),
			&startupInfo,
			&processInformation);

		UE_LOG(LogTemp, Display, TEXT("Waiting for Sonic Generations..."));

		while (!findProcess(s_gensProcessName))
			Sleep(10);
			
		UE_LOG(LogTemp, Display, TEXT("Waiting for memory mapped file..."));

		HANDLE handle;
		do
		{
			handle = OpenFileMapping(FILE_MAP_READ, FALSE, FMemoryMappedFile::s_name);
			Sleep(10);
		} while (!handle);

		CloseHandle(handle);
			
		UE_LOG(LogTemp, Display, TEXT("Success!"));
	}
#endif

	const auto process = findProcess(s_gensProcessName);
	if (!process)
	{
		onProcessNotFound();
	}

	const HANDLE processHandle = OpenProcess(SYNCHRONIZE, FALSE, *process);
	if (!processHandle)
	{
		onProcessNotFound();
	}

	FGensProcessThread::GensProcessInit(processHandle);

	UpdateThread = FGensUpdateThread::GensUpdateInit(this);
}

void UGensCommon::BeginDestroy()
{
	Super::BeginDestroy();
	
	PlayerPawn = nullptr;
}

void UGensCommon::SpawnPlayer(bool bSpawnModern)
{
	if (PlayerPawn) PlayerPawn->K2_DestroyActor();

	if (bSpawnModern) PlayerPawn = GetWorld()->SpawnActor<APlayerPawn>(ModernSonicClass);
	else PlayerPawn = GetWorld()->SpawnActor<APlayerPawn>(ClassicSonicClass);

	bIsModern = bSpawnModern;
}

void UGensCommon::UpdateCamera(const FVector& Pos, const FVector& Target, const FVector& Up, const float FOV)
{	
	if (!IsValid(CameraActor))
	{
		TArray<AActor*> Candidates;
		UGameplayStatics::GetAllActorsOfClass(this, AGensCameraActor::StaticClass(), Candidates);

		if (Candidates.Num() > 0) CameraActor = Cast<AGensCameraActor>(Candidates[0]);
		else return;
	}

	const auto Dir = (Target - Pos).GetSafeNormal();
	
	CameraActor->SetActorLocation(Pos);
	CameraActor->SetActorRotation(UKismetMathLibrary::MakeRotFromXZ(Dir, Up));
	CameraActor->GetCameraComponent()->SetFieldOfView(FOV);
}

#include "Windows/HideWindowsPlatformTypes.h"