// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "VRRTS.h"
#include "UserWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class VRRTS_API UUserWidgetController : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingame HUD")
	UTexture* SelectionPortrait;

	UFUNCTION(BlueprintCallable, Category = "Selection Portrait")
	void SetPortrait(UTexture* portrait);

	UFUNCTION()
	void SetUIElements(AVRRTSSelectable* SelectedEntity);

	UFUNCTION()
	void SetMCVector(FVector2D Vec);

	UFUNCTION()
	void SetThumbstickPressed(FVector2D Vec);

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void UpdateThumbstickPressed(FVector2D vec);

	UFUNCTION(BlueprintImplementableEvent, Category = "Selection")
	void Clear();

	UFUNCTION(BlueprintImplementableEvent, Category = "Selection")
	void UpdateUnitButtons(const TArray<AUnit*>& Units);

	UFUNCTION(BlueprintImplementableEvent, Category = "Input")
	void UpdateMCVector(FVector2D vec);

	UFUNCTION(BlueprintImplementableEvent, Category = "Selection")
	void UpdateBuildingButtons(const TArray<ABuilding*>& Buildings);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void SendUnitSpawnInformation(AUnit* unit);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void SendBuildingSpawnInformation(ABuilding* building);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void SetUnitData(TArray<AUnit*> Units);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void SetBuildingData(TArray<ABuilding*> Buildings);
};
