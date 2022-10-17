// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "AIController.h"
#include "BearAIController.generated.h"

/**
 * 
 */
UCLASS()
class STL_CPP_API ABearAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ABearAIController();

	virtual void PostInitializeComponents() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION()
	void SetTarget(APawn* InPawn);

private:
	UPROPERTY()
	class UBehaviorTree* BT;

	UPROPERTY()
	class UBlackboardData* BB;

	UPROPERTY()
	UBlackboardComponent* MyBlackboard;
};