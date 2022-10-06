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
	void AnimNotify_NextAttackCheck(); // AnimNotify_ ������ �̸��� �ִ� ��Ÿ�ֿ� ��Ƽ���� ��� ������ �����ϸ� �������� �˾Ƽ� �����.

	FOnNextAttackCheckDelegate OnNextAttackCheck;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true)) //private���� �������� ������ �����ϰ� �ϴ°��ε�.
	float PawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};