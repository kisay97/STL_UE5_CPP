// Copyright Epic Games, Inc. All Rights Reserved.


#include "STL_CPPGameModeBase.h"
#include "STLCppCharacter.h"
#include "STLCppPlayerController.h"

ASTL_CPPGameModeBase::ASTL_CPPGameModeBase()
{
	DefaultPawnClass = ASTLCppCharacter::StaticClass();
	PlayerControllerClass = ASTLCppPlayerController::StaticClass();
}