// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSoulSkill.h"
#include "SoulExchangeGameModeBase.h"
#include "Kismet/GameplayStatics.h"

ATimeSoulSkill::ATimeSoulSkill()
	:
	StartValue(4),
	Delta(0.5)
{
	MaxLevel = 8;
}

bool ATimeSoulSkill::UpLevel()
{
	ASoulExchangeGameModeBase* GameMode = Cast<ASoulExchangeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode)
	{
		return false;
	}
	if (Level < MaxLevel)
	{
		GameMode->SoulLifeTime = StartValue + Level * Delta;
		Level++;
		return true;
	}
	else
	{
		return false;
	}
}
