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

	SetupPlayerHeight();
	SetupMontionControllers();
}

// Called every frame
void AVRRTSHMDPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//if (bIsLeftPressed) {
	//	SelectedEntity = LeftController->LineTraceFunction(DeltaTime);
	//}

	//if (bIsRightPressed) {
	//	SelectedEntity = RightController->LineTraceFunction(DeltaTime);
	//}
}

#pragma region Inputs
void AVRRTSHMDPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);
	InputComponent->BindAction("LeftTrigger", EInputEvent::IE_Pressed, this, &AVRRTSHMDPawn::LeftTriggerPressed);
	InputComponent->BindAction("LeftTrigger", EInputEvent::IE_Released, this, &AVRRTSHMDPawn::LeftTriggerReleased);

	InputComponent->BindAction("RightTrigger", EInputEvent::IE_Pressed, this, &AVRRTSHMDPawn::RightTriggerPressed);
	InputComponent->BindAction("RightTrigger", EInputEvent::IE_Released, this, &AVRRTSHMDPawn::RightTriggerReleased);
}

void AVRRTSHMDPawn::LeftTriggerPressed() {
	//bIsLeftPressed = true;
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
	//bIsRightPressed = true;
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