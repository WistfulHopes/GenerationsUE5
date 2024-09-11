// Copyright Epic Games, Inc. All Rights Reserved.

#include "GenerationsUE5.h"
#include "Modules/ModuleManager.h"

#include "Utility\MemoryMappedFile.h"
#include "Utility/ProcessUtil.h"
#include "Utility\GensProcessThread.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <Windows.h>


IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, GenerationsUE5, "GenerationsUE5" );