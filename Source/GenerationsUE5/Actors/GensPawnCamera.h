// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "GensPawnCamera.generated.h"

UCLASS()
class GENERATIONSUE5_API AGensPawnCamera : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGensPawnCamera();

private:
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;
};
