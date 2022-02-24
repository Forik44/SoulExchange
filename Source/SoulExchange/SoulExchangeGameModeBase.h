// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSoulCharacter.h"
#include "SoulExchangeGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeCharacterPressed, ACharacter*, Item);

UCLASS()
class SOULEXCHANGE_API ASoulExchangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void JumpToSoul();
	void CancelJumpToSoul();

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FChangeCharacterPressed OnChangeCharacterPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Soul")
	float SoulSpawnTime;
	
private:
	void ChangeCharacter(ACharacter* Character);

	void JumpToSoulPrivate();

	FTimerHandle SoulSpawnTimer;
	void StartSpawnTimer();
	void StopSpawnTimer();
};
