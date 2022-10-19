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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true)) // AllowPrivateAccess = true : private���� �������� ������ �����ϰ� �ϴ°��ε�.
	float PawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;
};
