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

	GetOwner()->AttachToComponent(Character->GetFPVMesh(), AttachmentRules, FName(TEXT("AttachSocket")));

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

	bCanFire = true;

}

void UUnrealFPS_SkeletalMeshComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr) return;


}

void UUnrealFPS_SkeletalMeshComponent::Fire()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Cyan, TEXT("Tried to fire"));

	if (!bCanFire) return;

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Emerald, TEXT("FIRE!"));

	if (Projectile == nullptr) return;

	UWorld* World = GetWorld();

	if (World == nullptr) return;

	const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();

	auto txt = GetOwner()->GetName();

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, txt);

	const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(GuntipOffset);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	World->SpawnActor<AActor>(Projectile, SpawnLocation, SpawnRotation, ActorSpawnParams);

	bCanFire = false;

	World->GetTimerManager().SetTimer(FireTimerHandle, this, &UUnrealFPS_SkeletalMeshComponent::SetCanFireToTrue, FireCooldown);
}

void UUnrealFPS_SkeletalMeshComponent::SetCanFireToTrue()
{
	bCanFire = true;
}
