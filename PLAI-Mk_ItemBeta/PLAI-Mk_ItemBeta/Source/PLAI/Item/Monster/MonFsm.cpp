// Fill out your copyright notice in the Description page of Project Settings.


#include "MonFsm.h"
#include "Monster.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UMonFsm::UMonFsm()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMonFsm::BeginPlay()
{
	Super::BeginPlay();
	Monster = Cast<AMonster>(GetOwner());
}

// Called every frame
void UMonFsm::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Monster->HasAuthority())
	{
		switch (MonState)
		{
		case EMonState::Idle:
			Idle();
			break;
		case EMonState::Around:
			Around();
			break;
		case EMonState::Attack:
			Attack();
			break;
		}
	}
}

void UMonFsm::Idle()
{
	CurrentTime += GetWorld()->GetDeltaSeconds();
	if (CurrentTime > 1)
	{
		MonState = EMonState::Around;
		LineDestination();
		InitLocation = TargetLocation;
		FVector Vec = TargetLocation = Monster->GetActorLocation();
		Monster->SetActorRotation(Vec.GetSafeNormal().Rotation());
		CurrentTime = 0;
	}
}

void UMonFsm::Around()
{
	MoveDestination();
}

void UMonFsm::Attack()
{
}

FVector UMonFsm::RandLocation(float X, float Y, float Z)
{
	float x = FMath::RandRange(-X, X);
	float y = FMath::RandRange(-Y, Y);
	float z = FMath::RandRange(0.0f, Z);
	return FVector(x,y,z);
}


void UMonFsm::MoveDestination()
{
	FHitResult Hit = LineTraceResult(Monster->GetActorLocation());
	
	if (FVector::Distance(Monster->GetActorLocation(), Hit.ImpactPoint))
	{
		if (Monster->GetActorLocation().Z > Hit.ImpactPoint.Z)
		{
			Monster->AddActorLocalOffset(FVector(0,0,-5),false);
		}
		else
		{
			Monster->AddActorLocalOffset(FVector(0,0,5),false);
		}
	}
	FVector Distance = TargetLocation - Monster->GetActorLocation();
	if (Distance.Length() > 75)
	{
		FRotator Rotator = UKismetMathLibrary::MakeRotFromYZ(Monster->GetActorRightVector(),Hit.ImpactNormal);
		FRotator LerpRotator = UKismetMathLibrary::RLerp(Monster->GetActorRotation(),Rotator,GetWorld()->GetDeltaSeconds() * 5.0f,true);
		Monster->SetActorRotation(LerpRotator);
	}
	Monster->AddActorWorldOffset(Distance.GetSafeNormal()*10,false);

	if (Distance.Length() < 75)
	{
		LineDestination();
		if (FVector::Distance(TargetLocation,InitLocation) > InitLocationFloat)
		{
			FVector NewLoc = InitLocation - Monster->GetActorLocation();
			NewLoc.Normalize();
			TargetLocation = Monster->GetActorLocation() + NewLoc * 1500;
		}
		bRotator = true;
	}
	if (bRotator == true)
	{
		CurrentTime += GetWorld()->DeltaTimeSeconds;
		FRotator LerpRotator = UKismetMathLibrary::RLerp(Monster->GetActorRotation(), Distance.GetSafeNormal().Rotation(),
		CurrentTime / 2.5, true);
		Monster->SetActorRotation(LerpRotator);
		if (CurrentTime > 2.5)
		{
			CurrentTime = 0.0f;
			bRotator = false;
		}
	}
}

void UMonFsm::LineDestination()
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Monster);

	FVector Start = Monster->GetActorLocation() + RandLocation(RandLocationFloat,RandLocationFloat) + FVector(0,0,2000);
	FVector End = Start + FVector(0,0, -10000);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit,Start,End,ECC_GameTraceChannel1,Params);
	if(bHit)
	{
		TargetLocation = Hit.ImpactPoint;
	}
}

FHitResult UMonFsm::LineTraceResult(FVector Location)
{
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Monster);
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit,Location+FVector(0,0,1000),
		Location+FVector(0,0,-1000),ECC_GameTraceChannel1,Params);
	if(bHit)
	{
		return Hit;
	}
	else
	{
		return FHitResult();
	}
}




// DrawDebugLine(GetWorld(),Start,TargetLocation,FColor::Red,false,2.0f);
// DrawDebugSphere(GetWorld(),TargetLocation,10,10,FColor::Red,false,2.0f);


// UE_LOG(LogTemp,Warning,TEXT("MonFsm 초시계 %f"),CurrentTime)


