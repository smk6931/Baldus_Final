// Fill out your copyright notice in the Description page of Project Settings.


#include "CreBullet.h"

#include "CreFsm.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/SphereComponent.h"
#include "Dragon/CreDraFsm.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PLAI/Item/Monster/Monster.h"


// Sets default values
ACreBullet::ACreBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(RootComponent);
	
	NiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("AudioComponent"));
	NiagaraComp->SetupAttachment(RootComponent);

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleComp");
	ParticleComp->SetupAttachment(RootComponent);
	
	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileComp->InitialSpeed = 1000.0f;
	ProjectileComp->MaxSpeed = 2000.0f;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(RootComponent);
	
	ProjectileComp->bRotationFollowsVelocity = true;
	ProjectileComp->bShouldBounce = false;
}

// Called when the game starts or when spawned
void ACreBullet::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ACreBullet::OnMyBeginOverlapped);
}

// Called every frame
void ACreBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACreBullet::OnMyBeginOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMonster* Monster = Cast<AMonster>(OtherActor))
	{
		UE_LOG(LogTemp,Warning,TEXT("CreBullet 몬스터가 맞았음"))
		CreDraFsm->AttackMonster(Monster);
		UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
		CreDraFsm->NiagaraSkills[1],Monster->GetActorLocation(),FRotator::ZeroRotator,FVector(2.f),true, // AutoActivate                        
		true,// AutoDestroy
		ENCPoolMethod::AutoRelease);
		NiagaraComponent->SetActive(true);
		Destroy();
	}
	else
	{
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,[this]()
		{ Destroy(); },3.0f, false);
	}
}

