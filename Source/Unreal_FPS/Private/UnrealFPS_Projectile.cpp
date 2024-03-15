// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealFPS_Projectile.h"

#include "UnrealFPS_Enemy.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AUnrealFPS_Projectile::AUnrealFPS_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1000.f;

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerSphere"));
	TriggerSphere->SetCollisionProfileName("Trigger");
	TriggerSphere->SetSphereRadius(100.f);
	TriggerSphere->SetupAttachment(GetRootComponent());

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AUnrealFPS_Projectile::OnOverlapBegin);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(TriggerSphere);
}

// Called when the game starts or when spawned
void AUnrealFPS_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnrealFPS_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnrealFPS_Projectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetCollisionProfileName() == "Trigger") return;

	if (OtherActor->IsA<AUnrealFPS_Enemy>())
	{
		Cast<AUnrealFPS_Enemy>(OtherActor)->TakeDamage(1.f);

		Destroy();
	}
}
