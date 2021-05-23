// Fill out your copyright notice in the Description page of Project Settings.


#include "Muffin.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMuffin::AMuffin()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LaunchVelocity = FVector(0, 0, 1500);
	AirSpeed = 3500.0f;
	GroundSpeed = 300.0f;
	Reset();
}

// Called when the game starts or when spawned
void AMuffin::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());
	PC->bShowMouseCursor = true;
}

void AMuffin::MoveTowardsCursor()
{
	FVector MouseLocation, MouseDirection;
	PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	float YDir = FMath::Clamp(MouseLocation.Y - GetActorLocation().Y, -1.0f, 1.0f);

	float ScaleValue = FMath::Clamp(FMath::Abs(MouseLocation.Y - GetActorLocation().Y) / 100, 0.0f, 1.0f);
	FVector Dir = FVector(0, YDir, 0);
	AddMovementInput(Dir, ScaleValue);
}

void AMuffin::LaunchOnAnyKeyPress()
{
	if (bGameStarted == false)
	{
		Launch();
		bGameStarted = true;
	}
}

void AMuffin::Launch()
{
	LaunchCharacter(LaunchVelocity, false, true);
}

void AMuffin::IncreaseScore()
{
	Score++;
}

int AMuffin::GetScore() const
{
	return Score;
}

// Called every frame
void AMuffin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bDead == false)
	{
		MoveTowardsCursor();
		SetSpeed();
	}
}

// Called to bind functionality to input
void AMuffin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMuffin::LaunchOnAnyKeyPress);
}

void AMuffin::SetSpeed()
{
	if (GetCharacterMovement()->IsFalling() == true)
	{
		GetCharacterMovement()->MaxWalkSpeed = AirSpeed;
	}
	else
	{
		if (bGameStarted == false)
		{
			GetCharacterMovement()->MaxWalkSpeed = GroundSpeed;
		}
		else
		{
			GameOver();
		}
	}
}

void AMuffin::GameOver()
{
	bDead = true;
	SetActorRotation(FRotator::ZeroRotator);
	EnableInput(PC);
	DisplayRestart();
}

void AMuffin::Reset()
{
	Score = 0;
	bDead = false;
	bGameStarted = false;
}
