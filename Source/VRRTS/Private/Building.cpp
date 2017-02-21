// Fill out your copyright notice in the Description page of Project Settings.

#include "VRRTS.h"
#include "Building.h"

ABuilding::ABuilding(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) 
{
	PrimaryActorTick.bCanEverTick = false;

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

void ABuilding::BeginPlay() {
	Super::BeginPlay();
}

