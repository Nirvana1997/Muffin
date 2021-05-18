// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cloud.generated.h"

class UBoxComponent;
class UTextRenderComponent;
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

	void DisplayScore();

	UFUNCTION(BlueprintImplementableEvent)
	void FadeOut();

	UPROPERTY(VisibleAnyWhere, Category="Collision")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category="Show")
	UStaticMeshComponent* CloudPlane;

	UPROPERTY(EditAnyWhere, Category="Show")
	TArray<UTexture*> Textures;

	UPROPERTY(BlueprintReadOnly, Category = "Show")
	UMaterialInstanceDynamic* MatInstance;

	UMaterialInterface* MatInterface;

	AMuffin* Muffin;

	UPROPERTY(VisibleAnyWhere, Category = "Show")
	UTextRenderComponent* ScoreText;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
