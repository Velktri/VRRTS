// Fill out your copyright notice in the Description page of Project Settings.

#include "VRRTS.h"

#include "Unit.h"


// Sets default values
AUnit::AUnit (const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) 
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->CastShadow = true;
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionResponseToChannel(COLLISION_SELECTABLE, ECR_Block);

	SelectionDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("Selection Decal"));
	SelectionDecal->SetupAttachment(Mesh);
	SelectionDecal->AddLocalRotation(FRotator(-90, 0, 0));
	SelectionDecal->DecalSize = FVector(1, 2, 2);
	SelectionDecal->RelativeScale3D = FVector(1, 40, 40);
	SelectionDecal->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AUnit::BeginPlay() {
	Super::BeginPlay();
	JourneyLocation = GetActorLocation();
}

// Called every frame
void AUnit::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (bIsMoving) {
		if (PawnMovement && (PawnMovement->UpdatedComponent == RootComponent)) {
			FVector VectorDirection = (GetActorLocation() - JourneyLocation) * -1;
			VectorDirection.Normalize();

			PawnMovement->AddInputVector(VectorDirection * MovementSpeed);

			if (JourneyLocation.Equals(GetActorLocation(), MovementSpeed * 1.5)) {
				bIsMoving = false;
			}
		}
	}
}

// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	Super::SetupPlayerInputComponent(InputComponent);

}

void AUnit::Move(FVector NewLocation) {
	bIsMoving = true;
	JourneyLocation = NewLocation;
}