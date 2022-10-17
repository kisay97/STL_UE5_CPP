// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomLocation.h"
#include "NavigationSystem.h" //����� ��Ŭ����ϰ� �����ϸ� ��ũ������ �ߴµ�, ��� ���� ����̶�� ������ �ְ�, �׺���̼� �ý��� ����� NavigationSystem ��⿡ �ְ�, �̰Ŵ� �⺻������ �߰��� �ȵǾ��ֱ� ������ ������Ʈ��.Build.cs�� PublicDependencyModuleNames.AddRange�� "NavigationSystem"�� �߰�������Ѵ�.
#include "BearAIController.h" //ExecuteTask�� OwnerComp �Ķ������ UBehaivorTreeComponent Ŭ������ �����ؼ� �־���.
#include "BehaviorTree/BlackboardComponent.h" //OwnerComp.GetBlackboardComponent() �ʿ��� BlackboardComponent Ŭ������ �����ؼ� �־���.

UBTT_FindRandomLocation::UBTT_FindRandomLocation()
{
	NodeName = TEXT("FindRandomLocation"); //BT���� � �̸����� �������� �����ϴµ�.
}

EBTNodeResult::Type UBTT_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory); //�̰ŵ� ���� �����ָ� post intialize components ���� ���ϸ� ������ �������� ��ó�� (��� ������ �������� �ƴѵ�) �����̺�� Ʈ���� �ȵ��ٰ� ��.

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr) // !Pawn, Pawn.IsValidLowLevel(), ::Valid(Pawn) �� ����
	{
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(Pawn->GetWorld());
	if (NavSystem == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FNavLocation TargetLoc;
	if (NavSystem->GetRandomPointInNavigableRadius(Pawn->GetActorLocation(), 1000.f, TargetLoc))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomLocation"), TargetLoc.Location);
		return EBTNodeResult::Succeeded;
	}

	// �� if ��Ÿ�� �׺�ý��ۿ��� �������� ���� �����̼��� �������Ŷ� ����ó��
	return EBTNodeResult::Failed;
}