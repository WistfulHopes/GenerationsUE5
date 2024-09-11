// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PoseableMeshComponent.h"
#include "GensPoseableMeshComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GENERATIONSUE5_API UGensPoseableMeshComponent : public UPoseableMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Components|PoseableMesh")
	void SetBoneLocalTransformByName(FName BoneName, const FTransform& InTransform);	
};
