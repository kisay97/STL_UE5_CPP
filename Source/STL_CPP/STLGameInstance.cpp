// Fill out your copyright notice in the Description page of Project Settings.


#include "STLGameInstance.h"

USTLGameInstance::USTLGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CharacterData(TEXT("/Game/DataTable/StlCharData.StlCharData"));
	if (DT_CharacterData.Succeeded())
	{
		STLCharacterTable = DT_CharacterData.Object;
	}

	check(STLCharacterTable->GetRowMap().Num() > 0); //
}

void USTLGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("EXP: %d"), GetSTLCharacterData(5)->NextEXP);
}

FSTLCharacterData* USTLGameInstance::GetSTLCharacterData(int32 Level)
{
	return STLCharacterTable->FindRow<FSTLCharacterData>(*FString::FromInt(Level), TEXT("")); //ContextString는 실패를 했을 경우 같이 출력할 보조적인 내용
}

