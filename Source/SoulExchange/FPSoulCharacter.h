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
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/CapsuleComponent.h"
#include "FPSoulCharacter.generated.h"

UCLASS()
class SOULEXCHANGE_API AFPSoulCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSoulCharacter();


	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void ForwardMove(float value);
	void VertMove(float value);

	void HoriRot(float value);
	void VertRot(float value);

	UPROPERTY(EditAnywhere, Category = "Camera")
	UPhysicsHandleComponent* PhysicsHandle;



};
