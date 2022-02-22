// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSoulCharacter.h"

// Sets default values
AFPSoulCharacter::AFPSoulCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

