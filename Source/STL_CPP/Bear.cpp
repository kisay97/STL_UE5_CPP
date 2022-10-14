// Fill out your copyright notice in the Description page of Project Settings.


#include "Bear.h"
#include "AnimInstanceBear.h"

// Sets default values
ABear::ABear()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentHP = MaxHP = 100.f;

	// ĸ�� ����
	GetCapsuleComponent()->SetCapsuleRadius(88.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	// �� �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_Mesh(TEXT("/Game/Bear/Enemy_Bear.Enemy_Bear"));
	if (SM_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Mesh.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));

	// �ִ� ���� ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> CF_AnimInstance(TEXT("AnimBlueprint'/Game/Bear/ABP_Bear.ABP_Bear_C'"));
	if (CF_AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CF_AnimInstance.Class);
	}
}

// Called when the game starts or when spawned
void ABear::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABear::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

float ABear::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHP = FMath::Clamp(CurrentHP - Damage, 0.f, MaxHP);
	if (CurrentHP <= 0)
	{
		// TODO: �״� �ִϸ��̼� ���, �ݸ��� ����, �ִϸ��̼� ��� ������ �װ��ϱ�
		Destroy();
	}

	return 0.0f;
}

// Called every frame
void ABear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABear::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

