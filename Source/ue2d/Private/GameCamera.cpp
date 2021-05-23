// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Muffin.h"
#include "Cloud.h"

// Sets default values
AGameCamera::AGameCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(RootComponent);

	DestroyArea = CreateDefaultSubobject<UBoxComponent>(TEXT("DestroyArea"));
	DestroyArea->SetupAttachment(RootComponent);

	bFollowPlayer = true;
}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();

	Muffin = Cast<AMuffin>(UGameplayStatics::GetPlayerPawn(this, 0));

	PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->SetViewTargetWithBlend(this, 0);
}

void AGameCamera::MoveCamera()
{
	FVector TargetPos = FVector(GetActorLocation().X, GetActorLocation().Y, Muffin->GetActorLocation().Z);
	SetActorLocation(TargetPos);
}

void AGameCamera::CheckIfFailing()
{
	if (Muffin->GetVelocity().Z < 0)
	{
		UpdateTimer();
	}
	else
	{
		ResetTimer();
	}
}

void AGameCamera::onSureFailing()
{
	bFollowPlayer = false;
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0));

	Muffin->SetActorLocation(FVector(Muffin->GetActorLocation().X, Muffin->GetActorLocation().Y, 0));
	Muffin->DisableInput(PC);
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFollowPlayer == true)
	{
		MoveCamera();

		CheckIfFailing();
	}
}

void AGameCamera::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	Cloud = Cast<ACloud>(OtherActor);
	if (Cloud)
	{
		Cloud->Destroy();
	}
}

