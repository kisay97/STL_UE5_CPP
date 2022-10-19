// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceBear.h"
#include "Bear.h"

UAnimInstanceBear::UAnimInstanceBear()
{
	PawnSpeed = 0.f;
	//TODO : AttackMontage
}

void UAnimInstanceBear::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = Cast<ABear>(TryGetPawnOwner());
	if (::IsValid(Pawn))
	{
		PawnSpeed = Pawn->GetVelocity().Size();
		(Pawn->CurrentHP <= 0) ? IsDead = true : IsDead = false;
	}
}

void UAnimInstanceBear::PlayAttackMontage()
{
	// TODO AttackMontage
}

void UAnimInstanceBear::AnimNotify_Attack()
{
	UE_LOG(LogTemp, Log, TEXT("UAnimInstanceBear::AnimNotify_Attack"));
	//OnAttackCheck.Broadcast();
	auto bear = Cast<ABear>(GetOwningActor());
	if (bear)
	{
		bear->CheckAttackedCharacter();
	}
}