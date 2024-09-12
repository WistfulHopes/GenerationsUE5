// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GensPoseableMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class GENERATIONSUE5_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGensPoseableMeshComponent> CharaMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGensPoseableMeshComponent> SuperMesh;

	UPROPERTY(BlueprintReadOnly)
	bool bIsSuper;

private:
	TArray<FTransform> BoneTransforms;
	TMap<int, FString> BoneIndicesToNames;

	void SetBoneTransforms();
	FTransform GetComponentTransform(UGensPoseableMeshComponent* Mesh, int BoneIdx);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetBoneTransforms(const TArray<FTransform>& InTransforms);
	void SetBoneIndicesToNames(const TMap<int, FString>& InIndicesToNames);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
