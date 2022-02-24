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

void ASoulExchangeGameModeBase::JumpToSoulPrivate()
{

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

void ASoulExchangeGameModeBase::StartSpawnTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(SoulSpawnTimer);
	GetWorld()->GetTimerManager().SetTimer(SoulSpawnTimer, this, &ASoulExchangeGameModeBase::JumpToSoulPrivate, SoulSpawnTime, false);
}

void ASoulExchangeGameModeBase::StopSpawnTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(SoulSpawnTimer);
}

void ASoulExchangeGameModeBase::JumpToSoul()
{
	StartSpawnTimer();
}

void ASoulExchangeGameModeBase::CancelJumpToSoul()
{
	StopSpawnTimer();
}
