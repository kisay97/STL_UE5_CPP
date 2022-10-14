// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "GameFramework/Character.h"
#include "Bear.generated.h"

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

	UPROPERTY(VisibleAnywhere)
	float CurrentHP;

	UPROPERTY(VisibleAnywhere)
	float MaxHP;

public:
	UPROPERTY()
	class UAnimInstanceBear* AnimInstance;

private:
};
