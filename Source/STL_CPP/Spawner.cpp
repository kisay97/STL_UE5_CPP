// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Bear.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnCount = 0;
	MaxCount = 5;
	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Area->SetupAttachment(Root);
	SpawnClass = ABear::StaticClass();
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawner::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;
	if (ElapsedTime >= 5) {
		SpawnEnemy();
	}
}

void ASpawner::SpawnEnemy()
{
	FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), Area->GetScaledBoxExtent());
	if (SpawnCount < MaxCount)
	{
		auto SpawnedEnemy = GetWorld()->SpawnActor<ABear>(SpawnClass, FTransform(RandomLocation));
		if (SpawnedEnemy)
		{
			SpawnCount++;
			ElapsedTime = 0.f;
		}
	}
}