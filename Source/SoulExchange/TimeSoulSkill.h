// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill.h"
#include "TimeSoulSkill.generated.h"

/**
 * 
 */
UCLASS()
class SOULEXCHANGE_API ATimeSoulSkill : public ASkill
{
	GENERATED_BODY()

public:
	ATimeSoulSkill();
	virtual bool UpLevel() override;
	virtual bool DownLevel() override;
private:
	float StartValue;
	float Delta;
};
