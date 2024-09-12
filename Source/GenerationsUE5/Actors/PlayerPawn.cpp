// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "Kismet/KismetMathLibrary.h"


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
		Mesh->ResetBoneTransformByName(*BoneIndicesToNames[i]);

		auto RefBoneTransform = GetComponentTransform(Mesh, Mesh->GetSkinnedAsset()->GetRefSkeleton().FindBoneIndex(*BoneIndicesToNames[i]));
		auto BoneTransform = BoneTransforms[i] * RefBoneTransform;

		FVector Pos = BoneTransform.GetLocation();
		FRotator Rot = BoneTransform.Rotator();
		FVector Scale = BoneTransform.GetScale3D();
		
		Mesh->SetBoneTransformByName(*BoneIndicesToNames[i], FTransform(Rot, Pos, Scale), EBoneSpaces::ComponentSpace);
	}
}

FTransform APlayerPawn::GetComponentTransform(UGensPoseableMeshComponent* Mesh, int BoneIdx)
{
	if (BoneIdx == INDEX_NONE) return FTransform::Identity;
	
	FTransform BoneTransform = Mesh->GetSkinnedAsset()->GetRefSkeleton().GetRefBonePose()[BoneIdx];
	FMeshBoneInfo BoneInfo = Mesh->GetSkinnedAsset()->GetRefSkeleton().GetRefBoneInfo()[BoneIdx];
	if (BoneInfo.ParentIndex != 0)
	{
		BoneTransform *= GetComponentTransform(Mesh, BoneInfo.ParentIndex);
	}

	return BoneTransform;
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

	SetBoneTransforms();
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

