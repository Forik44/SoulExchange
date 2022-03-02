// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "TimeSpawnSoulSkill.generated.h"

/**
 * 
 */
UCLASS()
class SOULEXCHANGE_API ATimeSpawnSoulSkill : public ASkill
{
	GENERATED_BODY()
public:
	ATimeSpawnSoulSkill();
	virtual bool UpLevel() override;

private:
	float StartValue;
	float Delta;
};
