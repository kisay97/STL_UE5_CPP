// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "STL_CPP.h"
#include "BehaviorTree/BTTaskNode.h" // �굵 "GameplayTasks" ��� �߰��ؾ���.
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
