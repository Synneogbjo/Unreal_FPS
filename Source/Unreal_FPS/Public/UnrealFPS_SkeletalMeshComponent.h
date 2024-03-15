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

public:

	UUnrealFPS_SkeletalMeshComponent();

	AFPSCharacter* Character;

	UFUNCTION(Blueprintable, BlueprintCallable, Category = "Object")
	void AttachComponentToPlayer(AFPSCharacter* TargetCharacter);

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/*
	 * IMC and Actions
	 */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* FireIMC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FireAction;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Firing")
	TSubclassOf<UObject> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	FVector GuntipOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Firing")
	float FireCooldown;

	bool bCanFire;

	FTimerHandle FireTimerHandle;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void SetCanFireToTrue();

};
