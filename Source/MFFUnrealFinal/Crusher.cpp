// Fill out your copyright notice in the Description page of Project Settings.


#include "Crusher.h"

// Sets default values
ACrusherBase::ACrusherBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACrusherBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrusherBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Location = GetActorLocation();

	if (Location.Z >= MAX_HEIGHT)
	{
		Direction = -1.f;
	}
	if (Location.Z <= MIN_HEIGHT)
	{
		Direction = 1.f;
	}

	Location.Z += Direction * SPEED * DeltaTime;

	SetActorLocation(Location);
}

