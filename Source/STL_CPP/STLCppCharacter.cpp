// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "STLCppCharacter.h"

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
	// -- �ִ� ���� ���� ��
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