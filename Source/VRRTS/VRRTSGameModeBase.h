// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "VRRTS.h"
#include "VRRTSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VRRTS_API AVRRTSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVRRTSGameModeBase();
	virtual void BeginPlay() override;
	
	
};
