// Fill out your copyright notice in the Description page of Project Settings.


#include "Bear.h"
#include "AnimInstanceBear.h"
#include "BearAIController.h"
#include "Perception/PawnSensingComponent.h"
#include "BrainComponent.h"

// Sets default values
ABear::ABear()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentHP = MaxHP = 100.f;
	GetCharacterMovement()->MaxWalkSpeed = 150.f;

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

	// �� AI ��Ʈ�ѷ� ����
	AIControllerClass = ABearAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// ������
	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 500.f;
	PawnSensing->SetPeripheralVisionAngle(45.f); //�¿� 45�� == �� 90��

	// Attack Montage ����
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

	// ������ ���� �ʱ�ȭ
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
		Die();
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
	if (!AnimInstance->IsAnyMontagePlaying()) //������ ������(���� �ִԸ�Ÿ�� �����)�� �� �� ������ �Ϸ��� �ϸ� ���� ������ �ߴܵǸ鼭 �̻������°� ����
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

void ABear::Die()
{
	// TODO: �״� �ִϸ��̼� ���, �ݸ��� ����, �ִϸ��̼� ��� ������ �װ��ϱ�
	// �ݸ��� ����
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// �������� ����� �����Ʈ ���߱�
	GetCharacterMovement()->StopMovementImmediately();

	// ������ ���� �����(��Ÿ�� ������̸� ���߰� �ٷ� �׵���)
	AnimInstance->StopAllMontages(0.f);

	// �׾��ٰ� �˸���(������ ��)
	OnBearDied.Broadcast();

	// �����̺�� Ʈ�� ���߱�
	auto aiController = Cast<ABearAIController>(GetController());
	if (aiController) {
		aiController->BrainComponent->StopLogic(TEXT("Death"));
	}

	// ���� �ִϸ��̼� ����ϴ°� ������ 3������ ��ٷȴٰ� Destroy ��.
	FTimerHandle DestroyHandle;
	float Delaytime = 3.f;
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda([&]() {
		Destroy();
	}), Delaytime, false);

}