// Fill out your copyright notice in the Description page of Project Settings.


#include "FPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SoulExchangeGameModeBase.h"
#include "FPSoulCharacter.h"


AFPCharacter::AFPCharacter()
	:
	Speed(300),
	Stamina(15),
	isSplitPressed(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(0, 0, 40));

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));

	SkillsSystem = CreateDefaultSubobject<USkillSystem>(TEXT("SkillSystem"));

}

// Called when the game starts or when spawned
void AFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	ChangeSpeed(Speed);
	GetWorld()->GetTimerManager().SetTimer(RayTimer, this, &AFPCharacter::RayToSeeInteractiveItem, 0.1f, true);
}

// Called every frame
void AFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!ItemInHand)
	{
		return;
	}
	PhysicsHandle->SetTargetLocation(UKismetMathLibrary::GetForwardVector(Camera->GetComponentRotation()) * 150 + Camera->GetComponentLocation());
	if (sqrt((Camera->GetComponentLocation().X - ItemInHand->GetComponentLocation().X)* (Camera->GetComponentLocation().X - ItemInHand->GetComponentLocation().X) + (Camera->GetComponentLocation().Y - ItemInHand->GetComponentLocation().Y)* (Camera->GetComponentLocation().Y - ItemInHand->GetComponentLocation().Y) + (Camera->GetComponentLocation().Z - ItemInHand->GetComponentLocation().Z)* (Camera->GetComponentLocation().Z - ItemInHand->GetComponentLocation().Z)) > 225)
	{
		TakeReleased();
	}
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

	InputComponent->BindAction("Use", IE_Pressed, this, &AFPCharacter::UsePressed);
	
	InputComponent->BindAction("Take", IE_Pressed, this, &AFPCharacter::TakePressed);
	InputComponent->BindAction("Take", IE_Released, this, &AFPCharacter::TakeReleased);

	InputComponent->BindAction("TakeToInventory", IE_Pressed, this, &AFPCharacter::TakeToInventoryPressed);

	InputComponent->BindAction("Inventory", IE_Pressed, this, &AFPCharacter::InventoryPressed);

	InputComponent->BindAction("Split", IE_Pressed, this, &AFPCharacter::SplitPressed);
	InputComponent->BindAction("Split", IE_Released, this, &AFPCharacter::SplitReleased);

	InputComponent->BindAction("JumpToSoul", IE_Pressed, this, &AFPCharacter::JumpToSoul);
	InputComponent->BindAction("JumpToSoul", IE_Released, this, &AFPCharacter::CancelJumpToSoul);
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

void AFPCharacter::RayToSeeInteractiveItem()
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

void AFPCharacter::UsePressed()
{
	FHitResult* Hit = new FHitResult();
	FVector Start = Camera->GetComponentLocation();
	FVector End = UKismetMathLibrary::GetForwardVector(Camera->GetComponentRotation()) * 400 + Start;

	GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility);
	AInteractiveItems* Item = Cast<AInteractiveItems>(Hit->Actor);
	if (!Item)
	{
		return;
	}
	Item->OnUseKeyPressed.Broadcast();
}

void AFPCharacter::TakePressed()
{

	FHitResult* Hit = new FHitResult();
	FVector Start = Camera->GetComponentLocation();
	FVector End = UKismetMathLibrary::GetForwardVector(Camera->GetComponentRotation()) * 225 + Start;

	GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility);
	AInteractiveItems* Item = Cast<AInteractiveItems>(Hit->Actor);
	if (!Item )
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

void AFPCharacter::TakeReleased()
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

void AFPCharacter::TakeToInventoryPressed()
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
	OnTakeToInventoryKeyPressed.Broadcast(Item);
}

void AFPCharacter::InventoryPressed()
{
	OnInventoryKeyPressed.Broadcast(); 
}

void AFPCharacter::SplitPressed()
{
	isSplitPressed = true;
} 

void AFPCharacter::SplitReleased()
{
	isSplitPressed = false;
}

void AFPCharacter::JumpToSoul()
{
	ASoulExchangeGameModeBase* GameMode = Cast<ASoulExchangeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		return;
	}
	GameMode->JumpToSoul();
}

void AFPCharacter::CancelJumpToSoul()
{
	ASoulExchangeGameModeBase* GameMode = Cast<ASoulExchangeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		return;
	}
	GameMode->CancelJumpToSoul();
}


