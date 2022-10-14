// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "GameFramework/Character.h"
#include "STLCppCharacter.generated.h"

UCLASS()
class STL_CPP_API ASTLCppCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASTLCppCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	class USTLAnimInstance* StlAnim;

	void MoveForward(float axis);
	void MoveRight(float axis);
	void LookUp(float axis);
	void Turn(float axis);
	void Attack();

	void AttackStartCombo();
	void AttackEndCombo();
	void AttackCheck();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void AddWeaponToCharacter(AActor* weapon);

	UFUNCTION()
	bool CanGetWeapon();

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class USTLCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Attack)
	bool bIsAttackCheck;

	UPROPERTY()
	TArray<AActor*> HittedActor;

private:
	UPROPERTY(VisibleAnywhere, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsAttacking;
	UPROPERTY(VisibleAnywhere, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bCanNextCombo;
	UPROPERTY(VisibleAnywhere, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsComboInput;
	UPROPERTY(VisibleAnywhere, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;
	UPROPERTY(VisibleAnywhere, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;
	UPROPERTY(VisibleAnywhere, Category = Attack, Meta = (AllowPrivateAccess = true))
	float damage = 10.f;
};