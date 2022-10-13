// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "STLGameInstance.generated.h"

USTRUCT(BlueprintType) //이래야 블프에서 사용가능. 데이터테이블에서 기반 열거형을 선택할 때 C++에서 만든 열거형을 쓰기 위함.
struct FSTLCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSTLCharacterData() : Level(1), MaxHP(100.f), Attack(10.f), NextEXP(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 NextEXP;
};

UCLASS()
class STL_CPP_API USTLGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USTLGameInstance();

	virtual void Init() override;

	FSTLCharacterData* GetSTLCharacterData(int32 Level);

private:
	UPROPERTY()
	UDataTable* STLCharacterTable;
};
