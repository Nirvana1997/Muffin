// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCamera.generated.h"

class UCameraComponent;
class AMuffin;
class UBoxComponent;
class ACloud;

UCLASS()
class UE2D_API AGameCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveCamera();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateTimer();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetTimer();

	void CheckIfFailing();

	UFUNCTION(BlueprintCallable)
	void onSureFailing();

	UPROPERTY(VisibleAnyWhere, Category = "Component")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnyWhere, Category="Component")
	UBoxComponent* DestroyArea;

	APlayerController* PC;

	AMuffin* Muffin;

	ACloud* Cloud;

	UPROPERTY(BlueprintReadWrite)
	bool bFollowPlayer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
