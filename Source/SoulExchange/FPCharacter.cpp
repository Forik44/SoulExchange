// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"

// Sets default values
AFPCharacter::AFPCharacter()
	:
	Speed(300),
	Stamina(15)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(RootComponent);
	Camera->SetRelativeLocation(FVector(0, 0, 40));

}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	ChangeSpeed(Speed);
}

// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Hori", this, &AFPCharacter::HoriMove);
	InputComponent->BindAxis("Vert", this, &AFPCharacter::VertMove);

	InputComponent->BindAxis("HoriRot", this, &AFPCharacter::HoriRot);
	InputComponent->BindAxis("VertRot", this, &AFPCharacter::VertRot);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &AFPCharacter::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AFPCharacter::EndSprint);

}

void AFPCharacter::HoriMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AFPCharacter::VertMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void AFPCharacter::HoriRot(float value)
{
	if (value)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void AFPCharacter::VertRot(float value)
{
	if (value)
	{
		float Rotation = Camera->GetRelativeRotation().Pitch + value;

		if (Rotation < 65 && Rotation > -65)
		{
			Camera->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void AFPCharacter::ChangeSpeed(float speed)
{
	Cast<UCharacterMovementComponent>(GetMovementComponent())->MaxWalkSpeed = speed;
}

void AFPCharacter::StartSprint()
{
	if (Stamina > 2)
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaTimer);
		ChangeStaminaMinus();
		ChangeSpeed(Speed * 1.5);
		isSprint = true;
	}
}

void AFPCharacter::EndSprint()
{
	if (isSprint == true)
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaTimer);
		AFPCharacter::ChangeStaminaPlus();
		ChangeSpeed(Speed / 1.5);
		isSprint = false;
	}
}

void AFPCharacter::ChangeStaminaMinus()
{
	Stamina--;
	GetWorld()->GetTimerManager().SetTimer(StaminaTimer, this, &AFPCharacter::ChangeStaminaMinus, 1.0f, true);
	if (Stamina < 1)
	{
		EndSprint();
	}
	
}

void AFPCharacter::ChangeStaminaPlus()
{
	if (Stamina < 15)
	{
		GetWorld()->GetTimerManager().SetTimer(StaminaTimer, this, &AFPCharacter::ChangeStaminaPlus, 0.5f, true);
		Stamina++;
	}
	
}

