// Fill out your copyright notice in the Description page of Project Settings.


#include "Fountain.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // 액터 틱 활성화 여부

	// CDO는 생성자에서 해야함.
	// ConstructorHelpers는 생성자 쪽에서만 쓸 수 있음.
	// 런타임에선 런타임용 관리자가 따로 있음.

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));

	//컴포넌트 탭에서의 계층구조
	RootComponent = Body;
	//setupattachment
	Water->SetupAttachment(Body);

	// 스테틱 메시 로드 후 지정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Game/Fountain/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01")); //에디터에서 애셋 우클릭 > 레퍼런스 경로 복사하고 Static''만 지움
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Water(TEXT("/Game/Fountain/SM_Plains_Fountain_02.SM_Plains_Fountain_02")); //에디터에서 애셋 우클릭 > 레퍼런스 경로 복사하고 Static''만 지움
	if (SM_Water.Succeeded())
	{
		Water->SetStaticMesh(SM_Water.Object);
	}

	// 워터 상대좌표 조정
	Water->SetRelativeLocation(FVector(0.f, 0.f, 140.f));
}

// Called when the game starts or when spawned
void AFountain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Body->AddWorldRotation(FRotator(0, RotationSpeed * DeltaTime, 0));
}

