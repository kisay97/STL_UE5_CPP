// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_BearAttack.generated.h"

/**
 * 
 */
UCLASS()
class STL_CPP_API UBTT_BearAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_BearAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
