// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedSoulSkill.h"
#include "SoulExchangeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ASpeedSoulSkill::ASpeedSoulSkill()
	:
	StartValue(400),
	Delta(100)
{
	MaxLevel = 8;
}

bool ASpeedSoulSkill::UpLevel()
{
	ASoulExchangeGameModeBase* GameMode = Cast<ASoulExchangeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		return false;
	}
	if (Level < MaxLevel)
	{
		GameMode->SetSoulSpeed(StartValue + Level * Delta);
		Level++;
		return true;
	}
	else
	{
		return false;
	}
}
