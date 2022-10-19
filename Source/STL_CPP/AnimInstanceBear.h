// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBear.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackCheckDelegate);

/**
 * 
 */
UCLASS()
class STL_CPP_API UAnimInstanceBear : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInstanceBear();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	void PlayAttackMontage();

	UFUNCTION()
	void AnimNotify_Attack();

	FOnAttackCheckDelegate OnAttackCheck;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true)) // AllowPrivateAccess = true : private지만 블프에서 접근은 가능하게 하는거인듯.
	float PawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;
};
