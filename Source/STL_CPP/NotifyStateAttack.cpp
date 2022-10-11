// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyStateAttack.h"

void UNotifyStateAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	UE_LOG(LogTemp, Log, TEXT("UNotifyStateAttack::NotifyBegin"));
}

void UNotifyStateAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UE_LOG(LogTemp, Log, TEXT("UNotifyStateAttack::NotifyEnd"));
}
