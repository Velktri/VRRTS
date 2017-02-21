// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VRRTSSelectable.h"
#include "VRRTS.h"
#include "Building.generated.h"

class AVRRTSPlayerController;
/**
 * 
 */
UCLASS()
class VRRTS_API ABuilding : public AVRRTSSelectable
{
	GENERATED_BODY()
	
public:

	ABuilding(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay | Component")
	TArray<TSubclassOf<class AUnit>> BuildableUnits;
};
