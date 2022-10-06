// Fill out your copyright notice in the Description page of Project Settings.


#include "STLAnimInstance.h"

USTLAnimInstance::USTLAnimInstance()
{
	PawnSpeed = 0.f;
	bIsInAir = false;

	ConstructorHelpers::FObjectFinder<UAnimMontage>AM_Attack(TEXT("/Game/Animations/AM_Attack.AM_Attack"));
	if (AM_Attack.Succeeded())
	{
		AttackMontage = AM_Attack.Object;
	}
}

void USTLAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		PawnSpeed = Pawn->GetVelocity().Size();

		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			bIsInAir = Character->GetCharacterMovement()->IsFalling();
		}
	}
}

void USTLAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage);
	}
}

void USTLAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	FName SectionName = (*(FString(TEXT("Attack")) + FString::FromInt(NewSection)));
	Montage_JumpToSection(SectionName, AttackMontage);
}

void USTLAnimInstance::AnimNotify_NextAttackCheck()
{
	UE_LOG(LogTemp, Log, TEXT("AnimNotify_NextAttackCheck"));
	OnNextAttackCheck.Broadcast();
}
