// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "UserWidgetController.h"
#include "VRRTSHMDPawn.generated.h"

UCLASS()
class VRRTS_API AVRRTSHMDPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRRTSHMDPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	USceneComponent* VROrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	UCameraComponent* Camera;

	UFUNCTION()
	void SetupPlayerHeight();

	UFUNCTION()
	void SetupMontionControllers();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	TSubclassOf<class AHandControllerActor> HandBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	AHandControllerActor* LeftController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	AHandControllerActor* RightController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	TSubclassOf<class AActor> LeftWidgetContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	TSubclassOf<class AActor> RightWidgetContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float ThumbDeadZone;

	UFUNCTION()
	void LeftTriggerPressed();

	UFUNCTION()
	void LeftTriggerReleased();

	UFUNCTION()
	void RightTriggerPressed();

	UFUNCTION()
	void RightTriggerReleased();

	UFUNCTION()
	void LeftThumbstickReleased();

	UFUNCTION()
	void RightThumbstickReleased();

	UFUNCTION()
	void MCLeftY(float Amount);

	UFUNCTION()
	void MCLeftX(float Amount);

	UFUNCTION()
	void MCRightY(float Amount);

	UFUNCTION()
	void MCRightX(float Amount);

	UFUNCTION()
	AVRRTSPlayerController* GetPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingame HUD")
	class UClass* LeftWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ingame HUD")
	class UClass* RightWidgetClass;

	UFUNCTION()
	void SetUIElements(AVRRTSSelectable* SelectedEntity);

	UFUNCTION()
	void SetMCRotation();

	float LeftX;
	float LeftY;
	float RightX;
	float RightY;
};
