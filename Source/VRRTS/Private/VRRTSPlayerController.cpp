// Fill out your copyright notice in the Description page of Project Settings.

#include "VRRTS.h"
#include "VRRTSPlayerController.h"

AVRRTSPlayerController::AVRRTSPlayerController() {
	Race = ERace::Human;

	switch (Race) {
	case ERace::Human:
	{
		static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Blueprints/Buildings/Castle_BP.Castle_BP'"));
		if (ItemBlueprint.Object) {
			StartBuilding = (UClass*)ItemBlueprint.Object->GeneratedClass;
		}
		break;
	}
	default:
		break;
	}
}

void AVRRTSPlayerController::BeginPlay() {
	Super::BeginPlay();
	VRHMD = Cast<AVRRTSHMDPawn>(GetPawn());
}

void AVRRTSPlayerController::CreateStartBuilding(FVector SpawnPoint, UWorld* World) {
	SpawnPoint.Z = 0;
	FActorSpawnParameters SpawnParams;
	ABuilding* Building = World->SpawnActor<ABuilding>(StartBuilding, SpawnPoint, FRotator(0, 0, 0), SpawnParams);
	if (Building) {
		Building->SetPlayerController(this);
	}
}

void AVRRTSPlayerController::SetSelectedEntity(AVRRTSSelectable* Selected) {
	ClearSelection();
	SelectedEntities = Selected;
	if (VRHMD) {
		VRHMD->SetUIElements(SelectedEntities);
		Selected->OnSelected(this);		
	}
}

void AVRRTSPlayerController::ClearSelection() {
	if (SelectedEntities) {
		SelectedEntities->OnDeselected();
		VRHMD->SetUIElements(NULL);
		SelectedEntities = NULL;
	}
}

void AVRRTSPlayerController::SpawnUnit(AUnit* unit) {
	if (unit && SelectedEntities/*CurrentSelection[0]*/->IsA(ABuilding::StaticClass())) {
		ABuilding* building = Cast<ABuilding>(SelectedEntities/*CurrentSelection[0]*/);
		FVector SpawnPoint = building->GetActorLocation();
		SpawnPoint.X -= 70.0f;
		AUnit* NewUnit = GetWorld()->SpawnActor<AUnit>(unit->GetClass(), SpawnPoint, FRotator::ZeroRotator);
		if (NewUnit) {
			NewUnit->PlayerController = this;
			OwnedUnits.Add(NewUnit);
		} else {
			CreationFailed(Cast<AVRRTSSelectable>(unit));
		}
	}
}

void AVRRTSPlayerController::SpawnBuilding(ABuilding* building) {
	if (building && SelectedEntities/*CurrentSelection[0]*/->IsA(AUnit::StaticClass())) {
		AUnit* unit = Cast<AUnit>(SelectedEntities/*CurrentSelection[0]*/);
		FVector SpawnPoint = unit->GetActorLocation();
		SpawnPoint.X -= 70.0f;
		ABuilding* NewBuilding = GetWorld()->SpawnActor<ABuilding>(building->GetClass(), SpawnPoint, FRotator::ZeroRotator);
		if (NewBuilding) {
			NewBuilding->PlayerController = this;
			OwnedBuildings.Add(NewBuilding);
		} else {
			CreationFailed(Cast<AVRRTSSelectable>(building));
		}
	}
}

void AVRRTSPlayerController::SendMovementCommands(FVector Location) {
	if (SelectedEntities && SelectedEntities->IsA(AUnit::StaticClass())) {
		Cast<AUnit>(SelectedEntities)->Move(Location);
	}
}

void AVRRTSPlayerController::CreationFailed(AVRRTSSelectable* selectable) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Failed to Build " + selectable->Name);
}