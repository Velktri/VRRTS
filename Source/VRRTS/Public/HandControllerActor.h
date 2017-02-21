// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "HandControllerActor.generated.h"

UCLASS()
class VRRTS_API AHandControllerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandControllerActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	USceneComponent* Scene;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	class UMotionControllerComponent* MotionControl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	USkeletalMeshComponent*	Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	UArrowComponent* LineTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	class USteamVRChaperoneComponent* VRChaperone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Bounds)
	TArray<FVector> ChaperoneBounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VR)
	UChildActorComponent* UIContainer;

	UFUNCTION(BlueprintCallable, Category = "Trace")
	FHitResult TraceUI();

	UFUNCTION(BlueprintCallable, Category = "Trace")
	FHitResult TraceSelectable();

	UFUNCTION(BlueprintCallable, Category = "Trace")
	FHitResult TraceFloor();

	UFUNCTION()
	void SetUIContainer(TSubclassOf<class AActor> UIWidget, UUserWidgetController* InUIWidget);

	UFUNCTION()
	UUserWidgetController* GetUIWidget();

	UFUNCTION(BlueprintImplementableEvent, Category = "Selection")
	void SendUIClick();

private:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VR)
	UUserWidgetController* UIWidget;
};
