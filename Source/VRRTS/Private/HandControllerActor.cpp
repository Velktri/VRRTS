// Fill out your copyright notice in the Description page of Project Settings.

#include "VRRTS.h"
#include "HandControllerActor.h"


// Sets default values
AHandControllerActor::AHandControllerActor() {
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	MotionControl = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	VRChaperone = CreateDefaultSubobject<USteamVRChaperoneComponent>(TEXT("VRChaperone"));
	LineTrace = CreateDefaultSubobject<UArrowComponent>(TEXT("Line Trace"));
	UIContainer = CreateDefaultSubobject<UChildActorComponent>(TEXT("UI Container"));

	Scene->SetupAttachment(RootComponent);
	MotionControl->SetupAttachment(Scene);
	Mesh->SetupAttachment(MotionControl);
	LineTrace->SetupAttachment(Mesh);
	UIContainer->SetupAttachment(Mesh);


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ControllerMesh(TEXT("SkeletalMesh'/Game/SkeletalMesh/Controller.Controller'"));

	if (ControllerMesh.Object) {
		SkeletalMesh = Cast<USkeletalMesh>(ControllerMesh.Object);
	}

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHandControllerActor::BeginPlay() {
	Super::BeginPlay();
	
	//ChaperoneBounds = VRChaperone->GetBounds();
	if (SkeletalMesh) {
		Mesh->SetSkeletalMesh(SkeletalMesh);
	}
}

// Called every frame
void AHandControllerActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

FHitResult AHandControllerActor::TraceUI() {
	UWorld* World = GetWorld();
	FHitResult HitObjects = FHitResult(ForceInit);
	if (World) {
		FVector StartVector = Mesh->GetSocketLocation("LineTraceSocket");
		FVector EndVector = (FRotationMatrix(Mesh->GetSocketRotation("LineTraceSocket")).GetScaledAxis(EAxis::Z) * -1500) + StartVector;

		DrawDebugLine(World, StartVector, EndVector, FColor(255, 0, 0), true, 0.1f, 0, 0.1f);
		World->LineTraceSingleByChannel(HitObjects, StartVector, EndVector, COLLISION_USERMENU);
	}
	return HitObjects;
}

FHitResult AHandControllerActor::TraceSelectable() {
	UWorld* World = GetWorld();
	FHitResult HitObjects = FHitResult(ForceInit);
	if (World) {
		FVector StartVector = Mesh->GetSocketLocation("LineTraceSocket");
		FVector EndVector = (FRotationMatrix(Mesh->GetSocketRotation("LineTraceSocket")).GetScaledAxis(EAxis::Z) * -1500) + StartVector;

		DrawDebugLine(World, StartVector, EndVector, FColor(0, 255, 0), true, 0.1f, 0, 0.1f);
		World->LineTraceSingleByChannel(HitObjects, StartVector, EndVector, COLLISION_SELECTABLE);
	}
	return HitObjects;
}

FHitResult AHandControllerActor::TraceFloor() {
	UWorld* World = GetWorld();
	FHitResult HitObjects = FHitResult(ForceInit);
	if (World) {
		FVector StartVector = Mesh->GetSocketLocation("LineTraceSocket");
		FVector EndVector = (FRotationMatrix(Mesh->GetSocketRotation("LineTraceSocket")).GetScaledAxis(EAxis::Z) * -1500) + StartVector;

		DrawDebugLine(World, StartVector, EndVector, FColor(0, 0, 255), true, 0.1f, 0, 0.1f);
		World->LineTraceSingleByChannel(HitObjects, StartVector, EndVector, COLLISION_GROUND);
	}
	return HitObjects;
}

void AHandControllerActor::SetUIContainer(TSubclassOf<class AActor> InWidget, UUserWidgetController* InUIWidget) {
	if (InWidget) {
		UIContainer->SetChildActorClass(InWidget);
		UIContainer->CreateChildActor();

		UWidgetComponent* UIWidgetComponent = Cast<UWidgetComponent>(UIContainer->GetChildActor()->GetComponentByClass(UWidgetComponent::StaticClass()));
		if (UIWidgetComponent) {
			UIWidget = InUIWidget;
			UIWidgetComponent->SetWidget(InUIWidget);
		}
	}
}

UUserWidgetController* AHandControllerActor::GetUIWidget() {
	return UIWidget;
}

