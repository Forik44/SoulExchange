// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSoulCharacter.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
AFPSoulCharacter::AFPSoulCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	Audio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(0, 0, 40));


	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	Camera->SetFieldOfView(110);
	Camera->PostProcessSettings.VignetteIntensity = 1;
	Camera->PostProcessSettings.bOverride_VignetteIntensity = true;
	Camera->PostProcessSettings.GrainIntensity = 0.8;
	Camera->PostProcessSettings.bOverride_GrainIntensity = true;
	
}

// Called when the game starts or when spawned
void AFPSoulCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(RayTimer, this, &AFPSoulCharacter::RayToSeeInteractiveItem, 0.1f, true);
	
	Collision = Cast<UCapsuleComponent>(GetRootComponent());
	Collision->SetCapsuleHalfHeight(45);
	Collision->IgnoreActorWhenMoving(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 1);
	Collision->SetAngularDamping(0);
	
	Audio->Sound = LoadObject<USoundCue>(nullptr, TEXT("/Game/Sounds/Effects/Soul"));
}

// Called every frame
void AFPSoulCharacter::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	if (!IsButtonFPressed && !IsButtonRPressed)
	{
		GetMovementComponent()->StopMovementImmediately();
	}
	if (!ItemInHand)
	{
		return;
	}
	PhysicsHandle->SetTargetLocation(UKismetMathLibrary::GetForwardVector(Camera->GetComponentRotation()) * 150 + Camera->GetComponentLocation());
	if (sqrt((Camera->GetComponentLocation().X - ItemInHand->GetComponentLocation().X) * (Camera->GetComponentLocation().X - ItemInHand->GetComponentLocation().X) + (Camera->GetComponentLocation().Y - ItemInHand->GetComponentLocation().Y) * (Camera->GetComponentLocation().Y - ItemInHand->GetComponentLocation().Y) + (Camera->GetComponentLocation().Z - ItemInHand->GetComponentLocation().Z) * (Camera->GetComponentLocation().Z - ItemInHand->GetComponentLocation().Z)) > 225)
	{
		TakeReleased();
	}
	
}

// Called to bind functionality to input
void AFPSoulCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Hori", this, &AFPSoulCharacter::VertMove);
	InputComponent->BindAxis("Vert", this, &AFPSoulCharacter::ForwardMove);

	InputComponent->BindAxis("HoriRot", this, &AFPSoulCharacter::HoriRot);
	InputComponent->BindAxis("VertRot", this, &AFPSoulCharacter::VertRot);

	InputComponent->BindAction("Take", IE_Pressed, this, &AFPSoulCharacter::TakePressed);
	InputComponent->BindAction("Take", IE_Released, this, &AFPSoulCharacter::TakeReleased);
}

void AFPSoulCharacter::PlayAudio()
{
	Audio->Play(0);
}

void AFPSoulCharacter::DeleteLastItem()
{
	if (!LastItem)
	{
		return;
	}
	LastItem->SetCustomDeapth(false);
	LastItem = nullptr;
}

void AFPSoulCharacter::SetSpeed(float Speed)
{
	GetCharacterMovement()->MaxFlySpeed = Speed;
}

void AFPSoulCharacter::ForwardMove(float value)
{
	if (value != 0)
	{	
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		FRotator Rotator = Camera->GetComponentRotation();
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotator);
		AddMovementInput(ForwardVector, value);
		IsButtonFPressed = true;
	}
	else
	{
		IsButtonFPressed = false;
	}
}

void AFPSoulCharacter::VertMove(float value)
{
	if (value != 0)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		AddMovementInput(GetActorRightVector(), value);
		IsButtonRPressed = true;
	}
	else
	{
		IsButtonRPressed = false;
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

		if (Rotation < 90 && Rotation > -90)
		{
			Camera->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void AFPSoulCharacter::TakePressed()
{

	FHitResult* Hit = new FHitResult();
	FVector Start = Camera->GetComponentLocation();
	FVector End = UKismetMathLibrary::GetForwardVector(Camera->GetComponentRotation()) * 225 + Start;

	GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility);
	AInteractiveItems* Item = Cast<AInteractiveItems>(Hit->Actor);
	if (!Item)
	{
		return;
	}

	ItemInHand = Hit->GetComponent();

	if (ItemInHand->GetMass() >= 500.f)
	{
		ItemInHand = nullptr;
		return;
	}

	ItemInHand->SetAngularDamping(10);
	PhysicsHandle->GrabComponentAtLocation(Hit->GetComponent(), FName(), Item->GetActorLocation());
}

void AFPSoulCharacter::TakeReleased()
{
	PhysicsHandle->ReleaseComponent();
	if (!ItemInHand)
	{
		return;
	}
	ItemInHand->SetAllPhysicsLinearVelocity(FVector(0, 0, 0));
	ItemInHand->SetAngularDamping(0);
	ItemInHand = nullptr;
}

void AFPSoulCharacter::RayToSeeInteractiveItem()
{
	FHitResult* Hit = new FHitResult();
	FVector Start = Camera->GetComponentLocation();
	FVector End = UKismetMathLibrary::GetForwardVector(Camera->GetComponentRotation()) * 400 + Start;

	GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility);

	AInteractiveItems* Item = Cast<AInteractiveItems>(Hit->Actor);

	if (Item != LastItem && LastItem != nullptr)
	{
		LastItem->SetCustomDeapth(false);
	}
	if (!Item)
	{
		LastItem = nullptr;
		return;
	}
	else
	{
		if (LastItem != Item)
		{
			LastItem = Item;
			Item->SetCustomDeapth(true);
		}
	}
}


