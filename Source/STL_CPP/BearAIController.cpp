// Fill out your copyright notice in the Description page of Project Settings.


#include "BearAIController.h"
#include "BehaviorTree/BehaviorTree.h" //����� ��Ŭ����ϰ� �����ϸ� ��ũ������ �ߴµ�, ��� ���� ����̶�� ������ �ְ�, �����̺��Ʈ���� ����� AIModule ��⿡ �ְ�, �̰Ŵ� �⺻������ �߰��� �ȵǾ��ֱ� ������ ������Ʈ��.Build.cs�� PublicDependencyModuleNames.AddRange�� "AIModule"�� �߰�������Ѵ�.
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "STLCppCharacter.h"

ABearAIController::ABearAIController()
{
	//����Ǿ���� �ڵ�
	Blackboard = MyBlackboard; //�̰� �극�� ������Ʈ�� Get���� �� nullptr�� ���ͼ� ����

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB_Data(TEXT("BlackboardData'/Game/Bear/AI/BB_Bear.BB_Bear'"));
	if (BB_Data.Succeeded()) {
		BB = BB_Data.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_Data(TEXT("BehaviorTree'/Game/Bear/AI/BT_Bear.BT_Bear'"));
	if (BT_Data.Succeeded()) {
		BT = BT_Data.Object;
	}

}
void ABearAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABearAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BB, MyBlackboard))
	{
		UE_LOG(LogTemp, Warning, TEXT("Set BlackBoard"));
	}

	//BT ������
	if (!RunBehaviorTree(BT))
	{
		UE_LOG(LogTemp, Warning, TEXT("Run BT Error"));
	}
}

void ABearAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABearAIController::SetTarget(APawn* InPawn)
{
	auto TargetCharacter = Cast<ASTLCppCharacter>(InPawn);
	if (TargetCharacter)
	{
		Blackboard->SetValueAsObject(TEXT("TargetActor"), TargetCharacter);
	}
}