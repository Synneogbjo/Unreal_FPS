// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealFPS_SkeletalMeshComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

UUnrealFPS_SkeletalMeshComponent::UUnrealFPS_SkeletalMeshComponent()
{
	GuntipOffset = FVector(100.f, 0.f, 20.f);
}

void UUnrealFPS_SkeletalMeshComponent::AttachComponentToPlayer(AFPSCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	if (Character == nullptr || Character->GetHasWeapon()) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	AttachToComponent(Character->GetFPVMesh(), AttachmentRules, FName(TEXT("AttachSocket")));

	Character->SetHasWeapon(true);

	// Adding the input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireIMC, 1);
		}

		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);

		if (!EnhancedInputComponent) return;

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UUnrealFPS_SkeletalMeshComponent::Fire);
	}

}

void UUnrealFPS_SkeletalMeshComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr) return;


}

void UUnrealFPS_SkeletalMeshComponent::Fire()
{
	if (Projectile == nullptr) return;

	UWorld* World = GetWorld();

	if (World == nullptr) return;

	const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(GuntipOffset);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	World->SpawnActor<AActor>(Projectile, SpawnLocation, SpawnRotation, ActorSpawnParams);
}