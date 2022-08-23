// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSoulSkill.h"
#include "SoulExchangeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "FPCharacter.h"
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
	AFPCharacter* Character = Cast<AFPCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!GameMode)
	{
		return false;
	}
	if (Level < MaxLevel)
	{
		if (Character->SkillsSystem->GetSkillPoints() > 0)
		{
			GameMode->SoulLifeTime = StartValue + Level * Delta;
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

bool ATimeSoulSkill::DownLevel()
{
	ASoulExchangeGameModeBase* GameMode = Cast<ASoulExchangeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	AFPCharacter* Character = Cast<AFPCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!GameMode)
	{
		return false;
	}
	if (Level > 1)
	{
		Level--;
		GameMode->SoulLifeTime = StartValue + Level * Delta;
		Character->SkillsSystem->AddSkillPoints(1);
		return true;
	}
	else
	{
		return false;
	}
}
