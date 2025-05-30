﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreBullet.generated.h"

UCLASS()
class PLAI_API ACreBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACreBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* NiagaraComp;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* ProjectileComp;
};
