// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"


// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	CharaMesh = CreateDefaultSubobject<UGensPoseableMeshComponent>("CharaMesh");
	CharaMesh->SetupAttachment(RootComponent);
	SuperMesh = CreateDefaultSubobject<UGensPoseableMeshComponent>("SuperMesh");
	SuperMesh->SetupAttachment(RootComponent);
}

void APlayerPawn::SetBoneTransforms()
{
	auto Mesh = CharaMesh;
	if (bIsSuper) Mesh = SuperMesh;

	for (int i = 0; i < BoneTransforms.Num(); i++)
	{
		auto BoneTransform = BoneTransforms[i];
		Mesh->SetBoneTransformByName(*BoneIndicesToNames[i], BoneTransform, EBoneSpaces::ComponentSpace);
	}
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPawn::SetBoneTransforms(const TArray<FTransform>& InTransforms)
{
	BoneTransforms = InTransforms;
}

void APlayerPawn::SetBoneIndicesToNames(const TMap<int, FString>& InIndicesToNames)
{
	BoneIndicesToNames = InIndicesToNames;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// SetBoneTransforms();
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

