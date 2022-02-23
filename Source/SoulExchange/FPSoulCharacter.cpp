// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSoulCharacter.h"
#include "Components/InputComponent.h"

// Sets default values
AFPSoulCharacter::AFPSoulCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(0, 0, 40));

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));


}

// Called when the game starts or when spawned
void AFPSoulCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSoulCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSoulCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Hori", this, &AFPSoulCharacter::VertMove);
	InputComponent->BindAxis("Vert", this, &AFPSoulCharacter::ForwardMove);

	InputComponent->BindAxis("HoriRot", this, &AFPSoulCharacter::HoriRot);
	InputComponent->BindAxis("VertRot", this, &AFPSoulCharacter::VertRot);
}

void AFPSoulCharacter::ForwardMove(float value)
{
	if (value)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		FRotator Rotator = Camera->GetComponentRotation();
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotator);
		AddMovementInput(ForwardVector, value);
	}
}

void AFPSoulCharacter::VertMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AFPSoulCharacter::HoriRot(float value)
{
	if (value)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void AFPSoulCharacter::VertRot(float value)
{
	if (value)
	{
		float Rotation = Camera->GetRelativeRotation().Pitch + value;

		if (Rotation < 85 && Rotation > -85)
		{
			Camera->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

