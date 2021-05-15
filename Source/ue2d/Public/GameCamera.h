// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCamera.generated.h"

class UCameraComponent;
class AMuffin;

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

	UPROPERTY(VisibleAnyWhere)
	UCameraComponent* CameraComp;

	APlayerController* PC;

	AMuffin* Muffin;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
