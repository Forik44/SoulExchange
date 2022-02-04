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
#include "FPCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTakeToInventoryKeyPressedEvent, AInteractiveItems*, Item);



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

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FTakeToInventoryKeyPressedEvent OnTakeToInventoryKeyPressed;

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

	void UsePressed();

	void TakePressed();
	void TakeReleased();

	void TakeToInventoryPressed();

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UPhysicsHandleComponent* PhysicsHandle;

	UPrimitiveComponent* ItemInHand;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float Speed;
	
	bool isSprint;

	int Stamina;

};
