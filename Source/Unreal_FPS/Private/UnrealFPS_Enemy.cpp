// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealFPS_Enemy.h"

#include "AIController.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "Unreal_FPS/Character/FPSCharacter.h"

// Sets default values
AUnrealFPS_Enemy::AUnrealFPS_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	Health = 3.f;
	MovementSpeed = 200.f;
	Range = 500.f;

	RangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RangeSphere"));
	RangeSphere->SetCollisionProfileName("Trigger");
	RangeSphere->SetSphereRadius(Range);
	RangeSphere->SetupAttachment(GetRootComponent());

	RangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AUnrealFPS_Enemy::OnOverlapBegin);
	RangeSphere->OnComponentEndOverlap.AddDynamic(this, &AUnrealFPS_Enemy::OnOverlapEnd);

}

// Called when the game starts or when spawned
void AUnrealFPS_Enemy::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;

	AIController = Cast<AAIController>(GetController());

	RangeSphere->SetSphereRadius(Range);

}

// Called every frame
void AUnrealFPS_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target) AIMoveTowardsActor(Target);

}

// Called to bind functionality to input
void AUnrealFPS_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUnrealFPS_Enemy::AIMoveTowardsActor(const AActor* TargetActor) const
{
	if (!AIController) return;

	FAIMoveRequest AIMoveRequest;
	AIMoveRequest.SetGoalLocation(TargetActor->GetActorLocation());
	AIMoveRequest.SetAcceptanceRadius(25.f);

	FNavPathSharedPtr NavPath;

	AIController->MoveTo(AIMoveRequest, &NavPath);

	for (auto PathPoints = NavPath->GetPathPoints(); const FNavPathPoint Point : PathPoints)
	{
		const FVector CurrentLocation = Point.Location;
		UKismetSystemLibrary::DrawDebugSphere(this, CurrentLocation, 50.f, 8, FLinearColor::Green, 1.f, 1.f);
	}
}

void AUnrealFPS_Enemy::TakeDamage(float Damage)
{
	Health -= Damage;

	CheckIfDead();
}

void AUnrealFPS_Enemy::CheckIfDead()
{
	if (Health < 0.f) Destroy();
}

void AUnrealFPS_Enemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AFPSCharacter>()) Target = OtherActor;
}

void AUnrealFPS_Enemy::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA<AFPSCharacter>())
	{
		Target = nullptr;

		if (AIController) AIController->StopMovement();
	}
}

