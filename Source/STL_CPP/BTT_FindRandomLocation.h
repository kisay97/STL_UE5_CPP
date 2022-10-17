// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "BehaviorTree/BTTaskNode.h" // 얘도 "GameplayTasks" 모듈 추가해야함.
#include "BTT_FindRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class STL_CPP_API UBTT_FindRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_FindRandomLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
