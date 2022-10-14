// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class STL_CPP_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Collision;

	float dir;
	float currentYaw;
	float targetYaw;
	float tempAlpha = 0.0f;
	bool bIsOpenning = false;

private:
	void checkDir();
	void openDynamicGate(float alpha);
	void closeDynamicGate(float alpha);
};
