// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_BearAttack.h"
#include "BearAIController.h"

UBTT_BearAttack::UBTT_BearAttack()
{
	NodeName = (TEXT("BEAR Attack"));
	bNotifyTick = true;
}

EBTNodeResult::Type UBTT_BearAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO
	// 1. 공격 실행 Bear->Attack();
	// 2. finish 호출 불가
	// 3. return::InProgress
	return EBTNodeResult::Type();
}

void UBTT_BearAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}