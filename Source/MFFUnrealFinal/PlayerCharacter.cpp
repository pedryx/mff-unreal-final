// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAbilityActive)
	{
		AbilityTimeAccumulator += DeltaTime;

		if (AbilityTimeAccumulator >= MAX_ABILITY_TIME)
		{
			AbilityTimeAccumulator = 0.f;
			bAbilityActive = false;
			DeactivateAbility();
		}
	}
}

// Called to bind functionality to input
void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacterBase::UseAbility()
{
	if (CurrentAbility == AbilityType::NONE)
	{
		return;
	}

	bAbilityActive = true;
	ActivateAbility();
}

void APlayerCharacterBase::ActivateAbility()
{
	switch (CurrentAbility)
	{
	case AbilityType::LEVITATION:
		break;
	case AbilityType::TIME_SLOWDOWN:
		break;
	}
}

void APlayerCharacterBase::DeactivateAbility()
{
	switch (CurrentAbility)
	{
	case AbilityType::LEVITATION:
		break;
	case AbilityType::TIME_SLOWDOWN:
		break;
	}
}