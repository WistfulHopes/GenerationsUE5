// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GenerationsUE5/Actors/GensCameraActor.h"
#include "GensCommon.generated.h"

class FGensUpdateThread;
class AGensCamera;
class APlayerPawn;
/**
 * 
 */
UCLASS()
class GENERATIONSUE5_API UGensCommon : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerPawn> PlayerPawn;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGensCameraActor> CameraActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsModern;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerPawn> ModernSonicClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerPawn> ClassicSonicClass;

private:
	FGensUpdateThread* UpdateThread;
	
public:
	virtual void Init() override;
	virtual void BeginDestroy() override;

	void SpawnPlayer(bool bIsModern);
	void UpdateCamera(const FVector& Pos, const FVector& Target, const FVector& Up, float FOV);
};
