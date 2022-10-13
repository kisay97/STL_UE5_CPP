// Fill out your copyright notice in the Description page of Project Settings.


#include "NotifyStateAttack.h"
#include "STLCppCharacter.h"

void UNotifyStateAttack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	UE_LOG(LogTemp, Log, TEXT("UNotifyStateAttack::NotifyBegin"));

	auto character = Cast<ASTLCppCharacter>(MeshComp->GetOwner());
	if (character)
	{
		character->bIsAttackCheck = true;
		character->HittedActor.Add(character); //�ڱ��ڽ��� ��Ʈ���� �ʵ��� ����
	}
}

void UNotifyStateAttack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UE_LOG(LogTemp, Log, TEXT("UNotifyStateAttack::NotifyEnd"));

	auto character = Cast<ASTLCppCharacter>(MeshComp->GetOwner());
	if (character)
	{
		character->bIsAttackCheck = false;
		character->HittedActor.Empty();
	}
}