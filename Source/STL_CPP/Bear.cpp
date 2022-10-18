// Fill out your copyright notice in the Description page of Project Settings.


#include "Bear.h"
#include "AnimInstanceBear.h"
#include "BearAIController.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ABear::ABear()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentHP = MaxHP = 100.f;
	GetCharacterMovement()->MaxWalkSpeed = 150.f;

	// 캡슐 설정
	GetCapsuleComponent()->SetCapsuleRadius(88.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Enemy"));

	// 곰 메시 설정
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_Mesh(TEXT("/Game/Bear/Enemy_Bear.Enemy_Bear"));
	if (SM_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Mesh.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));

	// 애님 블프 세팅
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> CF_AnimInstance(TEXT("AnimBlueprint'/Game/Bear/ABP_Bear.ABP_Bear_C'"));
	if (CF_AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CF_AnimInstance.Class);
	}

	// 곰 AI 컨트롤러 설정
	AIControllerClass = ABearAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 폰센싱
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 500.f;
	PawnSensing->SetPeripheralVisionAngle(45.f); //좌우 45도 == 총 90도

	// Attack Montage 세팅
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Attack1(TEXT("AnimMontage'/Game/Bear/AM_Attack1.AM_Attack1'"));
	if (AM_Attack1.Succeeded())
	{
		Attack1 = AM_Attack1.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Attack2(TEXT("AnimMontage'/Game/Bear/AM_Attack2.AM_Attack2'"));
	if (AM_Attack2.Succeeded())
	{
		Attack2 = AM_Attack2.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM_Attack3(TEXT("AnimMontage'/Game/Bear/AM_Attack3.AM_Attack3'"));
	if (AM_Attack3.Succeeded())
	{
		Attack3 = AM_Attack3.Object;
	}

	// 공격중 변수 초기화
	IsAttacking = false;
}

// Called when the game starts or when spawned
void ABear::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABear::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensing->OnSeePawn.AddDynamic(this, &ABear::SetTarget);

	AnimInstance = Cast<UAnimInstanceBear>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &ABear::OnAttackMontageEnded);
}

float ABear::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHP = FMath::Clamp(CurrentHP - Damage, 0.f, MaxHP);
	if (CurrentHP <= 0)
	{
		// TODO: 죽는 애니메이션 재생, 콜리전 끄기, 애니메이션 재생 끝나고 죽게하기
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

void ABear::SetTarget(APawn* Pawn)
{
	if (!TargetPawn)
	{
		TargetPawn = Pawn;
		auto AIController = Cast<ABearAIController>(GetController());
		if (AIController)
		{
			AIController->SetTarget(Pawn);
		}
	}
}

void ABear::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

void ABear::Attack()
{
	if (!AnimInstance->IsAnyMontagePlaying()) //공격이 실행중(공격 애님몽타주 재생중)일 때 또 공격을 하려고 하면 이전 공격이 중단되면서 이상해지는걸 방지
	{
		IsAttacking = true;

		int attackType = FMath::RandRange(1, 3);
		switch (attackType)
		{
		case 1:
			AnimInstance->Montage_Play(Attack1);
			break;
		case 2:
			AnimInstance->Montage_Play(Attack2);
			break;
		case 3:
			AnimInstance->Montage_Play(Attack3);
			break;
		default:
			AnimInstance->Montage_Play(Attack1);
			break;
		}
	}
}