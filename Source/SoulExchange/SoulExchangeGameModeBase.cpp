// Copyright Epic Games, Inc. All Rights Reserved.


#include "SoulExchangeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "FPCharacter.h"

void ASoulExchangeGameModeBase::ChangeCharacter(ACharacter* Character)
{
	if (!Character)
	{
		return;
	}
	OnChangeCharacterPressed.Broadcast(Character);
}

void ASoulExchangeGameModeBase::JumpToSoul()
{
	ASoulExchangeGameModeBase* GameMode = Cast<ASoulExchangeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		return;
	}
	AFPCharacter* MainFPCharacter = Cast<AFPCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!MainFPCharacter)
	{
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AFPSoulCharacter* Soul = GetWorld()->SpawnActor<AFPSoulCharacter>(MainFPCharacter->Camera->GetComponentLocation(), FRotator(0, MainFPCharacter->Camera->GetComponentRotation().Yaw, MainFPCharacter->Camera->GetComponentRotation().Roll), SpawnParameters);
	ChangeCharacter(Soul);
}
