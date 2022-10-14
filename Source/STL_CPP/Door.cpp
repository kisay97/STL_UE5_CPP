// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "STLCppCharacter.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//기본 컴포넌트 생성
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Gate"));
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));

	//컴포넌트 계층구조 지정
	Body->SetupAttachment(RootComponent);
	Collision->SetupAttachment(RootComponent);

	//박스콜리전 위치 지정
	Collision->SetRelativeLocation(FVector(0.f, 80.f, 40.f));
	Collision->SetBoxExtent(FVector(100.f, 80.f, 40.f));

	//문 메시 지정
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Game/StaticMesh/SM_GATE.SM_GATE"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOpenning)
	{
		if (tempAlpha < 1)
		{
			tempAlpha = FMath::Clamp(tempAlpha + DeltaTime, 0, 1);
			openDynamicGate(tempAlpha);
		}
	}
	else
	{
		if (tempAlpha > 0)
		{
			tempAlpha = FMath::Clamp(tempAlpha - DeltaTime, 0, 1);
			closeDynamicGate(tempAlpha);
		}
	}
}

void ADoor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnComponentBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnComponentEndOverlap);
}

void ADoor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f,
		FColor::Cyan,
		FString::Printf(TEXT("ADoor::OnComponentBeginOverlap")));

	const auto player = Cast<ASTLCppCharacter>(OtherActor);
	if (player)
	{
		checkDir();
		currentYaw = Body->GetRelativeRotation().Yaw;
		targetYaw = 90.0f;
		tempAlpha = 0.0f;
		bIsOpenning = true;
	}
}

void ADoor::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.f,
		FColor::Cyan,
		FString::Printf(TEXT("ADoor::OnComponentEndOverlap")));

	const auto player = Cast<ASTLCppCharacter>(OtherActor);
	if (player)
	{
		currentYaw = Body->GetRelativeRotation().Yaw;
		targetYaw = 0.0f;
		tempAlpha = 1.0f;
		bIsOpenning = false;
	}
}

void ADoor::checkDir()
{
	FVector base = GetActorLocation() - UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();
	base.Normalize();
	float angleWithPlayer = base.Dot(GetActorForwardVector());
	if (angleWithPlayer >= 0)
	{
		dir = -1.0f;
	}
	else
	{
		dir = 1.0f;
	}
}

void ADoor::openDynamicGate(float alpha)
{
	float turnningYaw = UKismetMathLibrary::Lerp(currentYaw, dir * targetYaw, alpha);
	Body->SetRelativeRotation(FRotator(0.f, turnningYaw, 0.f));
}

void ADoor::closeDynamicGate(float alpha)
{
	float turnningYaw = UKismetMathLibrary::Lerp(targetYaw, currentYaw, alpha);
	Body->SetRelativeRotation(FRotator(0.f, turnningYaw, 0.f));
}

