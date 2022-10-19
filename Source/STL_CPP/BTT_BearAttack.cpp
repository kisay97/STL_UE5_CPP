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
	// 1. ���� ���� Bear->Attack();
	// 2. finish ȣ�� �Ұ�
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
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); //latent : �����ִ�. ������ �½�ũ�� �ǴϽ� ��Ų��.
	//}
}