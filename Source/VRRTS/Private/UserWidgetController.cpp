// Fill out your copyright notice in the Description page of Project Settings.

#include "VRRTS.h"
#include "UserWidgetController.h"


void UUserWidgetController::SetPortrait(UTexture* portrait) {
	SelectionPortrait = portrait;
}

void UUserWidgetController::SetUIElements(AVRRTSSelectable* SelectedEntity) {
	if (SelectedEntity) {
		SetPortrait(SelectedEntity->SelectionPortrait);
		if (SelectedEntity->IsA(ABuilding::StaticClass())) {
			TArray<AUnit*> UnitObjects;
			for (TSubclassOf<class AUnit> unit : Cast<ABuilding>(SelectedEntity)->BuildableUnits) {
				AUnit* UnitObject = Cast<AUnit>(unit->GetDefaultObject());
				UnitObjects.Add(UnitObject);
			}
			if (UnitObjects.Num() > 0) {
				SetUnitData(UnitObjects);
			}
		} else if (SelectedEntity->IsA(AUnit::StaticClass())) {
			TArray<ABuilding*> BuildingObjects;
			for (TSubclassOf<class ABuilding> Building : Cast<AUnit>(SelectedEntity)->BuildableBuildings) {
				ABuilding* BuildingObject = Cast<ABuilding>(Building->GetDefaultObject());
				BuildingObjects.Add(BuildingObject);
			}
			if (BuildingObjects.Num() > 0) {
				SetBuildingData(BuildingObjects);
			}
		}
	} else {
		SetPortrait(NULL);
		Clear();
	}
}

void UUserWidgetController::SetMCVector(FVector2D Vec) {
	UpdateMCVector(Vec);
}

void UUserWidgetController::SetThumbstickPressed(FVector2D Vec) {
	UpdateThumbstickPressed(Vec);
}

void UUserWidgetController::SetUnitData(TArray<AUnit*> Units) {
	UpdateUnitButtons(Units);
}

void UUserWidgetController::SetBuildingData(TArray<ABuilding*> Buildings) {
	UpdateBuildingButtons(Buildings);
}

void UUserWidgetController::SendUnitSpawnInformation(AUnit* unit) {
	AVRRTSPlayerController* PC = Cast<AVRRTSPlayerController>(GetOwningPlayer());
	if (PC) {
		PC->SpawnUnit(unit);
	}
}

void UUserWidgetController::SendBuildingSpawnInformation(ABuilding* building) {
	AVRRTSPlayerController* PC = Cast<AVRRTSPlayerController>(GetOwningPlayer());
	if (PC) {
		PC->SpawnBuilding(building);
	}
}