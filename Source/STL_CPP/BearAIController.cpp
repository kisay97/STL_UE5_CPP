// Fill out your copyright notice in the Description page of Project Settings.


#include "BearAIController.h"
#include "BehaviorTree/BehaviorTree.h" //헤더만 인클루드하고 빌드하면 링크에러가 뜨는데, 헤더 위에 모듈이라는 개념이 있고, 비헤이비어트리쪽 헤더는 AIModule 모듈에 있고, 이거는 기본적으로 추가가 안되어있기 때문에 프로젝트명.Build.cs에 PublicDependencyModuleNames.AddRange에 "AIModule"을 추가해줘야한다.
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "STLCppCharacter.h"

ABearAIController::ABearAIController()
{
	//변경되어야할 코드
	Blackboard = MyBlackboard; //이게 브레인 컴포넌트를 Get했을 때 nullptr이 나와서 덮음

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

	//BT 돌리기
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