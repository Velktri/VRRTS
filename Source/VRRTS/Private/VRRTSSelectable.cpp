// Fill out your copyright notice in the Description page of Project Settings.

#include "VRRTS.h"
#include "VRRTSPawnMovementComponent.h"
#include "VRRTSSelectable.h"


// Sets default values
AVRRTSSelectable::AVRRTSSelectable(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UVRRTSPawnMovementComponent>(TEXT("Unit Movement Component"))) 
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnMovement = CreateDefaultSubobject<UVRRTSPawnMovementComponent>(TEXT("CustomMovementComponent"));
	PawnMovement->UpdatedComponent = RootComponent;
	bIsMoving = false;
}

// Called when the game starts or when spawned
void AVRRTSSelectable::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AVRRTSSelectable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AVRRTSSelectable::SetPlayerController(AVRRTSPlayerController* PC) {
	if (PC) {
		PlayerController = PC;
	}
}

void AVRRTSSelectable::OnSelected(AVRRTSPlayerController* APC) {
	if (SelectionDecal) {
		SelectionDecal->SetHiddenInGame(false);
	}

	//AVRRTSPlayerController* PC = Cast<AVRRTSPlayerController>(APC);
	//if (PC) {
	//	ARTSHUD* hud = Cast<ARTSHUD>(PC->GetHUD());
	//	if (hud) {
	//		hud->SetSelectionTexture(SelectionPortrait);
	//		if (GetOwningController() == PC) {
	//			hud->SetBuildableUnits(BuildableUnits);
	//		} else {
	//			hud->ClearButtons();
	//		}
	//	}
	//}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Selected: " + Name);
}

void AVRRTSSelectable::OnDeselected() {
	if (SelectionDecal) {
		SelectionDecal->SetHiddenInGame(true);
	}
}

UVRRTSPawnMovementComponent* AVRRTSSelectable::GetUnitMovement() {
	return PawnMovement;
}