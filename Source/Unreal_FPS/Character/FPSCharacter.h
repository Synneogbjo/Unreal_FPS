// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "FPSCharacter.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class UCameraComponent;

UCLASS()
class UNREAL_FPS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	 * Components
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UCameraComponent* FPVCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* FPVMesh;

	/*
	 * Input Mapping Context and Actions
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input");
	UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAtAction;

	void Move(const FInputActionValue& value);
	void LookAt(const FInputActionValue& value);

	void Jump(const FInputActionValue& value);
	void StopJumping(const FInputActionValue& value);

	/*
	 * Weapon
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bHasWeapon;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetHasWeapon(bool bNewHasWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetHasWeapon();

	USkeletalMeshComponent* GetFPVMesh() const;

	UCameraComponent* GetFPVCameraComponent() const;


	//		!!! TUTORIAL STUFF, MIGHT DELETE LATER !!!
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void SpawnActor();

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> actorBPToSpawn;
};
