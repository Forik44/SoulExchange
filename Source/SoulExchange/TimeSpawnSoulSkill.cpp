// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSpawnSoulSkill.h"
#include "SoulExchangeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "FPCharacter.h"

ATimeSpawnSoulSkill::ATimeSpawnSoulSkill()
	:
	StartValue(2),
	Delta(-0.27)
{
	MaxLevel = 8;
}

bool ATimeSpawnSoulSkill::UpLevel()
{
	ASoulExchangeGameModeBase* GameMode = Cast<ASoulExchangeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	AFPCharacter* Character = Cast<AFPCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!GameMode)
	{
		return false;
	}
	if (Level < MaxLevel)
	{
		if (Character->SkillsSystem->GetSkillPoints() > 0)
		{
			GameMode->SoulSpawnTime = StartValue + Level * Delta;
			Level++;
			Character->SkillsSystem->AddSkillPoints(-1);
			return true;
		}
		else 
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
