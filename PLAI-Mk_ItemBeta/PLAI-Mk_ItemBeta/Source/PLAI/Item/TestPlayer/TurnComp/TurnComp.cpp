﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TurnComp.h"

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PLAI/Item/TestPlayer/TestPlayer.h"
#include "PLAI/Item/UI/Turn/UiTurn.h"


// Sets default values for this component's properties
UTurnComp::UTurnComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTurnComp::BeginPlay()
{
	Super::BeginPlay();

	UiTurn = CreateWidget<UUiTurn>(GetWorld(),UiTurnFactory);
	UiTurn->AddToViewport();
	UiTurn->SetVisibility(ESlateVisibility::Hidden);
	
	// UiTurn->TurnName->SetVisibility(ESlateVisibility::Hidden);
	
	TestPlayer = Cast<ATestPlayer>(GetOwner());
}


// Called every frame
void UTurnComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

