// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealFPS_Spawner.generated.h"

class UBoxComponent;

UCLASS()
class UNREAL_FPS_API AUnrealFPS_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnrealFPS_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	 * Variables
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnCooldown;

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> SpawnedActor;

	/*
	 * Components
	 */

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* SpawnArea;

	/*
	 * Functions
	 */

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnActorInArea() const;

};
