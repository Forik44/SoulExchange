// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill.generated.h"

UCLASS()
class SOULEXCHANGE_API ASkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skills")
	int Level;

	int MaxLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	FText Name;

	UFUNCTION(BlueprintCallable, Category = "Skills")
	virtual bool UpLevel();
};
