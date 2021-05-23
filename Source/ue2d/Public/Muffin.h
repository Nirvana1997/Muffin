// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Muffin.generated.h"

UCLASS()
class UE2D_API AMuffin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMuffin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveTowardsCursor();

	void LaunchOnAnyKeyPress();

	void SetSpeed();

	void GameOver();

	UFUNCTION(BlueprintCallable)
		void Reset();

	UFUNCTION(BlueprintImplementableEvent)
		void DisplayRestart();

	UPROPERTY(BlueprintReadOnly)
		bool bDead;

	bool bGameStarted;

	APlayerController* PC;

	FVector LaunchVelocity;

	UPROPERTY(EditAnyWhere, Category = "Speed")
		float AirSpeed;
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float GroundSpeed;

	int Score;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void Launch();

	void IncreaseScore();

	int GetScore() const;
};
