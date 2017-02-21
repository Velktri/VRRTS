// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "VRRTSHMDPawn.h"
#include "Building.h"
#include "Unit.h"
#include "VRRTSSelectable.h"
#include "VRRTSPlayerController.h"
#include "HandControllerActor.h"
#include "MotionControllerComponent.h"
#include "SteamVRChaperoneComponent.h"

#define COLLISION_USERMENU			ECC_GameTraceChannel1
#define COLLISION_GROUND			ECC_GameTraceChannel2
#define COLLISION_SELECTABLE		ECC_GameTraceChannel3