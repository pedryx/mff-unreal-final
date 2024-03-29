// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultPlayerController.h"
#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ADefaultPlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<APlayerCharacterBase>(aPawn);
	checkf(PlayerCharacter, TEXT("ADefaultPlayerControllerBase derived classes should only posses APlayerCharacter."));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to the EngancedInputComponent."));

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get reference to the EnhancedInputLocalPlayerSubsystem."));

	checkf(InputMappingContext, TEXT("InputMappingContext was not specified."));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);

	if (ActionMove)
	{
		EnhancedInputComponent->BindAction(
			ActionMove,
			ETriggerEvent::Triggered,
			this,
			&ADefaultPlayerControllerBase::HandleMove
		);
	}

	if (ActionLook)
	{
		EnhancedInputComponent->BindAction(
			ActionLook,
			ETriggerEvent::Triggered,
			this,
			&ADefaultPlayerControllerBase::HandleLook
		);
	}

	if (ActionActivateAbility)
	{
		EnhancedInputComponent->BindAction(
			ActionActivateAbility,
			ETriggerEvent::Triggered,
			this,
			&ADefaultPlayerControllerBase::HandleActivateAbility
		);
	}
}

void ADefaultPlayerControllerBase::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void ADefaultPlayerControllerBase::HandleMove(const FInputActionValue& InputActionValue)
{
	const float MovementDir = InputActionValue.Get<float>();

	FVector OriginalLocation = PlayerCharacter->GetActorLocation();
	FVector NewLocation = OriginalLocation + PlayerCharacter->GetActorForwardVector() * 100. * MovementDir;

	FHitResult HitResult;
	PlayerCharacter->SetActorLocation(NewLocation, true, &HitResult);

	if (HitResult.bBlockingHit)
	{
		PlayerCharacter->SetActorLocation(OriginalLocation);
	}
}

void ADefaultPlayerControllerBase::HandleLook(const FInputActionValue& InputActionValue)
{
	const float LookDir = InputActionValue.Get<float>();

	RotationInput.Add(0., 90. * LookDir, 0.);
}

void ADefaultPlayerControllerBase::HandleActivateAbility()
{
	PlayerCharacter->UseAbility();
}