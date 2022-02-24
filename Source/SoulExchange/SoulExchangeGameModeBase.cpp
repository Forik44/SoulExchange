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

	MainFPCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!MainFPCharacter)
	{
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AFPSoulCharacter* Soul = GetWorld()->SpawnActor<AFPSoulCharacter>(Cast<AFPCharacter>(MainFPCharacter)->Camera->GetComponentLocation(), FRotator(0, Cast<AFPCharacter>(MainFPCharacter)->Camera->GetComponentRotation().Yaw, Cast<AFPCharacter>(MainFPCharacter)->Camera->GetComponentRotation().Roll), SpawnParameters);
	ChangeCharacter(Soul);
	StartSoulLife();
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

void ASoulExchangeGameModeBase::StartSoulLife()
{
	GetWorld()->GetTimerManager().SetTimer(SoulLifeTimer, this, &ASoulExchangeGameModeBase::EndSoulLife, SoulLifeTime, false);
}

void ASoulExchangeGameModeBase::EndSoulLife()
{
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->Destroy();
	ChangeCharacter(MainFPCharacter);
}

void ASoulExchangeGameModeBase::JumpToSoul()
{
	StartSpawnTimer();
}

void ASoulExchangeGameModeBase::CancelJumpToSoul()
{
	StopSpawnTimer();
}
