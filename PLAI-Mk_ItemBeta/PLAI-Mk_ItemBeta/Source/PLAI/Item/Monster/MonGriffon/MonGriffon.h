﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PLAI/Item/Monster/MonsterMaster.h"
#include "MonGriffon.generated.h"

UCLASS()
class PLAI_API AMonGriffon : public AMonsterMaster
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonGriffon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
