// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealFPS_SphereComponent.h"
#include "Unreal_FPS/Character/FPSCharacter.h"

UUnrealFPS_SphereComponent::UUnrealFPS_SphereComponent()
{
	SphereRadius = 30.f;
}

void UUnrealFPS_SphereComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UUnrealFPS_SphereComponent::OnSphereBeginOverlap);
}

void UUnrealFPS_SphereComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, "Collided");

	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if (Character != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::White, "Picked up");

		OnPickUp.Broadcast(Character);

		OnComponentBeginOverlap.RemoveAll(this);
	}
}
