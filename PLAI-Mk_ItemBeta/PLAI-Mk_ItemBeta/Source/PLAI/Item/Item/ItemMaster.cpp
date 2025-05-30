// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMaster.h"

#include "Net/UnrealNetwork.h"


// Sets default values
AItemMaster::AItemMaster()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AItemMaster::BeginPlay()
{
	Super::BeginPlay();

	float Vec = FVector::DotProduct(GetActorForwardVector(), GetActorRightVector());
}

// Called every frame
void AItemMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemMaster::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

