// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "VRRTSPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class VRRTS_API UVRRTSPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:

	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
};
