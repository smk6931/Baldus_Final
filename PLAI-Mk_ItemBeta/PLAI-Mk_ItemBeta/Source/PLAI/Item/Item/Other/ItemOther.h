// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PLAI/Item/Item/Item.h"
#include "ItemOther.generated.h"

UCLASS()
class PLAI_API AItemOther : public AItem
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AItemOther();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
