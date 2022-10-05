// Fill out your copyright notice in the Description page of Project Settings.


#include "Fountain.h"

// Sets default values
AFountain::AFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; // ���� ƽ Ȱ��ȭ ����

	// CDO�� �����ڿ��� �ؾ���.
	// ConstructorHelpers�� ������ �ʿ����� �� �� ����.
	// ��Ÿ�ӿ��� ��Ÿ�ӿ� �����ڰ� ���� ����.

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));

	//������Ʈ �ǿ����� ��������
	RootComponent = Body;
	//setupattachment
	Water->SetupAttachment(Body);

	// ����ƽ �޽� �ε� �� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Game/Fountain/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01")); //�����Ϳ��� �ּ� ��Ŭ�� > ���۷��� ��� �����ϰ� Static''�� ����
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Water(TEXT("/Game/Fountain/SM_Plains_Fountain_02.SM_Plains_Fountain_02")); //�����Ϳ��� �ּ� ��Ŭ�� > ���۷��� ��� �����ϰ� Static''�� ����
	if (SM_Water.Succeeded())
	{
		Water->SetStaticMesh(SM_Water.Object);
	}

	// ���� �����ǥ ����
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

