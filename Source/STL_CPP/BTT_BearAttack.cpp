// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_BearAttack.h"
#include "BearAIController.h"
#include "Bear.h"

UBTT_BearAttack::UBTT_BearAttack()
{
	NodeName = (TEXT("BEAR Attack"));
	//bNotifyTick = true;
}

EBTNodeResult::Type UBTT_BearAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type r = Super::ExecuteTask(OwnerComp, NodeMemory);

	// TODO
	// 1. 공격 실행 Bear->Attack();
	// 2. finish 호출 불가
	// 3. return::InProgress
	auto ControlledBear = Cast<ABear>(OwnerComp.GetAIOwner()->GetPawn());
	if (ControlledBear)
	{
		ControlledBear->PlayAttackMontage();
		ControlledBear->OnAttackEnded.AddLambda([&]() {
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

void UBTT_BearAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	//auto ControlledBear = Cast<ABear>(OwnerComp.GetAIOwner()->GetPawn());
	//if (!ControlledBear->IsAttacking)
	//{
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); //latent : 숨어있는. 마지막 태스크를 피니시 시킨다.
	//}
}