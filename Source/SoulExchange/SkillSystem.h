// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skill.h"
#include "SpeedSoulSkill.h"
#include "SkillSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULEXCHANGE_API USkillSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	USkillSystem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TArray<TSubclassOf<ASkill>> Skills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TArray<ASkill*> SpawnedSkills;

	void AddSkillPoints(int Value);
	int GetSkillPoints();
private:
	int SkillPoints;
	void SpawnSkills();
		
};
