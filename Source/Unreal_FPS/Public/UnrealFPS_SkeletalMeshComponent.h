// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unreal_FPS/Character/FPSCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "UnrealFPS_SkeletalMeshComponent.generated.h"

class AFPSCharacter;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class UNREAL_FPS_API UUnrealFPS_SkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

	AFPSCharacter* Character;

	UFUNCTION(Blueprintable, Category = "Object")
	void AttachComponentToPlayer(AFPSCharacter* TargetCharacter);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
