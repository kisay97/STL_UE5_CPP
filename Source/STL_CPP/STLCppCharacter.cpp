// Fill out your copyright notice in the Description page of Project Settings.

#include "STLCppCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "STLAnimInstance.h"
#include "Weapon.h"
#include "DrawDebugHelpers.h"
#include "STLCharacterStatComponent.h"

// Sets default values
ASTLCppCharacter::ASTLCppCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// -- ĳ���� �޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM_Mesh(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Warrior.SK_CharM_Warrior"));
	if (SM_Mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM_Mesh.Object);
	}

	//GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	//GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88), FRotator(0, -90, 0));
	// -- ĳ���� �޽� ���� ��

	// -- ī�޶� ����
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 450.f;

	// ī�޶� ������ �̵� �и�(�ּ��� ���� �ߴ���, �ּ� ���Ѱ� �������� �ߴ���)
	//SpringArm->bUsePawnControlRotation = true;
	//bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate.Yaw = 540.f;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	// -- ī�޶� ���� ��

	// -- �ִ� ���� ����
	/*ConstructorHelpers::FClassFinder<UAnimInstance> SM_AnimInstance(TEXT("/Game/Animations/ABP_Character.ABP_Character"));
	GetMesh()->SetAnimInstanceClass(SM_AnimInstance.Class.Get());*/
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> SM_AnimInstance(TEXT("AnimBlueprint'/Game/Animations/ABP_Character.ABP_Character_C'"));
	if (SM_AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(SM_AnimInstance.Class);
	}

	//���� �� �ø���(800)
	GetCharacterMovement()->JumpZVelocity = 800.f;

	//2�� ���� �غ���?
	JumpMaxCount = 2;
	// -- �ִ� ���� ���� ��

	bIsAttacking = false;
	bIsAttackCheck = false;
	MaxCombo = 4;
	CurrentCombo = 0;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("StlCharacter"));

	CharacterStat = CreateDefaultSubobject<USTLCharacterStatComponent>(TEXT("CharacterStat"));
}

void ASTLCppCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StlAnim = Cast<USTLAnimInstance>(GetMesh()->GetAnimInstance());
	check(StlAnim != nullptr); //false�� ��� assert

	StlAnim->OnMontageEnded.AddDynamic(this, &ASTLCppCharacter::OnAttackMontageEnded);
	StlAnim->OnNextAttackCheck.AddLambda([this]()->void {
		bCanNextCombo = false;
		if (bIsComboInput)
		{
			AttackStartCombo();
			StlAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	});
}

// Called when the game starts or when spawned
void ASTLCppCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTLCppCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsAttackCheck)
	{
		AttackCheck();
	}
}

// Called to bind functionality to input
void ASTLCppCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//���Է� ���ε�
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ASTLCppCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASTLCppCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASTLCppCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ASTLCppCharacter::Turn);

	//�׼��Է� ���ε�?
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ASTLCppCharacter::Attack);
}

//Get Control Rotation return value z->Get Forward Vector in rot z
//Get Control Rotation return value z->Get Right Vector in rot z
void ASTLCppCharacter::MoveForward(float axis)
{
	//FRotationMatrix(FRotator(0, GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::X);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0, GetControlRotation().Yaw, 0)), axis);
}

void ASTLCppCharacter::MoveRight(float axis)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0, GetControlRotation().Yaw, 0)), axis);
}

void ASTLCppCharacter::LookUp(float axis)
{
	AddControllerPitchInput(axis);
}

void ASTLCppCharacter::Turn(float axis)
{
	AddControllerYawInput(axis);
}

void ASTLCppCharacter::Attack()
{
	//UE_LOG(LogTemp, Log, TEXT("LOG_ATTACK"));
	//StlAnim->PlayAttackMontage();

	if (bIsAttacking)
	{
		if (bCanNextCombo)
		{
			bIsComboInput = true;
		}
	}
	else
	{
		AttackStartCombo();
		StlAnim->PlayAttackMontage();
		StlAnim->JumpToAttackMontageSection(CurrentCombo);
		bIsAttacking = true;
	}
}

void ASTLCppCharacter::AttackStartCombo()
{
	bCanNextCombo = true;
	bIsComboInput = false;
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo+1, 1, MaxCombo);
}

void ASTLCppCharacter::AttackEndCombo()
{
	bCanNextCombo = false;
	bIsComboInput = false;
	CurrentCombo = 0;
}

void ASTLCppCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsAttacking = false;
	AttackEndCombo();
}

void ASTLCppCharacter::AddWeaponToCharacter(AActor* weapon)
{
	CurrentWeapon = Cast<AWeapon>(weapon);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetActorEnableCollision(false);
		CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("Weapon"));
		CurrentWeapon->SetOwner(this);
	}
}

bool ASTLCppCharacter::CanGetWeapon()
{
	if (!CurrentWeapon)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ASTLCppCharacter::AttackCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("ASTLCppCharacter::AttackCheck()"));

	TArray<FHitResult> results;
	FVector AttackStart = GetMesh()->GetSocketLocation(FName(TEXT("Attack_Start")));
	FVector AttackEnd = GetMesh()->GetSocketLocation(FName(TEXT("Attack_End")));
	
	// ���带 ���¹�
	/*bool bIsAnyHitted = GetWorld()->LineTraceMultiByChannel(results,
		AttackStart,
		AttackEnd,
		ECollisionChannel::ECC_GameTraceChannel1);
	DrawDebugLine(GetWorld(),
		AttackStart,
		AttackEnd,
		FColor::Red,
		false, 1.0f, 0U, 2.f);*/

	// Ű��� �ý��� ���̺귯���� ���¹�
	bool bIsAnyHitted = UKismetSystemLibrary::SphereTraceMulti(GetWorld(),
		AttackStart, AttackEnd, 25.f,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), //ECollisionChannel�� �޴°� �ƴ϶� ETraceTypeQuery�� �����Ƿ� UEngineTypes::ConvertToTraceType�� ����Ͽ� ��ȯ���ش�.
		false, HittedActor, EDrawDebugTrace::ForDuration, results, true);
	
	if (bIsAnyHitted)
	{
		for (const auto& result : results) //���� �ݺ����� �̷��� ����� Ÿ�Ӿƿ� �Ȱɸ��⿡ ����
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, 
				FColor::Cyan, 
				FString::Printf(TEXT("Hit: %s"), *result.GetActor()->GetName()));
			auto hitActor = result.GetActor();
			int32 bHitted = HittedActor.AddUnique(hitActor);
			if (bHitted)
			{
				UGameplayStatics::ApplyDamage(hitActor, CharacterStat->GetCharacterAttackDamage(), 
					UGameplayStatics::GetPlayerController(GetWorld(), 0), 
					this, nullptr);
			}
		}
	}

}