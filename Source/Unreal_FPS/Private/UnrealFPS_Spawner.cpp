// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealFPS_Spawner.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AUnrealFPS_Spawner::AUnrealFPS_Spawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnCooldown = 10.f;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(GetRootComponent());
	SpawnArea->SetCollisionProfileName("Trigger");

}

// Called when the game starts or when spawned
void AUnrealFPS_Spawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AUnrealFPS_Spawner::SpawnActorInArea, SpawnCooldown, true);
	
}

// Called every frame
void AUnrealFPS_Spawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUnrealFPS_Spawner::SpawnActorInArea() const
{
	const auto BoundingBox = SpawnArea->GetScaledBoxExtent();

	const FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->GetComponentLocation(), BoundingBox);
	const FRotator SpawnRotation = SpawnArea->GetComponentRotation();

	GetWorld()->SpawnActor<AActor>(SpawnedActor, SpawnLocation, SpawnRotation);
}