// Fill out your copyright notice in the Description page of Project Settings.


#include "GensGameMode.h"

#include "GensPlayerController.h"
#include "GenerationsUE5/Actors/GensPawnCamera.h"

AGensGameMode::AGensGameMode()
{
	PlayerControllerClass = AGensPlayerController::StaticClass();
	DefaultPawnClass = AGensPawnCamera::StaticClass();
}
