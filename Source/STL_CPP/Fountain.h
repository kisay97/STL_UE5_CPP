// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h" //엔진이 켜지는데 필요한 필수적인 요소. 뭔가 필요한 기능을 만들라 치면 EngineMinimal.h 바꾸는 경우가 많음
//#include "EngineMinimal.h"
#include "STL_CPP.h"
#include "GameFramework/Actor.h"
#include "Fountain.generated.h"

UCLASS()
class STL_CPP_API AFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Water;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 30.f;
};
