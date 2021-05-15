// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "GameCamera.h"
#include "Camera/CameraComponent.h"
#include "Muffin.h"

// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();

	Muffin = Cast<AMuffin>(UGameplayStatics::GetPlayerPawn(this,0));

	PC = UGameplayStatics::GetPlayerController(this,0);
	PC->SetViewTargetWithBlend(this,0);
}

void AGameCamera::MoveCamera()
{
	FVector TargetPos = FVector(GetActorLocation().X, GetActorLocation().Y, Muffin->GetActorLocation().Z);
	SetActorLocation(TargetPos);
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveCamera();
}

