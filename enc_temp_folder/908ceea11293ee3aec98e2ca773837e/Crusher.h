// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Crusher.generated.h"

UCLASS(Abstract)
class MFFUNREALFINAL_API ACrusherBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrusherBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActivateSlow() { bSlowed = true; }
	void DeactivateSlow() { bSlowed = false; }

	//static ACrusherBase* GetInstance() { return Instance; }
private:
	// Badly implemented singleton.
	//static ACrusherBase* Instance;

	static constexpr float MIN_HEIGHT = 50.f;
	static constexpr float MAX_HEIGHT = 300.f;
	static constexpr float SPEED = 1000.f;

	bool bSlowed = false;
	float Direction = 1.f;
};
