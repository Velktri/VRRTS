// Fill out your copyright notice in the Description page of Project Settings.

#include "VRRTS.h"
#include "VRRTSHMDPawn.h"


// Sets default values
AVRRTSHMDPawn::AVRRTSHMDPawn()
{
	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	VROrigin->SetupAttachment(RootComponent);
	Camera->SetupAttachment(VROrigin);

	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<AHandControllerActor> HandBPClass(TEXT("/Game/Blueprints/HandControllerActor_BP"));
	if (HandBPClass.Class != nullptr) {
		HandBlueprint = HandBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AActor> LeftWidgetBPClass(TEXT("/Game/UI/Left_WidgetContainer"));
	static ConstructorHelpers::FClassFinder<AActor> RightWidgetBPClass(TEXT("/Game/UI/Right_WidgetContainer"));
	LeftWidgetContainer = (LeftWidgetBPClass.Succeeded()) ? LeftWidgetBPClass.Class : nullptr;
	RightWidgetContainer = (RightWidgetBPClass.Succeeded()) ? RightWidgetBPClass.Class : nullptr;


	static ConstructorHelpers::FClassFinder<UUserWidget> LeftWidgetControllerOBJ(TEXT("/Game/UI/LeftUserWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> RightWidgetControllerOBJ(TEXT("/Game/UI/RIghtUserWidget"));
	LeftWidgetClass = (LeftWidgetControllerOBJ.Succeeded()) ? LeftWidgetControllerOBJ.Class : nullptr;
	RightWidgetClass = (RightWidgetControllerOBJ.Succeeded()) ? RightWidgetControllerOBJ.Class : nullptr;

}

// Called when the game starts or when spawned
void AVRRTSHMDPawn::BeginPlay() {
	Super::BeginPlay();

	ThumbDeadZone = 0.7;
	SetupPlayerHeight();
	SetupMontionControllers();
}

// Called every frame
void AVRRTSHMDPawn::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

	SetMCRotation();
}

#pragma region Inputs
void AVRRTSHMDPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);
	InputComponent->BindAction("LeftTrigger", EInputEvent::IE_Pressed, this, &AVRRTSHMDPawn::LeftTriggerPressed);
	InputComponent->BindAction("LeftTrigger", EInputEvent::IE_Released, this, &AVRRTSHMDPawn::LeftTriggerReleased);

	InputComponent->BindAction("RightTrigger", EInputEvent::IE_Pressed, this, &AVRRTSHMDPawn::RightTriggerPressed);
	InputComponent->BindAction("RightTrigger", EInputEvent::IE_Released, this, &AVRRTSHMDPawn::RightTriggerReleased);

	InputComponent->BindAction("RightThumbstick", EInputEvent::IE_Released, this, &AVRRTSHMDPawn::RightThumbstickReleased);
	InputComponent->BindAction("LeftThumbstick", EInputEvent::IE_Released, this, &AVRRTSHMDPawn::LeftThumbstickReleased);

	InputComponent->BindAxis("MC_Left_Y", this, &AVRRTSHMDPawn::MCLeftY);
	InputComponent->BindAxis("MC_Left_X", this, &AVRRTSHMDPawn::MCLeftX);
	InputComponent->BindAxis("MC_Right_Y", this, &AVRRTSHMDPawn::MCRightY);
	InputComponent->BindAxis("MC_Right_X", this, &AVRRTSHMDPawn::MCRightX);
}

void AVRRTSHMDPawn::LeftTriggerPressed() {

}

void AVRRTSHMDPawn::LeftTriggerReleased() {
	FHitResult SelectedEntity = LeftController->TraceUI();
	if (SelectedEntity.bBlockingHit) {
		LeftController->SendUIClick();
	} else {
		SelectedEntity = LeftController->TraceSelectable();
		if (SelectedEntity.bBlockingHit) {
			AVRRTSSelectable* Selected = Cast<AVRRTSSelectable>(SelectedEntity.Actor.Get());
			if (Selected) {
				GetPlayerController()->SetSelectedEntity(Selected);
			}
		} else {
			SelectedEntity = LeftController->TraceFloor();
			if (SelectedEntity.bBlockingHit) {
				GetPlayerController()->SendMovementCommands(SelectedEntity.Location);
			} else {
				GetPlayerController()->ClearSelection();
			}
		}
	}
}

void AVRRTSHMDPawn::RightTriggerPressed() {

}

void AVRRTSHMDPawn::RightTriggerReleased() {
	FHitResult SelectedEntity = RightController->TraceUI();
	if (SelectedEntity.bBlockingHit) {
		RightController->SendUIClick();
	} else {
		SelectedEntity = RightController->TraceSelectable();
		if (SelectedEntity.bBlockingHit) {
			// do building/unit things
			AVRRTSSelectable* Selected = Cast<AVRRTSSelectable>(SelectedEntity.Actor.Get());
			if (Selected) {
				GetPlayerController()->SetSelectedEntity(Selected);
			}
		} else {
			SelectedEntity = RightController->TraceFloor();
			if (SelectedEntity.bBlockingHit) {
				GetPlayerController()->SendMovementCommands(SelectedEntity.Location);
			} else {
				GetPlayerController()->ClearSelection();
			}
		}
	}
}

void AVRRTSHMDPawn::LeftThumbstickReleased() {
	if (FMath::Abs(LeftX) + FMath::Abs(LeftY) >= ThumbDeadZone) {
		LeftController->GetUIWidget()->SetThumbstickPressed(FVector2D(LeftX, LeftY));
	} else {
		LeftController->GetUIWidget()->SetThumbstickPressed(FVector2D(0.0f, 0.0f));
	}
}

void AVRRTSHMDPawn::RightThumbstickReleased() {
	if (FMath::Abs(RightX) + FMath::Abs(RightY) >= ThumbDeadZone) {
		RightController->GetUIWidget()->SetThumbstickPressed(FVector2D(RightX, RightY));
	} else {
		RightController->GetUIWidget()->SetThumbstickPressed(FVector2D(0.0f, 0.0f));
	}
}

void AVRRTSHMDPawn::MCLeftY(float Amount) {
	LeftY = Amount;
}

void AVRRTSHMDPawn::MCLeftX(float Amount) {
	LeftX = Amount;
}

void AVRRTSHMDPawn::MCRightY(float Amount) {
	RightY = Amount;
}

void AVRRTSHMDPawn::MCRightX(float Amount) {
	RightX = Amount;
}

#pragma endregion

void AVRRTSHMDPawn::SetupPlayerHeight() {
	FName HMDName = UHeadMountedDisplayFunctionLibrary::GetHMDDeviceName();

	if (HMDName == "SteamVR") {
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	}
}

void AVRRTSHMDPawn::SetupMontionControllers() {
	UWorld* World = GetWorld();
	FVector Location = FVector(0, 0, 0);
	FRotator Rotation = FRotator(0, 0, 0);

	if (World && HandBlueprint) {
		FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, false);
		AttachRules.ScaleRule = EAttachmentRule::KeepWorld;

		LeftController = World->SpawnActor<AHandControllerActor>(HandBlueprint, Location, Rotation);
		LeftController->AttachToComponent(VROrigin, AttachRules);
		LeftController->MotionControl->Hand = EControllerHand::Left;
		UUserWidgetController* LeftWidget = (UUserWidgetController*)CreateWidget<UUserWidget>(GetPlayerController(), this->LeftWidgetClass);
		LeftController->SetUIContainer(LeftWidgetContainer, LeftWidget);

		RightController = World->SpawnActor<AHandControllerActor>(HandBlueprint, Location, Rotation);
		RightController->AttachToComponent(VROrigin, AttachRules);
		RightController->MotionControl->Hand = EControllerHand::Right;
		UUserWidgetController* RightWidget = (UUserWidgetController*)CreateWidget<UUserWidget>(GetPlayerController(), this->RightWidgetClass);
		RightController->SetUIContainer(RightWidgetContainer, RightWidget);
	}
}

AVRRTSPlayerController* AVRRTSHMDPawn::GetPlayerController() {
	return Cast<AVRRTSPlayerController>(GetController());
}


void AVRRTSHMDPawn::SetUIElements(AVRRTSSelectable* SelectedEntity) {
	RightController->GetUIWidget()->SetUIElements(SelectedEntity);
	LeftController->GetUIWidget()->SetUIElements(SelectedEntity);
}

void AVRRTSHMDPawn::SetMCRotation() {
	if (FMath::Abs(LeftX) + FMath::Abs(LeftY) >= ThumbDeadZone) {
		LeftController->GetUIWidget()->SetMCVector(FVector2D(LeftX, LeftY));
	} else {
		LeftController->GetUIWidget()->SetMCVector(FVector2D(0.0f, 0.0f));
	}

	if (FMath::Abs(RightX) + FMath::Abs(RightY) >= ThumbDeadZone) {
		RightController->GetUIWidget()->SetMCVector(FVector2D(RightX, RightY));
	} else {
		RightController->GetUIWidget()->SetMCVector(FVector2D(0.0f, 0.0f));
	}
}
