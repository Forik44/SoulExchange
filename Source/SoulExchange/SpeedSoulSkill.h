// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "SpeedSoulSkill.generated.h"

/**
 * 
 */
UCLASS()
class SOULEXCHANGE_API ASpeedSoulSkill : public ASkill
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	ASpeedSoulSkill();
	virtual bool UpLevel() override;
	virtual bool DownLevel() override;
private:
	float StartValue;
	float Delta;
};
