// Fill out your copyright notice in the Description page of Project Settings.


#include "MonSpawn.h"

#include "Blueprint/UserWidget.h"
#include "PLAI/Item/Monster/Monster.h"
#include "PLAI/Item/Monster/MonsterMaster.h"
#include "Templates/Function.h"
#include "WorldPartition/WorldPartitionSubsystem.h"

// Sets default values
AMonSpawn::AMonSpawn()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMonSpawn::BeginPlay()
{
	Super::BeginPlay();

	TArray<FName>RawNames = MonsterTable->GetRowNames();
	for (FName RawName : RawNames)
	{
		FMonsterStruct* MonsterStruct = MonsterTable->FindRow<FMonsterStruct>(RawName, "MonSpawn65");
		if (MonsterStruct && MonsterStruct->MonsterTop == static_cast<int32>(MonSpawnType))
		{
			MonsterFactory.Add(MonsterStruct->MonsterFactory[0]);
		}
	}
}

// Called every frame
void AMonSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += GetWorld()->GetDeltaSeconds();
	if (CurrentTime >= 2)
	{
		SpawnMonster();
		CurrentTime = 0;
	}
}

FVector AMonSpawn::RandLocation(float X, float Y, float Z)
{
	float x = FMath::RandRange(-X, X);
	float y = FMath::RandRange(-Y, Y);
	float z = FMath::RandRange(0.0f, Z);
	return FVector(x, y, z);
}

void AMonSpawn::SpawnMonster()
{
	MonsterFactory.Empty();
	Monsters.RemoveAll([](const TWeakObjectPtr<AMonster>& Monster)
	{
		return !Monster.IsValid();
	});
	if (Monsters.Num() > 7) return;
	
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FVector Start = GetActorLocation() + RandLocation() + FVector(0,0,1500);
	FVector End = Start + FVector(0,0,-10000);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit,Start,End,ECC_GameTraceChannel1,Params);
	if (bHit)
	{
		TArray<FName>RawNames = MonsterTable->GetRowNames();
		for (FName RawName : RawNames)
		{
			FMonsterStruct* MonsterStruct = MonsterTable->FindRow<FMonsterStruct>(RawName, "MonSpawn65");
			if (MonsterStruct && MonsterStruct->MonsterTop == static_cast<int32>(MonSpawnType))
			{
				MonsterFactory.Add(MonsterStruct->MonsterFactory[0]);
				int32 RandIndex = FMath::RandRange(0,MonsterFactory.Num()-1);

				if (AMonster* Monster = GetWorld()->SpawnActor<AMonster>(MonsterFactory[RandIndex]))
				{
					Monster->MonsterStruct = *MonsterStruct;
					Monster->SetMonsterUi();
					Monster->SetActorLocation(Hit.Location);
					Monsters.Add(Monster);
				}
			}
		}
		
		

		// FActorSpawnParameters SpawnParams;
		// SpawnParams.Owner = this;
		// SpawnParams.Instigator = GetInstigator();
		// SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	}
	
	// MyTimer([this]()
	// {
	// 	Monsters.RemoveAll([](const TWeakObjectPtr<AMonster>& WeakM){return !WeakM.IsValid();});
	// 	
	// 	FHitResult Hit;
	// 	FCollisionQueryParams Params;
	// 	Params.AddIgnoredActor(this);
	// 	FVector Start = GetActorLocation() + RandLocation(1000,1000) + FVector(0, 0, 1500);
	// 	FVector End = Start + FVector(0,0, -10000);
	// 	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start,End,ECC_Visibility,Params);
	// 	if (bHit)
	// 	{
	// 		if (Monsters.Num() > 6)return;
	// 		TArray<FName>Raws = MonsterTable->GetRowNames();
	// 		for (FName Raw : Raws)
	// 		{
	// 			FMonsterStruct* MonsterStruct = MonsterTable->FindRow<FMonsterStruct>(Raw,TEXT("MonSpawn"));
	// 			if (MonsterStruct && MonsterStruct->MonsterTop == static_cast<int32>(MonSpawnType))
	// 			{
	// 				MonsterFactory.Add(MonsterStruct->MonsterFactory[0]);
	// 				int32 RandIndex = FMath::RandRange(0, Monsters.Num() - 1);
	// 			
	// 				FActorSpawnParameters SpawnParams;
	// 				SpawnParams.Owner = this;
	// 				SpawnParams.Instigator = GetInstigator();
	// 				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// 				
	// 				if (AMonsterMaster* MonsterMaster = GetWorld()->SpawnActor<AMonsterMaster>(MonsterFactory[RandIndex],
	// 					Hit.Location,FRotator(0,0,0),SpawnParams))
	// 				{
	// 					MonsterMaster->MonsterStruct = *MonsterStruct;
	// 					MonsterMaster->SetMonsterUi();
	// 					Monsters.Add(MonsterMaster);
	// 				}
	// 			}
	// 		}
	// 	}
	// },1.5);

	
}


// FMonsterStruct* MonsterStruct = MonsterTable->FindRow<FMonsterStruct>(Raw,TEXT("MonSpawn"));
// if (MonsterStruct && MonsterStruct->MonsterTop == 0)
// {
// 	MonsterFactory.Add(MonsterStruct->MonsterFactory[0]);
// 	int32 RandIndex = FMath::RandRange(0, Monsters.Num() - 1);
//
// 	FActorSpawnParameters SpawnParams;
// 	SpawnParams.Owner = this;
// 	SpawnParams.Instigator = GetInstigator();
// 	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
// 	
// 	if (AMonsterMaster* MonsterMaster = GetWorld()->SpawnActor<AMonsterMaster>(MonsterFactory[RandIndex],
// 		Hit.Location,FRotator(0,0,0),SpawnParams))
// 	{
// 		MonsterMaster->MonsterStruct = *MonsterStruct;
// 		MonsterMaster->SetMonsterUi();
// 		Monsters.Add(MonsterMaster);
// 	}
// }

// DrawDebugLine(GetWorld(),Start,Hit.ImpactPoint,FColor::Red,false,1.5f);
// DrawDebugSphere(GetWorld(),Hit.ImpactPoint,20,10,FColor::Blue,false,1.5f);


// UWorldPartitionSubsystem* WPS = GetWorld()->GetSubsystem<UWorldPartitionSubsystem>();
// WPS->OnU
// WPS->OnActorLoaded.AddUObject(this, &AMonSpawn::MyTimer);
// WPS->OnActorUnloaded.AddUObject(this, &AMonSpawn::HandleActorUnloaded);








// void AMonSpawn::MyTimer(TFunction<void()> Func, float Second)
// {
// 	bTimer = false;
// 	CurrentTime += GetWorld()->GetDeltaSeconds();
// 	if (CurrentTime >= Second)
// 	{
// 		bTimer = true;
// 		Func();
// 		CurrentTime = 0.0f;
// 	}
// }