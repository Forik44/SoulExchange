#include "SkillSystem.h"

USkillSystem::USkillSystem() 
:
SkillPoints(9)
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USkillSystem::BeginPlay()
{
	Super::BeginPlay();
	SpawnSkills();
	
}

void USkillSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USkillSystem::AddSkillPoints(int Value)
{
	SkillPoints += Value;
}

int USkillSystem::GetSkillPoints()
{
	return SkillPoints;
}

void USkillSystem::SpawnSkills()
{
	FActorSpawnParameters SpawnParameters;
	for (size_t i = 0; i < Skills.Num(); i++)
	{
		SpawnedSkills.Add(GetWorld()->SpawnActor<ASkill>(Skills[i], FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParameters));
	}
	
}

