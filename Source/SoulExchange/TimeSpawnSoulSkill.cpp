// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSpawnSoulSkill.h"
#include "SoulExchangeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ATimeSpawnSoulSkill::ATimeSpawnSoulSkill()
	:
	StartValue(2),
	Delta(-0.25)
{
	MaxLevel = 8;
}

bool ATimeSpawnSoulSkill::UpLevel()
{
	ASoulExchangeGameModeBase* GameMode = Cast<ASoulExchangeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		return false;
	}
	if (Level < MaxLevel)
	{
		GameMode->SoulSpawnTime = StartValue + Level * Delta;
		Level++;
		return true;
	}
	else
	{
		return false;
	}
}
