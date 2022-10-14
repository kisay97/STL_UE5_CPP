// Fill out your copyright notice in the Description page of Project Settings.


#include "STLCharacterStatComponent.h"
#include "STLGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USTLCharacterStatComponent::USTLCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	Level = 1;
}


void USTLCharacterStatComponent::SetNewLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<USTLGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		CurrentStat = MyGameInstance->GetSTLCharacterData(NewLevel);

		if (CurrentStat)
		{
			Level = NewLevel;
			CurrentHP = CurrentStat->MaxHP;
		}
	}
}

float USTLCharacterStatComponent::GetCharacterAttackDamage()
{
	// 현재 캐릭터의 공격력을 반환해주는 접근자
	if(CurrentStat)
	{
		return CurrentStat->Attack;
	}
	
	return 0.f;
}

void USTLCharacterStatComponent::SetCurrentHpByDamage(float NewDamage)
{
	CurrentHP = FMath::Clamp(CurrentHP - NewDamage, 0.f, CurrentStat->MaxHP);

	if (CurrentHP <= 0)
	{
		//TODO:죽을때 애니메이션
	}
}

// Called when the game starts
void USTLCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USTLCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetNewLevel(Level);
}


// Called every frame
void USTLCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

