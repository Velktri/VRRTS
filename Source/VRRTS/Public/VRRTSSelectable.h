// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "VRRTS.h"
#include "VRRTSPawnMovementComponent.h"
#include "VRRTSSelectable.generated.h"

UCLASS()
class VRRTS_API AVRRTSSelectable : public APawn
{
	GENERATED_BODY()

public:
	AVRRTSSelectable(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = System)
		AVRRTSPlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay | Component")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay | Resourses")
		int32 Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay | Resourses")
		int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Mesh")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Materials")
		UDecalComponent* SelectionDecal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components | Materials")
		UTexture* SelectionPortrait;

	void SetPlayerController(AVRRTSPlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = "OnClick")
	void OnSelected(AVRRTSPlayerController* APC);

	UFUNCTION(BlueprintCallable, Category = "OnClick")
	void OnDeselected();

	UVRRTSPawnMovementComponent* GetUnitMovement();

	class UVRRTSPawnMovementComponent* PawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay | Component")
	bool bCanMove;

	bool bIsMoving;
};
