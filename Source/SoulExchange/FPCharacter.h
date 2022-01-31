// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "InteractiveItems.h"
#include "Kismet/KismetMathLibrary.h"
#include "FPCharacter.generated.h"

UCLASS()
class SOULEXCHANGE_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HoriMove(float value);
	void VertMove(float value);

	void HoriRot(float value);
	void VertRot(float value);

	void ChangeSpeed(float speed);
	void StartSprint();
	void EndSprint();

	FTimerHandle StaminaTimer;
	void ChangeStaminaMinus();
	void ChangeStaminaPlus();

	FTimerHandle RayTimer;
	void RayToSeeInteractiveItem();
	AInteractiveItems* LastItem;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float Speed;
	
	bool isSprint;

	int Stamina;

};
