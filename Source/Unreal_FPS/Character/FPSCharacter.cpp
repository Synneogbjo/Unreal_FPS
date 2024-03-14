// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Camera Component */
	FPVCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCamera"));
	FPVCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPVCameraComponent->bUsePawnControlRotation = true;

	/* Skeletal Mesh Component */
	FPVMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSMesh"));
	FPVMesh->SetupAttachment(FPVCameraComponent);

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	int num = 0;

	// Adding the input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EnhancedInputComponent) return;

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
	EnhancedInputComponent->BindAction(LookAtAction, ETriggerEvent::Triggered, this, &AFPSCharacter::LookAt);
}


void AFPSCharacter::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	if (!Controller) return;
	
	AddMovementInput(GetActorForwardVector(), MovementVector.Y * MoveSpeed.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X * MoveSpeed.X);

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::White, TEXT("Moving"));
}

void AFPSCharacter::LookAt(const FInputActionValue& value)
{
	FVector2D LookAroundVector = value.Get<FVector2D>();

	if (!Controller) return;
	
	AddControllerYawInput(LookAroundVector.X * CameraRotationSpeed.X);
	AddControllerPitchInput(LookAroundVector.Y * CameraRotationSpeed.Y);
	
}

void AFPSCharacter::SetHasWeapon(bool bNewHasWeapon)
{
	bHasWeapon = bNewHasWeapon;
}

bool AFPSCharacter::GetHasWeapon()
{
	return bHasWeapon;
}

USkeletalMeshComponent* AFPSCharacter::GetFPVMesh() const
{
	return FPVMesh;
}

UCameraComponent* AFPSCharacter::GetFPVCameraComponent() const
{
	return FPVCameraComponent;
}