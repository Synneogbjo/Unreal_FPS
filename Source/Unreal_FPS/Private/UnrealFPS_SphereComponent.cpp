// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealFPS_SphereComponent.h"

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
	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if (Character != nullptr)
	{
		OnPickUp.Broadcast(Character);

		OnComponentBeginOverlap.RemoveAll(this);
	}
}
