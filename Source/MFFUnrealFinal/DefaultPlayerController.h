// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "DefaultPlayerController.generated.h"

class UEnhancedInputComponent;
class APlayerCharacterBase;
class UInputMappingContext;

/**
 * 
 */
UCLASS(Abstract)
class MFFUNREALFINAL_API ADefaultPlayerControllerBase : public APlayerController
{
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Input")
	UInputAction* ActionMove = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputAction* ActionLook = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	UInputAction* ActionActivateAbility = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	void HandleMove(const FInputActionValue& InputActionValue);
	void HandleLook(const FInputActionValue& InputActionValue);
	void HandleActivateAbility();
	
private:
	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	APlayerCharacterBase* PlayerCharacter = nullptr;

	GENERATED_BODY()
};
