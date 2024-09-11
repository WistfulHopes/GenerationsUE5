// Fill out your copyright notice in the Description page of Project Settings.


#include "GensPawnCamera.h"


// Sets default values
AGensPawnCamera::AGensPawnCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGensPawnCamera::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	GetMeshComponent()->SetHiddenInGame(true);
}
