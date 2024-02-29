// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	UE_LOG(LogTemp, Warning, TEXT("using ability"));

	if (CurrentAbility == AbilityType::NONE)
	{
		UE_LOG(LogTemp, Warning, TEXT("no ability"));
		return;
	}

	if (bAbilityActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("ability already active"));
		return;
	}

	bAbilityActive = true;
	UsedAbility = CurrentAbility;
	ActivateAbility();
}

void APlayerCharacterBase::ActivateAbility()
{
	switch (CurrentAbility)
	{
		case AbilityType::LEVITATION:
		{
			UE_LOG(LogTemp, Warning, TEXT("levitation begin"));

			GetCharacterMovement()->GravityScale = 0.;
			FVector Location = GetActorLocation();
			Location.Z += FLY_HEIGHT;
			SetActorLocation(Location);

			break;
		}
		case AbilityType::TIME_SLOWDOWN:
		{
			UE_LOG(LogTemp, Warning, TEXT("time slowdown begin"));

			if (Crusher == nullptr)
			{
				//Crusher = ACrusherBase::GetInstance();
				checkf(Crusher, TEXT("Reference to crusher is not set."));
			}

			Crusher->ActivateSlow();

			break;
		}
	}
}

void APlayerCharacterBase::DeactivateAbility()
{
	switch (UsedAbility)
	{
	case AbilityType::LEVITATION:
	{
		UE_LOG(LogTemp, Warning, TEXT("levitation end"));

		GetCharacterMovement()->GravityScale = 1.;

		break;
	}
	case AbilityType::TIME_SLOWDOWN:
		UE_LOG(LogTemp, Warning, TEXT("time slowdown end"));

		Crusher->DeactivateSlow();

		break;
	}
}