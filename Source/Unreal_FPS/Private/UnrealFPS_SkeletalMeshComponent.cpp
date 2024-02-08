// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealFPS_SkeletalMeshComponent.h"

void UUnrealFPS_SkeletalMeshComponent::AttachComponentToPlayer(AFPSCharacter* TargetCharacter)
{
	Character = TargetCharacter;

	if (Character == nullptr || Character->GetHasWeapon()) return;

	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	AttachToComponent(Character->GetMeshFPV(), AttachmentRules, FName(TEXT("AttachSocket")));

	Character->SetHasWeapon(true);
	
}

void UUnrealFPS_SkeletalMeshComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr) return;


}