// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "VRRTSPlayerController.generated.h"

UENUM(BlueprintType)
enum class ERace : uint8 {
	Human		UMETA(DisplayName = "Human"),
	Orc			UMETA(DisplayName = "Orc"),
};

UCLASS()
class VRRTS_API AVRRTSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AVRRTSPlayerController();

	virtual void BeginPlay() override;
	
	/** Player's Race */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Race)
	ERace Race;

	/** Start Building */
	TSubclassOf<class ABuilding> StartBuilding;

	/** Generate Player's Start Building */
	void CreateStartBuilding(FVector SpawnPoint, UWorld* World);

	void SetSelectedEntity(AVRRTSSelectable* Selected);
	void ClearSelection();

	void SpawnUnit(AUnit* unit);
	void SpawnBuilding(ABuilding* building);
	void SendMovementCommands(FVector Location);

private:
	/* Players HMD */
	class AVRRTSHMDPawn* VRHMD;
	class AVRRTSSelectable* SelectedEntities;
	TArray<class AUnit*> OwnedUnits;
	TArray<class ABuilding*> OwnedBuildings;

	void CreationFailed(AVRRTSSelectable* selectable);
};
