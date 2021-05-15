// Fill out your copyright notice in the Description page of Project Settings.


#include "Cloud.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstance.h"
#include "Muffin.h"

// Sets default values
ACloud::ACloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;

	CloudPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CloudPlane"));
	CloudPlane->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ACloud::BeginPlay()
{
	Super::BeginPlay();
	
	SetARandomCloudTexture();
}

void ACloud::SetARandomCloudTexture()
{
	MatInterface = CloudPlane->GetMaterial(0);

	MatInstance = CloudPlane->CreateDynamicMaterialInstance(0, MatInterface);
	int Index = FMath::RandRange(0, 2);
	if (Textures[Index])
	{
		MatInstance->SetTextureParameterValue(FName(TEXT("Texture")), Textures[Index]);
		CloudPlane->SetMaterial(0, MatInstance);
	}
}

// Called every frame
void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACloud::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	Muffin = Cast<AMuffin>(OtherActor);
	if (Muffin)
	{
		Muffin->Launch();
	}
}

