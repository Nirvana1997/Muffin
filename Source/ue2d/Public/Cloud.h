// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cloud.generated.h"

class UBoxComponent;
class AMuffin;

UCLASS()
class UE2D_API ACloud : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetARandomCloudTexture();

	UPROPERTY(VisibleAnyWhere, Category="Collision")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnyWhere, Category="Show")
	UStaticMeshComponent* CloudPlane;

	UPROPERTY(EditAnyWhere, Category="Show")
	TArray<UTexture*> Textures;

	UMaterialInstanceDynamic* MatInstance;

	UMaterialInterface* MatInterface;

	AMuffin* Muffin;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
