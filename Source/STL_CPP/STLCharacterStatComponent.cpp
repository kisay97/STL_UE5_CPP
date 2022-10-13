// Fill out your copyright notice in the Description page of Project Settings.


#include "STLCharacterStatComponent.h"

// Sets default values for this component's properties
USTLCharacterStatComponent::USTLCharacterStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void USTLCharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USTLCharacterStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void USTLCharacterStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

