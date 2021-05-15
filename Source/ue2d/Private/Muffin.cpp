// Fill out your copyright notice in the Description page of Project Settings.


#include "Muffin.h"

// Sets default values
AMuffin::AMuffin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LaunchVelocity = FVector(0, 0, 1500);
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
	FVector Dir = FVector(0, YDir, 0);
	AddMovementInput(Dir);
}

void AMuffin::LaunchOnAnyKeyPress()
{
	Launch();
}

void AMuffin::Launch()
{
	LaunchCharacter(LaunchVelocity, false, true);
}

// Called every frame
void AMuffin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveTowardsCursor();
}

// Called to bind functionality to input
void AMuffin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMuffin::LaunchOnAnyKeyPress);
}

