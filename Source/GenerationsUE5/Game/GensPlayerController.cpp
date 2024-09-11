// Fill out your copyright notice in the Description page of Project Settings.


#include "GensPlayerController.h"

#include "GenerationsUE5/Actors/GensCamera.h"

AGensPlayerController::AGensPlayerController()
{
	PlayerCameraManagerClass = AGensCamera::StaticClass();
}
