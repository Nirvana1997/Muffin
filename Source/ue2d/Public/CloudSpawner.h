// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CloudSpawner.generated.h"

class UBoxComponent;
class ACloud;
class AMuffin;

UCLASS()
class UE2D_API ACloudSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACloudSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnCloud();

	UFUNCTION(BlueprintCallable)
		void Reset();

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		UBoxComponent* SpawnArea;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		UBoxComponent* TriggerArea;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
		USceneComponent* DefaultRootComponent;

	UPROPERTY(EditAnyWhere, Category = "Cloud")
		TSubclassOf<ACloud> Cloud;

	AMuffin* Muffin;

	UPROPERTY(EditAnyWhere, Category = "Cloud")
		int InitialSpawnAmount;

	UPROPERTY(EditAnyWhere, Category = "Cloud")
		float SpawnSpacing;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
