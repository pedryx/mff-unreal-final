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

	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementDir);
}

void ADefaultPlayerControllerBase::HandleLook(const FInputActionValue& InputActionValue)
{
	const float LookDir = InputActionValue.Get<float>();

	AddYawInput(LookDir);
}

void ADefaultPlayerControllerBase::HandleActivateAbility()
{
	PlayerCharacter->UseAbility();
}