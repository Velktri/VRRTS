// Fill out your copyright notice in the Description page of Project Settings.

#include "VRRTS.h"
#include "VRRTSGameModeBase.h"

AVRRTSGameModeBase::AVRRTSGameModeBase() {
	DefaultPawnClass = AVRRTSHMDPawn::StaticClass();
	PlayerControllerClass = AVRRTSPlayerController::StaticClass();
}

void AVRRTSGameModeBase::BeginPlay() {
	Super::BeginPlay();
	UWorld* const World = GetWorld();
	if (World) {
		for (FConstPlayerControllerIterator Iterator = World->GetPlayerControllerIterator(); Iterator; ++Iterator) {
			AVRRTSPlayerController* PlayerController = Cast<AVRRTSPlayerController>(Iterator->Get());
			if (PlayerController && PlayerController->IsA(AVRRTSPlayerController::StaticClass())) {
				AActor* PlayerStartPoint = FindPlayerStart(PlayerControllerClass.GetDefaultObject(), "PlayerStart");
				if (PlayerStartPoint) {
					PlayerController->CreateStartBuilding(PlayerStartPoint->GetActorLocation(), World);
				}
			}
		}
	}
}