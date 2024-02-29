// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilityType.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS(Abstract)
class MFFUNREALFINAL_API APlayerCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetAbility(AbilityType Ability) { CurrentAbility = Ability; }
	UFUNCTION(BlueprintCallable)
	AbilityType GetAbility() const { return CurrentAbility; }

	void UseAbility();

	static constexpr float MAX_ABILITY_TIME = 5.f;
	static constexpr float FLY_HEIGHT = 100.f;

private:
	AbilityType CurrentAbility = AbilityType::NONE;
	float AbilityTimeAccumulator = 0.f;
	bool bAbilityActive = false;

	void ActivateAbility();
	void DeactivateAbility();
};
