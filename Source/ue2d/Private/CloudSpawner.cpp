// Fill out your copyright notice in the Description page of Project Settings.


#include "CloudSpawner.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Cloud.h"
#include "Muffin.h"

// Sets default values
ACloudSpawner::ACloudSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRootComponent"));
	RootComponent = DefaultRootComponent;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(RootComponent);
	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerArea"));
	TriggerArea->SetupAttachment(RootComponent);
	InitialSpawnAmount = 6;
	SpawnSpacing = 300.0f;
}

// Called when the game starts or when spawned
void ACloudSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ACloudSpawner::SpawnCloud()
{
	FVector SpawnOrigin = SpawnArea->Bounds.Origin;
	FVector SpawnExtent = SpawnArea->Bounds.BoxExtent;
	float YLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent).Y;

	FVector SpawnLocation = FVector(SpawnArea->GetComponentLocation().X, YLocation, SpawnArea->GetComponentLocation().Z);

	GetWorld()->SpawnActor<ACloud>(Cloud, SpawnLocation, FRotator::ZeroRotator);

	AddActorWorldOffset(FVector(0, 0, SpawnSpacing));
}

void ACloudSpawner::Reset()
{
	InitialSpawnAmount = 6;

	SetActorLocation(FVector::ZeroVector);

	TArray<AActor*> FoundClouds;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACloud::StaticClass(), FoundClouds);

	for (AActor* TActor : FoundClouds)
	{
		ACloud* MyCloud = Cast<ACloud>(TActor);
		if (MyCloud != nullptr)
		{
			MyCloud->Destroy();
		}
	}

	while (InitialSpawnAmount > 0)
	{
		InitialSpawnAmount--;
		SpawnCloud();
	}
}

// Called every frame
void ACloudSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloudSpawner::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	Muffin = Cast<AMuffin>(OtherActor);
	if (Muffin)
	{
		SpawnCloud();
	}
}
