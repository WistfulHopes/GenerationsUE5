// Fill out your copyright notice in the Description page of Project Settings.


#include "GensPoseableMeshComponent.h"

void UGensPoseableMeshComponent::SetBoneLocalTransformByName(FName BoneName, const FTransform& InTransform)
{
	if (!GetSkinnedAsset() || !RequiredBones.IsValid())
	{
		return;
	}

	const int32 BoneIndex = GetBoneIndex(BoneName);
	if (BoneIndex >= 0 && BoneIndex < BoneSpaceTransforms.Num())
	{
		BoneSpaceTransforms[BoneIndex] = InTransform;
		MarkRefreshTransformDirty();
	}
}
