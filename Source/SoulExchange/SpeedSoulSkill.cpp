// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedSoulSkill.h"
#include "SoulExchangeGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "FPCharacter.h"

void ASpeedSoulSkill::BeginPlay()
{
	Super::BeginPlay();
	ASoulExchangeGameModeBase* GameMode = Cast<ASoulExchangeGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->SetSoulSpeed(StartValue);
}

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
	AFPCharacter* Character = Cast<AFPCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!GameMode)
	{
		return false;
	}
	if (Level < MaxLevel)
	{
		if (Character->SkillsSystem->GetSkillPoints() > 0)
		{
			GameMode->SetSoulSpeed(StartValue + Level * Delta);
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

bool ASpeedSoulSkill::DownLevel()
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
		GameMode->SetSoulSpeed(StartValue + Level * Delta);
		Character->SkillsSystem->AddSkillPoints(1);
		return true;
	}
	else
	{
		return false;
	}
}
