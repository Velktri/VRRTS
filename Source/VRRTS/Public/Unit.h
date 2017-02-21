// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VRRTSSelectable.h"
#include "Unit.generated.h"

/**
 * 
 */
UCLASS()
class VRRTS_API AUnit : public AVRRTSSelectable
{
	GENERATED_BODY()

public:
	AUnit(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay | Component")
	TArray<TSubclassOf<class ABuilding>> BuildableBuildings;

	UFUNCTION()
	void Move(FVector NewLocation);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay | Component")
	float MovementSpeed;

	FVector JourneyLocation;
};
