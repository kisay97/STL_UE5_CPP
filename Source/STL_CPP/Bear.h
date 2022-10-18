// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "GameFramework/Character.h"
#include "Bear.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBearDiedDelegate);

UCLASS()
class STL_CPP_API ABear : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SetTarget(APawn* Pawn);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void Attack();

	UFUNCTION()
	void Die();

	UPROPERTY(VisibleAnywhere)
	float CurrentHP;

	UPROPERTY(VisibleAnywhere)
	float MaxHP;

	UPROPERTY()
	bool IsAttacking;

	UPROPERTY()
	UAnimMontage* Attack1;

	UPROPERTY()
	UAnimMontage* Attack2;

	UPROPERTY()
	UAnimMontage* Attack3;

	FOnAttackEndedDelegate OnAttackEnded;
	FOnBearDiedDelegate OnBearDied;

public:
	UPROPERTY()
	class UAnimInstanceBear* AnimInstance;

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensing;

private:
	UPROPERTY()
	APawn* TargetPawn;
};
