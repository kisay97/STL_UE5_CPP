// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "Animation/AnimInstance.h"
#include "STLAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);

/**
 * 
 */
UCLASS()
class STL_CPP_API USTLAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	USTLAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

	UFUNCTION()
	void AnimNotify_NextAttackCheck(); // AnimNotify_ 다음에 이름이 애님 몽타주에 노티파이 명과 완전히 동일하면 엔진에서 알아서 잡아줌.

	FOnNextAttackCheckDelegate OnNextAttackCheck;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true)) //private지만 블프에서 접근은 가능하게 하는거인듯.
	float PawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};