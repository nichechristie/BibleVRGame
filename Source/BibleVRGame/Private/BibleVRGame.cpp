// Copyright Epic Games, Inc. All Rights Reserved.

#include "BibleVRGame.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogBibleVRGame);

void FBibleVRGameModule::StartupModule()
{
	// This code will execute after your module is loaded into memory
	UE_LOG(LogBibleVRGame, Log, TEXT("Bible VR Game Module Started"));
}

void FBibleVRGameModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module
	UE_LOG(LogBibleVRGame, Log, TEXT("Bible VR Game Module Shutdown"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FBibleVRGameModule, BibleVRGame, "BibleVRGame");
