// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBox.h"
#include "Weapon.h"
#include "STLCppCharacter.h"

// Sets default values
AItemBox::AItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = Box;
	Trigger->SetupAttachment(Box);
	Trigger->SetBoxExtent(FVector(15.f,15.f,10.f));
	Trigger->SetRelativeLocation(FVector(0, 0, 7.f));
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorScale3D(FVector(5.f, 5.f, 5.f));

	// ����ƽ �޽� �ε� �� ����
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Box(TEXT("/Game/ItemBox/Meshes/Props/SM_MerchantShip_Storagebox_01.SM_MerchantShip_Storagebox_01")); //�����Ϳ��� �ּ� ��Ŭ�� > ���۷��� ��� �����ϰ� Static''�� ����
	if (SM_Box.Succeeded())
	{
		Box->SetStaticMesh(SM_Box.Object);
	}

	WeaponClass = AWeapon::StaticClass();
}

void AItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AItemBox::OnCharacterOverlap);
}

// Called when the game starts or when spawned
void AItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("AItemBox::OnCharacterOverlap"));

	auto character = Cast<ASTLCppCharacter>(OtherActor);
	if (character != nullptr && character->CanGetWeapon())
	{
		character->AddWeaponToCharacter(GetWorld()->SpawnActor<AWeapon>(WeaponClass));
		//������ �ڽ��� ��ȸ���� ��� �ڽ� ����
		Destroy();
	}
}