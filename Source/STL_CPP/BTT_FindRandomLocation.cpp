// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindRandomLocation.h"
#include "NavigationSystem.h" //헤더만 인클루드하고 빌드하면 링크에러가 뜨는데, 헤더 위에 모듈이라는 개념이 있고, 네비게이션 시스템 헤더는 NavigationSystem 모듈에 있고, 이거는 기본적으로 추가가 안되어있기 때문에 프로젝트명.Build.cs에 PublicDependencyModuleNames.AddRange에 "NavigationSystem"을 추가해줘야한다.
#include "BearAIController.h" //ExecuteTask에 OwnerComp 파라미터의 UBehaivorTreeComponent 클래스를 몰라해서 넣어줌.
#include "BehaviorTree/BlackboardComponent.h" //OwnerComp.GetBlackboardComponent() 쪽에서 BlackboardComponent 클래스를 몰라해서 넣어줌.

UBTT_FindRandomLocation::UBTT_FindRandomLocation()
{
	NodeName = TEXT("FindRandomLocation"); //BT에서 어떤 이름으로 보여줄지 결정하는듯.
}

EBTNodeResult::Type UBTT_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory); //이거도 슈퍼 안해주면 post intialize components 슈퍼 안하면 에디터 에러나는 것처럼 (얘는 에디터 에러까진 아닌데) 비헤이비어 트리가 안돈다고 함.

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	if (Pawn == nullptr) // !Pawn, Pawn.IsValidLowLevel(), ::Valid(Pawn) 도 가능
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

	// 위 if 안타면 네비시스템에서 에러나서 랜덤 로케이션을 못잡은거라 실패처리
	return EBTNodeResult::Failed;
}